/*
 * Keyboard.h
 *
 *  Created on: 22 Nov 2023
 *      Author: suhas
 */

#ifndef KNOB_H_
#define KNOB_H_

/** Importing the VoltageRegulator.h header files is necessary as we need to get the Regulated
 * 	voltage via the Voltage Regulator class. Since the Voltage recieved from the Power Supply Component
 * 	is usually very high than the desired value.
 */
#include "VoltageRegulator.h"

//! User Input Class
/**
 * Keyboard or a knob regulator to set the desired room Temperature. The desired_value is inputed
 * by the User.
 */
class Knob
{
private:
	float Desired_value;					/** User inputs */
	Voltage_Regulator Regulated_Voltage;

public:
	/**Attributes are initialised in this constructor.
	 * @param Voltage_Regulator::Regulated_Voltage - Regulated Voltage is sent as a parameter for this constructor.
	 * @param Desired_Value of type float - Inputs taken from the User.
	 * @return No return value as it is a constructor.
	 */
	Knob(Voltage_Regulator Regulated_Voltage, float user_input_value);
	virtual ~Knob();
	/**
	 *	This function is used to take inputs from the User, the user turns the knob,
	 *	which is attached to a incremental decoder, this function wraps the decoder driver,
	 *	which gives the value of the pulses rotated, this is then used to deduce how much
	 *	degree the user wants to increase / reduce the current temperature.
	 *	@param float* user_input_value - The new value is updated from the user
	 * @return - returns void
	 */
	void get_Decoder(float* user_input_value);
};

#endif /* KNOB_H_ */
