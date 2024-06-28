/*
 * HeatingSwitch.h
 *
 *  Created on: 22 Nov 2023
 *      Author: suhas
 */

#ifndef HEATINGSWITCH_H_
#define HEATINGSWITCH_H_

/** Importing the VoltageRegulator.h header files is necessary as we need to get the Regulated
 * 	voltage via the Voltage Regulator class. Since the Voltage recieved from the Power Supply Component
 * 	is usually very high than the desired value.
 */
#include "Controller.h"
#include "VoltageRegulator.h"

//! Heating_Switch
/** The Controller send the difference in the sensor collected current temperature value and the User Inputed Value,
 * 	the heating Switch turns ON the heater if the Controller_Output is less than the User desired Value.
 *
 */
class Heating_Switch
{
private:
	/**< Output Value of the Controller Unit */
	float Controller_Output;

	/**< Regulated_Voltage - Output of Voltage Regulator */
	Voltage_Regulator Regulated_Voltage;

public:
	/**< The Constructor is used to Initialise the Variables
	 * @param float* Controller_Input: It points to the controllers current_temp_output*/
	Heating_Switch(float* Controller_Input, Voltage_Regulator Regulated_Voltage);
	virtual ~Heating_Switch();

	/**< If the Controller Output is less than the User defined inputs, the Switch turns ON
	 * the Heater and vice versa */
	void Heater_Switch();
};

#endif /* HEATINGSWITCH_H_ */
