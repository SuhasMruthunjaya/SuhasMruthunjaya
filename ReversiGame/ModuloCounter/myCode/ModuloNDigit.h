/*
 * ModuloNiDigit.h
 *
 *  Created on: 10 Nov 2023
 *      Author: suhas
 */

#ifndef MODULONDIGIT_H_
#define MODULONDIGIT_H_

#include "global.h"

/*! Counter_Status Enum to represent the counter status */
typedef enum
{
	IS_NOTVALID,
	OVERFLOW,
	IS_VALID

}Counter_Status;

/*! This enum is used for printing function, when Counter_Value is passed, the value is displayed,
 *  when Counter_Name is passed, the name of the counter is displayed.
 */
typedef enum
{
	COUNTER_VALUE,
	COUNTER_NAME
}Counter_Prints;

//! Single Digit Counter Class
/** This is the class of Single Digit Modulo Counter. It has two Private attributes of type Maximum Counter Value
 *  and Current Counter Value. It has two public methods to count and display the counter.
 *
 */
class ModuloNDigit
{
private:

	//< Maximum_Counter_Value is the end value of a counter, it is inputed by the User.
	int max_count_value;

	//< Current_Counter_Value is the starting value of the counter, usually starts with 0.
	int current_count_value;

public:
	virtual ~ModuloNDigit();

	/*! Constructor for initialising a ModuloNDigit instance
	 * @param int max_count_value -  as given by the user
	 * @return - Does not return anything as it is a constructor
	 */
	ModuloNDigit(int max_count_value = 0);

	/*! This function increments the current_count_value once everytime it is called, and if current_count_value
	 *  is less than max_count_value-1. If not, it returns OVERFLOW and the current_count_value is 0.
	 *  @return - returns Enum of type Counter_Status
	 */
	Counter_Status count ();

	/*!
	 * This function takes in the enum Counter_prints as a parameter and if the enum is COUNTER_NAME, the
	 * name of the modulo (max_count) counter is displayed on console, if the enum is COUNTER_VALUE, the
	 * value of the current_count_value attribute is displayed on the screen.
	 * @param Counter_Prints Value
	 * @return - returns void
	 */
	void  print(Counter_Prints value);

	/*!	This function takes a parameter and sets the Current_count_value attribute
	 * @param currentCountValue:int - The current value is set to this value
	 * @return - returns void
	 */
	void setCurrentCountValue(int currentCountValue);

	/*!	This function takes a parameter and sets the Maximum_count_value attribute
	 * @param currentCountValue:int - The maximum value is set to this value
	 * @return - returns void
	 */
	void setMaxCountValue(int maxCountValue);

	/*!	This function returns the Current_count_value attribute
	 * @return - returns the current count value
	 */
	int getCurrentCountValue() const;

	/*!	This function returns the Maximum_count_value attribute
	 * @return - returns the maximum count value
	 */
	int getMaxCountValue() const;

	/*! This function takes the input from the user for number of digits attribute and returns the same
	 * @returns - Input Digit : int
	 */
	int getNumOfDigits();

	/*! This function takes the input from the user for InputType attribute and returns the same
	 * @returns - InputType : int
	 */
	int getType();

	/*!
	 * This method increments the Counter by using Operator Overloading Function.
	 * Pre-Increment.
	 * @return The return Value of this function is of reference to the type ModuloNDigit.
	 */
	ModuloNDigit& operator++ ();

	/*!
	 * This method increments the Counter by using Operator Overloading Function.
	 * Post-Increment.
	 * @return The return Value of this function is of the type ModuloNDigit.
	 */
	ModuloNDigit operator++ (int);

};

#endif /* MODULONDIGIT_H_ */
