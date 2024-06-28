/*
 * TemperatureSensor.cpp
 *
 *  Created on: 22 Nov 2023
 *      Author: suhas
 */

#include "TemperatureSensor.h"

/**! Constructor to initialise the variables  */
Temperature_Sensor::Temperature_Sensor(Voltage_Regulator Regulated_Voltage)
{
	// TODO Auto-generated constructor stub

	/**! Initialising the Regulated_Voltage taking from the Voltage_Regulator Class */
	this->Regulated_Voltage = Regulated_Voltage;

}

Temperature_Sensor::~Temperature_Sensor()
{
	// TODO Auto-generated destructor stub
}

/**!	Function to sense the surrounding temperature and pass it to the Controller.*/
float Temperature_Sensor::Current_temperature_Value()
{
	/**
	 *  Code to implement temperature sensing.
	 */


	return 0;
}
