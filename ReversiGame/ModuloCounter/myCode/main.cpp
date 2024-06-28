// Standard (system) header files
#include <iostream>
#include <cstdlib>
// Add more standard header files as required
// #include <string>

#include "ModuloNDigit.h"
#include "ModuloNCounter.h"

//#define Testing
#define modulocounter
//#define modulodigit

using namespace std;

// Add your project's header files here
// #include "CFraction.h"

// Main program
int main ()
{
    // TODO: Add your program code here
	cout << "ModuloCounter started." << endl << endl;

#ifdef modulodigit

	ModuloNDigit counter(10);
	counter.print(COUNTER_NAME);

//	for(int i=0; i<31; i++)
//	{
//		counter.print(COUNTER_VALUE);
//		counter.count();
//
//	}

	cout << "Pre-increment" << endl;

	for(int i=0; i<31; i++)
	{
		counter.print(COUNTER_VALUE);
		++counter;
	}

	cout << "Post-increment" << endl;

	for(int i=0; i<31; i++)
	{
		counter.print(COUNTER_VALUE);
		counter++;
	}


#endif  // modulodigit

#ifdef modulocounter

while(true)
{


#ifdef Testing

	int InputDigits = 2, InputType = 10;


#else

	ModuloNDigit counter;

	int InputDigits = 0, InputType = 0;

	cout << "Please enter the number of digits" << endl;

	InputDigits = counter.getNumOfDigits();

	cout << "Please enter the type type (2/8/10/16) " << endl;


	InputType = counter.getType();


	if((InputType == 0) && (InputDigits == 0))
	{
		cout << "End of Test!!" << endl;
		return 0;
	}


#endif // Testing

	ModuloNCounter m_counter (InputDigits,InputType);

//	for(int i=0; i<100; i++)
//		{
//			m_counter.ModuloCount(0);
//			m_counter.ModuloPrint(InputType);
//		}

	cout << "pre increment" << endl;
	for(int i=0; i<100; i++)
		{
			++m_counter;
			m_counter.ModuloPrint(InputType);
		}

	cout << endl;

	cout << "post increment" << endl;
	for(int i=0; i<100; i++)
		{
			m_counter++.ModuloPrint(InputType);
		}


	std::cout << endl;

}


#endif // modulocounter

	return 0;
}
