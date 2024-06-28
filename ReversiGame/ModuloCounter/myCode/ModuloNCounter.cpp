/*
 * ModuloNCounter.cpp
 *
 *  Created on: 11 Nov 2023
 *      Author: suhas
 */

#include "ModuloNCounter.h"
#include <iostream>


using namespace std;

/*! Constructor for initialising a ModuloNCounter instance with num_of_digits and type given
 * by the user. A memory of num_of_digit times ModuloNDigit is created on the Heap,
 * Also validates the type, sets to the object only if type = 2/8/10/16, any other type given by
 * the user sets the type to 0
 * @param int num_of_digits, int type - IN num_of_digits and type as given by the user
 * @return - Does not return anything as it is a constructor
 */
ModuloNCounter::ModuloNCounter(int num_of_digits, int type)
{
	int max_value;
	this->num_of_digit = num_of_digits;

	//singleCounter = (ModuloNDigit*)malloc(num_of_digits*sizeof(ModuloNDigit)); //new ModuloNDigit(this->num_of_digit);

	singleCounter = new ModuloNDigit[num_of_digits];
	if((type == 2) || (type == 8) || (type == 10) || (type == 16) )
	{
		max_value = type;
	}
	else
	{
		cout << " You have entered a different type than 2/8/10/16, hence "
				" initialising both the max_value and the current_value to 0" << endl;

		max_value = 0;
	}


	for(int i = 0; i < num_of_digits; i++)
	{
		singleCounter[i].setCurrentCountValue(0);
		singleCounter[i].setMaxCountValue(max_value);
	}

//	for(int i = 0; i < num_of_digits; i++)
//	{
//		cout << singleCounter[i].getCurrentCountValue();
//		if (i == num_of_digits -1)
//		{
//			cout << "\t";
//		}
//	}
}


/*!
 * The Allocated memory for the created array of single Counters is deleted in this destructor.
 */
ModuloNCounter::~ModuloNCounter()
{
	// TODO Auto-generated destructor stub

	delete[] singleCounter;
}


/*!
 * Each single counter is counted till given Max_Value and is Overflowed when the Max is reached.
 * When a counter is Overflowed, the next consecutive counter is increamented by 1. This continues until all the
 * counters are in their Max value.
 * @return - This method returns RC_OK if the execution is completed without any errors.
 */
RC_t ModuloNCounter::ModuloCount(int digit)
{
	if(digit < num_of_digit)
	{
		if(singleCounter[digit].count() == OVERFLOW)
		{
			digit = digit + 1;
			ModuloCount(digit);
		}
	}

	return RC_OK;

}

/*!
 * This method prints the ModuloNCounter on the console.
 * @param InputType:int - If the InputType is 2 or 16, the counter is printed on the screen with
 * 16 columns, if the inputType is 8, the counter is printed in8 columns, similarly 10 columns for
 * InputType is 10
 * @return RC_t : returns RC_OK if successful
 */
RC_t ModuloNCounter::ModuloPrint(int InputType)
{

	if(InputType == BINARY)
	{
		int count = 0;

		for(int i = num_of_digit -1; i >= 0; i--)
		{

			cout << singleCounter[i].getCurrentCountValue() << flush;

			if(i == 0)
				cout << " \t" ;

			if(singleCounter[i].getCurrentCountValue() == 1)
			{
				count = count +1;

			}

			if(count == num_of_digit)
			{

				cout << endl;
			}
		}
	}
	else if(InputType == OCTAL)
	{

		for(int i = num_of_digit -1; i >= 0; i--)
		{

			cout << singleCounter[i].getCurrentCountValue() << flush;

		}
		cout << "\t";
		if(singleCounter[0].getCurrentCountValue() == OCTAL -1)
		{
			cout << endl;
		}

	}
	else if(InputType == DECIMAL)
	{
		for(int i = num_of_digit -1; i >= 0; i--)
				{

					cout << singleCounter[i].getCurrentCountValue() << flush;

				}
				cout << "\t";
				if(singleCounter[0].getCurrentCountValue() == DECIMAL -1)
				{
					cout << endl;
				}

	}
	else if(InputType == HEXA)
	{
		for(int i = num_of_digit -1; i >= 0; i--)
		{
			cout << hex << singleCounter[i].getCurrentCountValue() << flush;
		}
		cout << "\t";
		if(singleCounter[0].getCurrentCountValue() == HEXA -1)
		{
			cout << endl;
		}
	}

return RC_OK;

}

/*!
 * This method increments the Counter by using Operator Overloading Function.
 * Pre-Increment.
 * @return The return Value of this function is of reference to the type ModuloNCounter.
 */
ModuloNCounter& ModuloNCounter::operator ++()
{

	ModuloCount(0);
	return *this;

}

/*! This is a copy constructor overload, we need to overload the copy constructor for the post
 * increment overload, as the object should be returned before incrementing and after returning the
 * current count value is incremented. In this process while returning we copy the object to a new
 * ModuloNCounter object (please refer the post increment overload function) here the default copy
 * constructor is called if not overwritten. This just implements a shallow copy, whereas we need
 * a deep copy between the objects.
 */

ModuloNCounter::ModuloNCounter(const ModuloNCounter &orig)
{
	num_of_digit = orig.num_of_digit;

	singleCounter = new ModuloNDigit[num_of_digit];

	for(int i = 0; i < num_of_digit; i++)
	{
		singleCounter[i] =  orig.singleCounter[i];
	}

}

/*!
 * This method increments the Counter by using Operator Overloading Function.
 * Post-Increment. We need to overload the copy constructor in this function
 * @return The return Value of this function returns ModuloNCounter object
 */
ModuloNCounter ModuloNCounter::operator ++(int)
{
	//< We need to overload the copy constructor for the below line //
	ModuloNCounter result = *this;

	ModuloCount(0);

	return result;

}
