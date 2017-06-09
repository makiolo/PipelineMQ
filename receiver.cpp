#include <iostream>
#include <sstream>
#include <boost/algorithm/string.hpp>
#include <future>
#include <boost/circular_buffer.hpp>
// consume radio
#include <RF24/RF24.h>
// produce mqtt
#include <mqtt/client.h>
// produce in mysql for persistence
#include <boost/scoped_ptr.hpp>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <mysql_connection.h>
#include <mysql_driver.h>

class radio
{
public:
	explicit radio()
		: _r(RPI_BPLUS_GPIO_J8_15,RPI_BPLUS_GPIO_J8_24, BCM2835_SPI_SPEED_8MHZ)
	{
		radio_begin();
		recv_mode();
	}

	void send_mode(unsigned char channel = 116)
	{
		_r.setChannel(channel);
		_r.openWritingPipe(_pipes[1]);  
		_r.openReadingPipe(1,_pipes[0]);  
		_r.stopListening();
	}

	void recv_mode(unsigned char channel = 108)
	{
		_r.setChannel(channel);
		_r.openWritingPipe(_pipes[0]);  
		_r.openReadingPipe(1,_pipes[1]);  
		_r.startListening();  
	}

	void radio_begin()
	{
		_r.begin();                           // Setup and configure rf radio 
		_r.setPALevel(RF24_PA_HIGH);
		_r.setDataRate(RF24_2MBPS);  
		//_r.setDataRate(RF24_250KBPS); // Fast enough.. Better range
		//_r.setPALevel(RF24_PA_LOW);
		_r.setAutoAck(1);                     // Ensure autoACK is enabled  
		_r.setRetries(15, 15);                  // Optionally, increase the delay between retries. Want the number of auto-retries as high as possible (15)  
		_r.setCRCLength(RF24_CRC_16);         // Set CRC length to 16-bit to ensure quality of data  
		//_r.printDetails();                   // Dump the configuration of the rf unit for debugging  
		//_r.powerUp();                        //Power up the radio
	}

	auto get()
	{
		std::tuple<std::string, std::string, float> tpl;
		bool received = false;
		while(!received)
		{
			if(_r.available())
			{
				char data[32];
				_r.read(&data, sizeof(data));
				std::string d(data);
				try
				{
					std::vector<std::string> strs;
					boost::split(strs, d, boost::is_any_of(";"));
					const std::string& location = strs.at(0);
					const std::string& sensor = strs.at(1);
					float value = std::stof(strs.at(2));
					if(	(location == "salon" || location == "habita") 
						&&
						(sensor == "humidity" || sensor == "temperature" || sensor == "presence_1" || sensor == "presence_2" || sensor == "presence_3")
						&&
						((0.0 <= value) && (value <= 100.0)))
					{
						std::get<0>(tpl) = location;
						std::get<1>(tpl) = sensor;
						std::get<2>(tpl) = value;
						received = true;
					}
					else
					{
						std::cerr << "invalid " << location << " / " << sensor << " / " << value << std::endl;
					}
				}
				catch(std::out_of_range& e)
				{
					std::cerr << "error parsing: " << d << std::endl;
				}
			}
			else
			{
				delay(10);
			}
		}
		return tpl;
	}

protected:
	RF24 _r;
	const uint64_t _pipes[2] = { 0xABCDABCD71LL, 0x544d52687CLL }; 
};

class mqtt_client
{
public:
	explicit mqtt_client()
		: _client("tcp://localhost:1883", "receiver")
	{
		mqtt::connect_options connOpts;
		connOpts.set_keep_alive_interval(120);
		connOpts.set_clean_session(true);
		_client.connect(connOpts);
	}

	~mqtt_client()
	{
		_client.disconnect();
	}

	void publish(std::string location, std::string sensor, float value)
	{
		std::stringstream topic, payload;
		topic << "/domotica/" << location << "/" << sensor;
		payload << value;
		_client.publish(mqtt::message(topic.str(), payload.str(), 1, false));
	}
protected:
	mqtt::client _client;
};

void mysql_publish(std::string location, std::string sensor, float value)
{
	const int cooldown = 2;
	std::stringstream ss;
	ss << "select count(*) as cont from measures where ";
	ss << "location = " << "'" << location << "'" << " AND ";
	ss << "sensor = " << "'" << sensor << "'" << " AND ";
	ss << "value = " << "'" << value << "'" << " AND ";
	ss << "DATE_SUB(NOW(), INTERVAL " << cooldown << " SECOND) < time";
	sql::Driver* driver = sql::mysql::get_driver_instance();
	boost::scoped_ptr<sql::Connection> con(driver->connect("localhost", "domotica", ""));
	con->setSchema("domotica");
	boost::scoped_ptr< sql::Statement > stmt(con->createStatement());
	boost::scoped_ptr< sql::ResultSet > res(stmt->executeQuery(ss.str()));
	if(res->next() && res->getInt("cont") <= 0)
	{
		ss.str("");
		ss << "insert into measures (id, location, sensor, value, time) VALUES (";
		ss << "NULL, "; // id
		ss << "'" << location << "', "; // location
		ss << "'" << sensor << "', "; // sensor
		ss << "'" << value << "', "; // value
		ss << "CURRENT_TIMESTAMP)"; // time
		stmt->execute(ss.str());
	}
}

int main(int argc, char const* argv[])
{
	radio r;
	mqtt_client client;
	try
	{
		boost::circular_buffer<std::future<void> > async_buffer(16);
		while(true)
		{
			// read from radio
			auto tpl = r.get();
			const std::string& location = std::get<0>(tpl);
			const std::string& sensor = std::get<1>(tpl);
			float value = std::get<2>(tpl);

			// write on MQTT sync with QOS=1
			async_buffer.push_back( std::async(std::launch::async, std::bind(&mqtt_client::publish, client), location, sensor, value) );

			// write on MYSQL async
			async_buffer.push_back( std::async(std::launch::async, mysql_publish, location, sensor, value) );
		}
	}
	catch (const mqtt::exception& exc)
	{
		std::cerr << exc.what() << std::endl;
	}
	catch (const std::exception& exc)
	{
		std::cerr << exc.what() << std::endl;
	}
	return 0;
}
