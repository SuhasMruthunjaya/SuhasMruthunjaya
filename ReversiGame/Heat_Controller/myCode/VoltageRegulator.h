/*
 * VoltageRegulator.h
 *
 *  Created on:  22 Nov 2023
 *      Author: suhas
 */

#ifndef VOLTAGEREGULATOR_H_
#define VOLTAGEREGULATOR_H_

//! Voltage Regulator Class
/**
 * There is a need for Regulating the Voltage recieved from the Power supply unit,
 * as most of the devices works at 5V DC, whereas the output from the relays via
 * the Power Supply unit are usually more than the maximum voltage. The Class
 * Voltage_Regulator takes in the Actual_Voltage as input and step down it to a
 * reasonable value.
 */

#include "PowerSupply.h"

class Voltage_Regulator
{
private:
	/**! This is the voltage from the Power Supply */
	Power_Supply* Actual_Voltage;

public:
	/**! Constructor to initialise Actual_Voltage
	 * @param Power_Supply voltage: It takes in the voltage from the Power_Supply Class */
	//Voltage_Regulator();
	Voltage_Regulator(Power_Supply* voltage = nullptr);
	virtual ~Voltage_Regulator();

	/** This function regulates the unregulated Volts recieved from the Power Supply Unit.*/
	float Regulator();


};

#endif /* VOLTAGEREGULATOR_H_ */
