/*
 * Address.h
 *
 *  Created on: 16 Jan 2024
 *      Author: suhas
 */

#ifndef ADDRESS_H_
#define ADDRESS_H_

#include <string>


/**
 * @class Address
 * @brief Represents an address with street, postal code, city name, and
 * additional information.
 */
class Address
{
private:
	std::string street;
	unsigned short postalCode;
	std::string cityName;
	std::string additionalInfo;

public:

	/**
	 * @brief Constructor for the Address class.
	 *
	 * @param street The street name.
	 * @param postalCode The postal code.
	 * @param cityName The city name.
	 * @param additionalInfo Additional information about the address
	 * (default: "NaN").
	 */
	Address(std::string street, unsigned short postalCode,
			std::string cityName, std::string additionalInfo = "NaN");

	/**
	 * @brief Getter function for additionalInfo.
	 *
	 * @return const std::string& The additional information
	 * about the address.
	 */
	const std::string& getAdditionalInfo() const;

	/**
	 * @brief Getter function for cityName.
	 *
	 * @return const std::string& The city name.
	 */
	const std::string& getCityName() const;

	/**
	 * @brief Getter function for postalCode.
	 *
	 * @return unsigned short The postal code.
	 */
	unsigned short getPostalCode() const;

	/**
	 * @brief Getter function for street.
	 *
	 * @return const std::string& The street name.
	 */
	const std::string& getStreet() const;


	static Address read(std::istream& in);



};

#endif /* ADDRESS_H_ */
