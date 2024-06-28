// Standard (system) header files
#include <iostream>
//#include <cstdlib>
// Add more standard header files as required
// #include <string>

using namespace std;

// Add your project's header files here
#include "PulseSequenceParser.h"
#include "XmlPulseParser.h"

// Main program
int main ()
{
    // TODO: Add your program code here
	cout << "PulseParser started." << endl << endl;

    PulseSequenceParser* newDoc = new XmlPulseParser("C:/QT_Projects/PulseSequenceParser/Bell.xml");

    newDoc->parseDoc();


	return 0;
}
