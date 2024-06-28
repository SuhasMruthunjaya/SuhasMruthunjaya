/*
 * Controller.h
 *
 *  Created on: 9 Nov 2022
 *      Author: suhas
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

//! The main Controller Class
/**!
 * The Class Controller is a comparator unit, which gets the Current temperature value from the
 * temperature sensor and the desired temperature value from the knob and compare them, send
 * the value to switching unit, which in turn switches ON/OFF the Heater.
 * @Attribute float Current_temperature_Value.
 * @Attribute float Desired_temperatre_Value.
 */

#include "Knob.h"
#include "TemperatureSensor.h"
#include "VoltageRegulator.h"
#include "global.h"

class Controller
{
private:
	/**< This value is taken from the temperature sensor*/
	float Current_temperature_Value;

	/**< This value is taken from the Knob(User Input)*/
	float Desired_temperature_Value;

	/**< This value is of type Voltage_Regulator and it is the regulated Voltage outputed from the Voltage Regulator.
	 * The Controller works fine only when Regulated_value is in the desired range. */
	Voltage_Regulator Regulated_Value;


public:

	/**! Attributes are initialised in this constructor. Regulated Voltage is sent as a
	 * parameter for this constructor. Current_temperature_Value is the Temperature sensor
	 * output and Desired_temperature_Value is the output of the Keyboard(User Input)
	 * @param Current_temperature_Value				: [OUT] Current_temperature_Value from Temperature
	 * 														Sensor.
	 * @param Desired_temperature_Value				: [IN]  Desired temperature value inputed from the User.
	 * @Return - No return Value, as it is a constructor.
	 */
	Controller(float Current_temperature_Value, float Desired_temperature_Value, Voltage_Regulator regulator);

	virtual ~Controller();

	/**! This functions Compare between Current_temperature_Value and Desired_tempearture_Value and
	 * send it to the switching element.
	 * addHeat() is called if the current room temperature from the sensor is less than desired
	 * temperature
	 * removeHeat() is called if the current room temperature from the sensor is high than the
	 * desired temperature
	 * @return It returns RC_t type.
	 */
	RC_t Compare();

	/*!
	 * addHeat() is called if the current room temperature from the sensor is less than desired
	 * temperature
	 * @return : returns RC_OK if successful.
	 *
	 */
	RC_t addHeat();

	/*!
	 * removeHeat() is called if the current room temperature from the sensor is high than the
	 * desired temperature
	 * @return : returns RC_OK if successful.
	 *
	 */
	RC_t removeHeat();

	/*!
	 * This function gets the value from the regulator, When a regulator is turned, the degree it
	 * turned is calculated from the getDecoder function in the Knob class, we then get that value
	 * from this function to the controller.
	 * @param Knob* value : The value is updated in this variable
	 * @return: void
	 */
	void getUserValue (Knob* value);

	/*!
	 * This function gets the value from the Temperature Sensor to the controller.
	 * @param Temperature_Sensor* value : The value is updated in this variable.
	 * @return: void
	 */
	void getTempSensorValue (Temperature_Sensor* value);

};

#endif /* CONTROLLER_H_ */
