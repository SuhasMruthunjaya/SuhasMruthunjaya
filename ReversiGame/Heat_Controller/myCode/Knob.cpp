/*
 * Keyboard.cpp
 *
 *  Created on: 22 Nov 2022
 *      Author: suhas
 */

#include "Knob.h"


Knob::Knob(Voltage_Regulator Regulated_Voltage, float user_input_value)
{
	/**! Initialising Regulated_Voltage and Desired_Value provided by the user */
	this->Regulated_Voltage = Regulated_Voltage;
	this->Desired_value = user_input_value;
}

Knob::~Knob()
{
	// TODO Auto-generated destructor stub
}


void Knob::get_Decoder(float* user_input_value)
{
	/**
		 *	This function is used to take inputs from the User, the user turns the knob,
		 *	which is attached to a incremental decoder, this function wraps the decoder driver,
		 *	which gives the value of the pulses rotated, this is then used to deduce how much
		 *	degree the user wants to increase / reduce the current temperature.
		 *
	**/

}
