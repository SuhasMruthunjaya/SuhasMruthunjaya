/*
 * ModuloNCounter.h
 *
 *  Created on: 11 Nov 2023
 *      Author: suhas
 */

#ifndef MODULONCOUNTER_H_
#define MODULONCOUNTER_H_

#include "ModuloNDigit.h"

typedef enum
{
	BINARY = 2,
	OCTAL = 8,
	DECIMAL = 10,
	HEXA = 16,

}counterType;

/*! MULTI_DIGIT COUNTER CLASS
 *
 * ModuloNCounter is a multi digit counter, which consists of a n digit single counter Array. This Class
 * consists of 2 Private Attributes and a couple of public methods.
 */
class ModuloNCounter
{
private:
	//< A pointer of type ModuloNDigit pointing to an Array of Single Counters.
	ModuloNDigit* singleCounter;

	//< Number of digits is inputed by the User, represents the N in ModuloNCounter.
	int num_of_digit;

public:

	/*! Constructor for initialising a ModuloNCounter instance with num_of_digits and type given
	 * by the user. A memory of num_of_digit times ModuloNDigit is created on the Heap,
	 * Also validates the type, sets to the object only if type = 2/8/10/16, any other type given by
	 * the user sets the type to 0
	 * @param int num_of_digits, int type - IN num_of_digits and type as given by the user
	 * @return - Does not return anything as it is a constructor
	 */
	ModuloNCounter(int num_of_digits = 0, int type = 0);

	/*!
	 * The Allocated memory for the created array of single Counters is deleted in this destructor.
	 */
	virtual ~ModuloNCounter();

	/*! This is a copy constructor overload, we need to overload the copy constructor for the post
	 * increment overload, as the object should be returned before incrementing and after returning the
	 * current count value is incremented. In this process while returning we copy the object to a new
	 * ModuloNCounter object (please refer the post increment overload function) here the default copy
	 * constructor is called if not overwritten. This just implements a shallow copy, whereas we need
	 * a deep copy between the objects.
	 */
	ModuloNCounter(const ModuloNCounter& orig);


	/*!
	 * Each single counter is counted till given Max_Value and is Overflowed when the Max is reached.
	 * When a counter is Overflowed, the next consecutive counter is incremented by 1. This continues until all the
	 * counters are in their Max value.
	 * @return - This method returns RC_OK if the execution is completed without any errors.
	 */
	RC_t ModuloCount(int digit);

	/*!
	 * This method prints the ModuloNCounter on the console.
	 * @param InputType:int - If the InputType is 2 or 16, the counter is printed on the screen with
	 * 16 columns, if the inputType is 8, the counter is printed in8 columns, similarly 10 columns for
	 * InputType is 10
	 * @return RC_t : returns RC_OK if successful
	 */
	RC_t ModuloPrint(int InputType);

	/*!
	 * This method increments the Counter by using Operator Overloading Function.
	 * Pre-Increment.
	 * @return The return Value of this function is of reference to the type ModuloNCounter.
	 */
	ModuloNCounter& operator++();

	/*!
	 * This method increments the Counter by using Operator Overloading Function.
	 * Post-Increment. We need to overload the copy constructor in this function
	 * @return The return Value of this function returns ModuloNCounter object
	 */
	ModuloNCounter operator++(int);



};

#endif /* MODULONCOUNTER_H_ */
