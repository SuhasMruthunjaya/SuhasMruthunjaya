/*
 * OutputConsole.h
 *
 *  Created on: 22 Nov 2023
 *      Author: suhas
 */

#ifndef OUTPUTCONSOLE_H_
#define OUTPUTCONSOLE_H_

/** Importing the VoltageRegulator.h header files is necessary as we need to get the Regulated
 * 	voltage via the Voltage Regulator class. Since the Voltage recieved from the Power Supply Component
 * 	is usually very high than the desired value */
#include "VoltageRegulator.h"

//! Output_Console
/** The Output is displaced in the LCD Screen, if the current value is less than the User defined inputs,
 * the Heaters turns on the Heather SWICTH
 */

#include "Controller.h"
class Output_Console
{
private:
	/**< The Current Temperature Value after the Heater value is held in this attribute */
	float Current_Temperature_Value;
	Voltage_Regulator Regulated_Voltage;

public:
	/*!
	 *  Initialises the attributes in this method.
	 *  @param float* Controller_Output: Takes in the pointer to the controller current temp input
	 */
	Output_Console(float* Controller_Output, Voltage_Regulator Regulated_Value);
	virtual ~Output_Console();

	/**< Prints the Current Temperature Value in the Console*/
	void Display_Current_Temperature_Value();
};

#endif /* OUTPUTCONSOLE_H_ */
