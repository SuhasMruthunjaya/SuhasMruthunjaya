/*
 * TemperatureSensor.h
 *
 *  Created on: 22 Nov 2023
 *      Author: suhas
 */

#ifndef TEMPERATURESENSOR_H_
#define TEMPERATURESENSOR_H_

/** Importing the VoltageRegulator.h header files is necessary as we need to get the Regulated
 * 	voltage via the Voltage Regulator class. Since the Voltage recieved from the Power Supply Component
 * 	is usually very high than the desired value.
 */
#include "VoltageRegulator.h"

//! Temperature Sensor Class
/**
 * The Temperature Sensor records the surrounding temperature and sends the output to
 * the controller. It needs the desired Regulated_Voltage for it work without damaging its components.
 */

class Temperature_Sensor
{
private:

	/**! Declaring variable Regulated_Voltage of type Voltage_Regulator  */
	Voltage_Regulator Regulated_Voltage;

public:
	/**! Constructor to initialise the variables  */
	Temperature_Sensor(Voltage_Regulator Regulated_Voltage);
	virtual ~Temperature_Sensor();

	/**!	Function to sense the surrounding temperature and pass it to the Controller.*/
	float Current_temperature_Value();

};

#endif /* TEMPERATURESENSOR_H_ */
