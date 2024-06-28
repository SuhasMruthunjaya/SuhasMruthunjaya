/*
 * HeatingSwitch.cpp
 *
 *  Created on: 22 Nov 2023
 *      Author: suhas
 */

#include "HeatingSwitch.h"

	/**< The Constructor is used to Initialise the Variables
	 * @param float* Controller_Input: It points to the controllers current_temp_output*/
Heating_Switch::Heating_Switch(float* Controller_Input, Voltage_Regulator Regulated_Voltage)
{
	this->Controller_Output = Controller_Output;
	this->Regulated_Voltage = Regulated_Voltage;

}

Heating_Switch::~Heating_Switch()
{
	// TODO Auto-generated destructor stub
}


/**< If the Controller Output is less than the User defined inputs, the Switch turns ON
 * the Heater and vice versa */
void Heating_Switch::Heater_Switch()
{
}
