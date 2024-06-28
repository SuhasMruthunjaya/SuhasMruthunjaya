/*
 * PowerSupply.h
 *
 *  Created on: 22 Nov 2023
 *      Author: suhas
 */

#ifndef POWERSUPPLY_H_
#define POWERSUPPLY_H_

//!	 POWER_SUPPLY Class
/*!
 *  The Power Supply is the main component for any devices to work. It is passed through a Voltage Regulator
 *  to regulate the high Voltage output, which is necessary as some devices has a specific desired voltage for
 *  them to function. The Class has two functions to Power ON and Power OFF the Supplier.
 */

class Power_Supply
{
private:
	/**< Voltage of the Power Supplier */
	float Voltage;

public:
	/**< Constructor to initialise the attributes */
	Power_Supply();
	virtual ~Power_Supply();

	/**< Method for Switching ON the Power Supply */
	void Power_ON();

	/**<  Method for Switching ON the Power Supply*/
	void Power_OFF();
};

#endif /* POWERSUPPLY_H_ */
