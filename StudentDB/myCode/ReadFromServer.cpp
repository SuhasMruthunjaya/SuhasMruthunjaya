/*
 * ReadFromServer.cpp
 *
 *  Created on: 1 Feb 2024
 *      Author: suhas
 */

#include "ReadFromServer.h"
#include <Poco/UTF8Encoding.h>
#include <Poco/Windows1252Encoding.h>
#include <Poco/TextConverter.h>



#include <iostream>
#include <sstream>

using namespace boost::asio;
using namespace boost::property_tree;

/**
 * @brief Constructor for the ReadFromServer class.
 */
ReadFromServer::ReadFromServer()
{
}

/**
 * @brief Reads data from the specified server and port using Boost.Asio.
 *
 * @param server The server address.
 * @param port The port to connect to.
 * @return boost::property_tree::ptree The parsed property tree representing
 * the received data.
 */
ptree ReadFromServer::readServer(std::string server, std::string port)
{
	// Establish a TCP connection to the server
	ip::tcp::iostream stream;

	stream.connect(server,port);

	// Check if the connection is successful
	if(!stream)
	{
		std::cerr << "FAiled to connect to server " <<
				stream.error().message() << std::endl;
	}

	// Send a request to the server
	stream << "generate" << std::endl;
	stream.flush();

	// Receive and process the response
	std::string received_data, receivedJSON, end_data, closingData;

	std::getline(stream, received_data);

	std::getline(stream, receivedJSON);

	std::cout << receivedJSON << std::endl;

	Poco::UTF8Encoding utf8enc;
	Poco::Windows1252Encoding winEnc;
	Poco::TextConverter conv(utf8enc, winEnc);
	std::string converted;
	conv.convert(receivedJSON, converted);
	std::cout << converted.size() << " " << converted << std::endl;

	stream << "quit" << std::endl;

	// Parse the received JSON data into a property tree
	std::istringstream JSONStream(converted);

	ptree pt;

	read_json(JSONStream, pt);

	return pt;

}

/**
 * @brief Destructor for the ReadFromServer class.
 */
ReadFromServer::~ReadFromServer()
{

}

