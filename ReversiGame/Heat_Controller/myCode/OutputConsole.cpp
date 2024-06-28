/*
 * OutputConsole.cpp
 *
 *  Created on: 22 Nov 2023
 *      Author: suhas
 */

#include "OutputConsole.h"

#include "Controller.h"
#include "VoltageRegulator.h"

/*!
*  Initialises the attributes in this method.
*  @param float* Controller_Output: Takes in the pointer to the controller current temp input
*/

Output_Console::Output_Console(float* Controller_Output, Voltage_Regulator Regulated_Value)
{
	this->Current_Temperature_Value = *Controller_Output;
	this->Regulated_Voltage = Regulated_Voltage;


}

Output_Console::~Output_Console()
{
	// TODO Auto-generated destructor stub
}

/**< Prints the Current Temperature Value in the Console*/

void Output_Console::Display_Current_Temperature_Value()
{
	/**
	 * Code for printing the Current_Temperature_
	 */
}
