// Standard (system) header files
#include <iostream>
#include <cstdlib>
// Add more standard header files as required
// #include <string>

using namespace std;

// Add your project's header files here
#include "SimpleUI.h"
#include "StudentDb.h"

// Main program
int main ()
{

	cout << "StudentDB started." << endl << endl;

		StudentDb database;

		SimpleUI UI(database);
		UI.run();

	return 0;
}
