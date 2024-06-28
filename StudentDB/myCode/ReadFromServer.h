/*
 * ReadFromServer.h
 *
 *  Created on: 1 Feb 2024
 *      Author: suhas
 */

#ifndef READFROMSERVER_H_
#define READFROMSERVER_H_
#include <string>

#include <boost/asio.hpp>
#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/json_parser.hpp"

/**
 * @class ReadFromServer
 * @brief Provides functionality to read data from a server.
 */
class ReadFromServer
{
public:
	/**
	 * @brief Constructor for the ReadFromServer class.
	 */
	ReadFromServer();

	/**
	 * @brief Reads data from the specified server and port using Boost.Asio.
	 *
	 * @param server The server address.
	 * @param port The port to connect to.
	 * @return boost::property_tree::ptree The parsed property tree
	 * representing the received data.
	 */
	static boost::property_tree::ptree
	readServer(std::string server, std::string port);

	/**
	 * @brief Destructor for the ReadFromServer class.
	 */
	virtual ~ReadFromServer();
};

#endif /* READFROMSERVER_H_ */
