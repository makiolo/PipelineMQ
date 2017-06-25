#include <iostream>
#include <sstream>
#include <ctime>
#include <boost/algorithm/string.hpp>
#include <stdexcept>
// consume radio
#include <RF24/RF24.h>
// produce mqtt
#include <mqtt/client.h>
// produce in mysql for persistence
#include <boost/scoped_ptr.hpp>

class radio_server
{
public:
	explicit radio_server()
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
		// _r.setDataRate(RF24_250KBPS); // Fast enough.. Better range
		// _r.setPALevel(RF24_PA_LOW);
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
						throw std::runtime_error("invalid input in radio");
					}
				}
				catch(std::out_of_range& e)
				{
					std::cerr << "error parsing: " << d << std::endl;
					throw std::runtime_error("error parsing radio");
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
		: _client("tcp://192.168.1.4:1883", "receiver")
	{
		mqtt::connect_options connOpts;
		connOpts.set_keep_alive_interval(120);
		connOpts.set_clean_session(true);
		connOpts.set_automatic_reconnect(true);
		_client.connect(connOpts);
	}

	~mqtt_client()
	{
		_client.disconnect();
	}

	void publish(std::time_t current_timestamp, std::string location, std::string sensor, float value)
	{
		std::stringstream topic, payload;
		topic << "/domotica/" << location << "/" << sensor;
		payload << current_timestamp << "/" << value;
		_client.publish(mqtt::message(topic.str(), payload.str(), 1, false));
	}
protected:
	mqtt::client _client;
};

int main(int argc, char const* argv[])
{
	radio_server radio;
	mqtt_client mqtt;
	while(true)
	{
		// read from radio
		auto tpl = radio.get();
		std::time_t current_timestamp = std::time(nullptr);
		const std::string& location = std::get<0>(tpl);
		const std::string& sensor = std::get<1>(tpl);
		float value = std::get<2>(tpl);
		mqtt.publish(current_timestamp, location, sensor, value);
		delay(20);
	}
	return 0;
}

