/*
 * Address.cpp
 *
 *  Created on: 16 Jan 2024
 *      Author: suhas
 */

#include "Address.h"


/**
 * @brief Constructor for the Address class.
 *
 * @param street The street name.
 * @param postalCode The postal code.
 * @param cityName The city name.
 * @param additionalInfo Additional information about the address
 * (default: "NaN").
 */
Address::Address(std::string street, unsigned short postalCode,
		std::string cityName, std::string additionalInfo) : street(street),
		cityName(cityName), additionalInfo(additionalInfo)
{

	this->postalCode = postalCode;

}

/**
 * @brief Getter function for additionalInfo.
 *
 * @return const std::string& The additional information
 * about the address.
 */
const std::string& Address::getAdditionalInfo() const
{
	return additionalInfo;
}


/**
 * @brief Getter function for cityName.
 *
 * @return const std::string& The city name.
 */
const std::string& Address::getCityName() const
{
	return cityName;
}

/**
 * @brief Getter function for postalCode.
 *
 * @return unsigned short The postal code.
 */
unsigned short Address::getPostalCode() const
{
	return postalCode;
}
/**
 * @brief Getter function for street.
 *
 * @return const std::string& The street name.
 */
const std::string& Address::getStreet() const
{
	return street;
}

Address Address::read(std::istream &in)
{
	std::string street;
	std::getline(in,street, ';');

	std::string postalCode_str;
	std::getline(in, postalCode_str, ';');
	unsigned short postalCode = std::stoi(postalCode_str);

	std::string cityName;
	std::getline(in, cityName, ';');

	std::string addnInfo;
	std::getline(in, addnInfo, '\n');

	return Address(street, postalCode, cityName, addnInfo);

}
