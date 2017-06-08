#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cctype>
#include <thread>
#include <chrono>
#include <mqtt/client.h>
#include <gmock/gmock.h>

using testing::AtLeast;
using testing::AnyNumber;
using testing::_;

const std::string SERVER_ADDRESS("tcp://localhost:1883");
const std::string CLIENT_ID("sync_subcribe_cpp");
const std::string TOPIC("hello");

const int QOS = 1;

/////////////////////////////////////////////////////////////////////////////

/**
 * Local callback & listener class for use with the client connection.
 * This is primarily intended to receive messages, but it will also monitor
 * the connection to the broker. If the connection is lost, it will attempt
 * to restore the connection and re-subscribe to the topic.
 */
class callback : public virtual mqtt::callback
{
	mqtt::client& cli_;

	void connected(const std::string& cause) override {
		std::cout << "\nConnected: " << cause << std::endl;
		cli_.subscribe(TOPIC, QOS);
		std::cout << std::endl;
	}

	// Callback for when the connection is lost.
	// This will initiate the attempt to manually reconnect.
	void connection_lost(const std::string& cause) override {
		std::cout << "\nConnection lost";
		if (!cause.empty())
			std::cout << ": " << cause << std::endl;
		std::cout << std::endl;
	}

	// Callback for when a message arrives.
	void message_arrived(mqtt::const_message_ptr msg) override {
		std::cout << msg->get_topic() << ": " << msg->get_payload_str() << std::endl;
	}

	void delivery_complete(mqtt::delivery_token_ptr token) override {}

public:
	callback(mqtt::client& cli) : cli_(cli) {}
};

/////////////////////////////////////////////////////////////////////////////

class SubscribeTests : testing::Test { };

TEST(SubscribeTests, TestSync)
{
	mqtt::connect_options connOpts;
	connOpts.set_keep_alive_interval(20);
	connOpts.set_clean_session(false);
	connOpts.set_automatic_reconnect(true);

	mqtt::client cli(SERVER_ADDRESS, CLIENT_ID);

	callback cb(cli);
	cli.set_callback(cb);

	// Start the connection.

	try {
		std::cout << "Connecting to the MQTT server..." << std::flush;
		cli.connect(connOpts);
		cli.subscribe(TOPIC, QOS);
		std::cout << "OK" << std::endl;
	}
	catch (const mqtt::exception& exc) {
		std::cerr << "\nERROR: Unable to connect to MQTT server: '"
			<< SERVER_ADDRESS << "'" << std::endl;
		return;
	}

	// Just block till user tells us to quit.

	while (std::tolower(std::cin.get()) != 'q')
		;

	// Disconnect

	try {
		std::cout << "\nDisconnecting from the MQTT server..." << std::flush;
		cli.disconnect();
		std::cout << "OK" << std::endl;
	}
	catch (const mqtt::exception& exc) {
		std::cerr << exc.what() << std::endl;
		return;
	}
}
