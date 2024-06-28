/*
 * VoltageRegulator.cpp
 *
 *  Created on: 10 Nov 2022
 *      Author: suhas
 */

#include "VoltageRegulator.h"


/**! Constructor to initialise Actual_Voltage
	 * @param Power_Supply voltage: It takes in the voltage from the Power_Supply Class */
Voltage_Regulator::Voltage_Regulator(Power_Supply* voltage)
{

	/** Initializing the private variables */
	Actual_Voltage = voltage;

}



/** This function regulates the unregulated Volts recieved from the Power Supply Unit.*/
float Voltage_Regulator::Regulator()
{
	/**
	 * Code for Regulating Voltage
	 */
	return 0;
}



Voltage_Regulator::~Voltage_Regulator()
{

}

//Voltage_Regulator::Voltage_Regulator()
//{
//}
