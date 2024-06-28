/*
 * ModuloNiDigit.cpp
 *
 *  Created on: 10 Nov 2023
 *      Author: suhas
 */

#include "ModuloNDigit.h"

#include <iostream>

using namespace std;


/*! Constructor for initialising a ModuloNDigit instance
 * @param int max_count_value -  as given by the user
 * @return - Does not return anything as it is a constructor
 */
ModuloNDigit::ModuloNDigit(int max_count_value)
{
	// TODO Auto-generated constructor stub
	this->current_count_value = 0;
	this->max_count_value = max_count_value;

}

ModuloNDigit::~ModuloNDigit()
{
	// TODO Auto-generated destructor stub
}

/*! This function increments the current_count_value once everytime it is called, and if current_count_value
 *  is less than max_count_value-1. If not, it returns OVERFLOW and the current_count_value is 0.
 *  @return - returns Enum of type Counter_Status
 */

Counter_Status ModuloNDigit::count()
{
	if(current_count_value < max_count_value-1)
	{
		current_count_value++;
		return IS_VALID;
	}
	else
	{
		current_count_value = 0;
		return OVERFLOW;
	}

}

/*!
 * This function takes in the enum Counter_prints as a parameter and if the enum is COUNTER_NAME, the
 * name of the modulo (max_count) counter is displayed on console, if the enum is COUNTER_VALUE, the
 * value of the current_count_value attribute is displayed on the screen.
 * @param Counter_Prints Value
 * @return - returns void
 */
void ModuloNDigit::print(Counter_Prints value)
{
	if(value == COUNTER_NAME)
	{
		cout << "Modulo " << max_count_value << " Counter" << endl;
	}
	else if (value == COUNTER_VALUE)
	{
		cout << current_count_value << endl;
	}

}


/*!	This function takes a parameter and sets the Current_count_value attribute
 * @param currentCountValue:int - The current value is set to this value
 * @return - returns void
 */
void ModuloNDigit::setCurrentCountValue(int currentCountValue)
{
	current_count_value = currentCountValue;
}


/*!	This function takes a parameter and sets the Maximum_count_value attribute
 * @param currentCountValue:int - The maximum value is set to this value
 * @return - returns void
 */
void ModuloNDigit::setMaxCountValue(int maxCountValue)
{
	max_count_value = maxCountValue;
}

/*!	This function returns the Current_count_value attribute
 * @return - returns the current count value
 */
int ModuloNDigit::getCurrentCountValue() const
{
	return current_count_value;
}

/*!	This function returns the Maximum_count_value attribute
 * @return - returns the maximum count value
 */
int ModuloNDigit::getMaxCountValue() const
{
	return max_count_value;
}


/*! This function takes the input from the user for number of digits attribute and returns the same
 * @returns - Input Digit : int
 */
int ModuloNDigit::getNumOfDigits()
{
	int InputDigits = 0;
	cin >> InputDigits;

	return InputDigits;
}

/*! This function takes the input from the user for InputType attribute and returns the same
 * @returns - InputType : int
 */
int ModuloNDigit::getType()
{
	int InputType = 0;
	cin >> InputType;

	return InputType;
}

/*!
 * This method increments the Counter by using Operator Overloading Function.
 * Pre-Increment.
 * @return The return Value of this function is of reference to the type ModuloNDigit.
 */

ModuloNDigit& ModuloNDigit::operator ++()
{
	count();
	return *this;
}

/*!
 * This method increments the Counter by using Operator Overloading Function.
 * Post-Increment.
 * @return The return Value of this function is of the type ModuloNDigit.
 */

ModuloNDigit ModuloNDigit::operator ++(int int1)
{
	ModuloNDigit result = *this;

	count();

	return result;

}
