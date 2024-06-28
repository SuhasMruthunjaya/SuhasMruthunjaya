/*
 * Controller.cpp
 *
 *  Created on: 22 Nov 2022
 *      Author: suhas
 */

#include "Controller.h"
#include "VoltageRegulator.h"

/**
 * The private attributes of the Controller class are initialised
 * in this constructor.
 */
Controller::Controller(float Current_temperature_Value, float Desired_temperature_Value, Voltage_Regulator Regulated_Value)
{
	// TODO Auto-generated constructor stub
	this->Current_temperature_Value = Current_temperature_Value;
	this->Desired_temperature_Value = Desired_temperature_Value;
	this->Regulated_Value = Regulated_Value;

}

Controller::~Controller()
{
	// TODO Auto-generated destructor stub
}

/**! This functions Compare between Current_temperature_Value and Desired_tempearture_Value and
 * send it to the switching element.
 * addHeat() is called if the current room temperature from the sensor is less than desired
 * temperature
 * removeHeat() is called if the current room temperature from the sensor is high than the
 * desired temperature
 * @return It returns RC_t type.
 */
RC_t Controller::Compare()
{
	return RC_OK;
}

/*!
 * addHeat() is called if the current room temperature from the sensor is less than desired
 * temperature
 * @return : returns RC_OK if successful.
 *
 */
RC_t addHeat()
{
	return RC_OK;
}

/*!
 * removeHeat() is called if the current room temperature from the sensor is high than the
 * desired temperature
 * @return : returns RC_OK if successful.
 *
 */
RC_t removeHeat()
{
	return RC_OK;
}

/*!
 * This function gets the value from the regulator, When a regulator is turned, the degree it
 * turned is calculated from the getDecoder function in the Knob class, we then get that value
 * from this function to the controller.
 * @param Knob* value : The value is updated in this variable
 * @return: void
 */
void getUserValue (Knob* value)
{

}

/*!
 * This function gets the value from the Temperature Sensor to the controller.
 * @param Temperature_Sensor* value : The value is updated in this variable.
 * @return: void
 */
void getTempSensorValue (Temperature_Sensor* value)
{

}
