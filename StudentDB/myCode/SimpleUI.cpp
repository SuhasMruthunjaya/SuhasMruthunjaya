/*
 * SimpleUI.cpp
 *
 *  Created on: 16 Jan 2024
 *      Author: suhas
 */

#include "SimpleUI.h"
#include <iostream>
#include <sstream>
#include "Poco/Data/Time.h"
#include <fstream>

#include <boost/asio.hpp>
#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/json_parser.hpp"

#include "ReadFromServer.h"

using namespace boost::asio;
using namespace boost::property_tree;


using namespace std;


/**
 * @brief Constructor for the SimpleUI class.
 * @param db Reference to the Student Database instance.
 */
SimpleUI::SimpleUI(StudentDb& db)
{
	this->studentdb = &db;
}

/**
 * @brief Converts numeric input to the corresponding user_options enumeration.
 * @param user_input The user's numeric input.
 * @return SimpleUI::user_options The corresponding user option.
 */
SimpleUI::user_options SimpleUI::getUserSelection(unsigned short user_input)
{

	switch(user_input)
	{
	case 1: return AddNewCourse;
	case 2: return ListCourse;
	case 3: return AddNewStudent;
	case 4: return AddEnrollment;
	case 5: return PrintStudent;
	case 6: return SearchStudent;
	case 7: return UpdateStudent;
	case 8: return WritetoFile;
	case 9: return ReadFromFile;
	case 10: return ReadFromServer;
	case 0: return TerminateProgram;
	}

	return NONE;

}
/**
 * @brief Command to add a new course based on user input.
 */
void SimpleUI::AddNewCourseCommand()
{
	int user_selection  = 0;
	int dayInput = 0;
	Poco::DateTime::DaysOfWeek day = Poco::DateTime::DaysOfWeek::SUNDAY;
	Poco::Data::Time starttime, endtime;
	Poco::Data::Date startdate, enddate;

	cout << " Please enter what type of course you want to add: " << endl;
	cout << "1. Weekly Course" << endl;
	cout << "2. Block course" << endl;

	cin >> user_selection;

	if (user_selection == 1)
		AddWeeklyCourseCommand(dayInput, day, starttime, endtime);
	else if(user_selection == 2)
		AddBlockedCourseCommand(startdate, enddate,
				starttime, endtime);

	cout << " Please enter courseKey , title and major and creditPoints "
			"of the course" << endl;
	unsigned int courseKey = 0; std::string title = " ", major = " ";
	float creditPoints;
	cout << "courseKey: ";
	cin >> courseKey;
	cout << "title: ";
	cin >> title;
	cout << "major: ";
	cin >> major;
	cout << "creditPoints: ";
	cin >> creditPoints;


	studentdb->AddCourse(courseKey, title, major, creditPoints, user_selection,
			day, starttime, endtime, startdate, enddate);


}

/**
 * @brief Command to add a blocked course based on user input.
 * @param startdate Reference to the start date.
 * @param enddate Reference to the end date.
 * @param starttime Reference to the start time.
 * @param endtime Reference to the end time.
 */
void SimpleUI::AddBlockedCourseCommand(
		Poco::Data::Date& startdate,
		Poco::Data::Date& enddate,
		Poco::Data::Time& starttime,
		Poco::Data::Time& endtime)
{
	int year, month, date;
	int hour, minute, second;

	cout << " Enter the start date of the Blocked course " << endl;
	cout << " Enter year: " ;
	cin >> year;
	cout << " Enter month: " ;
	cin >> month;
	cout << " Enter date: " ;
	cin >> date;

	startdate.assign(year,month,date);

	cout << " Enter the end date of the Blocked course " << endl;
	cout << " Enter year: " ;
	cin >> year;
	cout << " Enter month: " ;
	cin >> month;
	cout << " Enter date: " ;
	cin >> date;

	enddate.assign(year,month,date);

	cout << " Enter the start time of the Blocked course " << endl;
	cout << " Enter hour: " ;
	cin >> hour;
	cout << " Enter minute: " ;
	cin >> minute;
	cout << " Enter second: " ;
	cin >> second;

	starttime.assign(hour,minute,second);

	cout << " Enter the start time of the Blocked course " << endl;
	cout << " Enter hour: " ;
	cin >> hour;
	cout << " Enter minute: " ;
	cin >> minute;
	cout << " Enter second: " ;
	cin >> second;

	endtime.assign(hour,minute,second);


}
/**
 * @brief Command to add a weekly course based on user input.
 * @param dayInput User input for the day.
 * @param day Reference to the day of the week.
 * @param starttime Reference to the start time.
 * @param endtime Reference to the end time.
 */

void SimpleUI::AddWeeklyCourseCommand(int dayInput,
		Poco::DateTime::DaysOfWeek& day, Poco::Data::Time& starttime,
		Poco::Data::Time& endtime)
{
	char colon1, colon2;
	int hour, minute, second;

	cout << " Please select which day is the course: " << endl;

	cout << "0. Sunday " << endl;
	cout << "1. Monday " << endl;
	cout << "2. Tuesday " << endl;
	cout << "3. Wednesday" << endl;
	cout << "4. Thursday" << endl;
	cout << "5. Friday" << endl;
	cout << "6. Saturday" << endl;


	cin >> dayInput;

	day = dayofweek(dayInput);

	std::string startTime, endTime;

	cout << " Please enter the start Time in the format (hour:minute:sec)"
			<< endl;
	cin >> startTime;

	cout << " Please enter the end Time in the format (hour:minute:sec)"
			<< endl;
	cin >> endTime;

	istringstream iss(startTime), end_iss(endTime);

	iss >> hour >> colon1 >> minute >> colon2 >> second;


	starttime.assign(hour,minute,second);

	end_iss >> hour >> colon1 >> minute >> colon2 >> second;

	endtime.assign(hour, minute, second);


}

/**
 * @brief Converts numeric input to Poco::DateTime::DaysOfWeek.
 * @param dayInput User input for the day.
 * @return Poco::DateTime::DaysOfWeek The corresponding day of the week.
 */
Poco::DateTime::DaysOfWeek SimpleUI::dayofweek(int dayInput)
{
	switch(dayInput)
	{
	case 0: return Poco::DateTime::DaysOfWeek::SUNDAY;
	case 1: return Poco::DateTime::DaysOfWeek::MONDAY;
	case 2: return Poco::DateTime::DaysOfWeek::TUESDAY;
	case 3: return Poco::DateTime::DaysOfWeek::WEDNESDAY;
	case 4: return Poco::DateTime::DaysOfWeek::THURSDAY;
	case 5: return Poco::DateTime::DaysOfWeek::FRIDAY;
	case 6: return Poco::DateTime::DaysOfWeek::SATURDAY;
	}

	return Poco::DateTime::DaysOfWeek::SUNDAY;
}
/**
 * @brief Command to list all courses in the database.
 */
void SimpleUI::ListCourseCommand()
{

	const auto& courses  = studentdb->getCourses();

	cout << endl;
	cout << " The list of Courses: " << endl;
	for( auto const& element : courses)
	{
		element.second->print(cout);
		cout << endl;
		cout << endl;
	}
	cout << endl;
}
/**
 * @brief Command to add a new student based on user input.
 */
void SimpleUI::AddNewStudentCommand()
{
	std::string firstName = " ", lastName = " ", street = " ", cityName = " ",
			additionalInfo = " ";

	unsigned short postalCode = 0;
	std::cin.ignore();

	cout << " Give the necessary details to create a new Student in database:"
			"" << endl;

	cout << "Enter the first name of the student: ";
	std::getline(std::cin, firstName);
	cout << "Enter the last name of the Student:  ";
	std::getline(std::cin, lastName);

	std::string input;
	int year, month, date;
	char dash1 , dash2;

	cout << " Enter the dob (YYYY - MM - DD) format" << endl;
	cin >> input;

	std::cin.ignore();
	cout << "Enter the street:  ";
	std::getline(std::cin, street);

	cout << "Enter the postalCode: ";
	cin >> postalCode;

	cout << "Enter the city name:  ";
	cin >> cityName;

	std::cin.ignore();
	cout << "Enter any additional Info:  ";
	std::getline(std::cin, additionalInfo);


	if(isValidDate(input))
	{
		istringstream iss(input);

		iss >> year >> dash1 >> month >> dash2 >> date;

		Poco::Data::Date dob(year,month,date);

		studentdb->AddStudent(firstName,lastName,dob,street,postalCode,
				cityName,additionalInfo);

	}
	else
	{
		cout << " The date which is entered is invalid" << endl;
	}



}
/**
 * @brief Validates the format of a date string.
 * @param dob Date of birth string.
 * @return bool True if the date is valid, false otherwise.
 */
bool SimpleUI::isValidDate(std::string dob)
{
	int year, month, date;
	char dash1 , dash2;

	istringstream iss(dob);

	if(iss >> year >> dash1 >> month >> dash2 >> date)
	{
		if(iss.eof() && dash1 == '-' && dash2 == '-')
		{
			if(year > 0 && month > 0 && month <= 12 && date > 0 && date <= 31)
			{
				return true;
			}
		}
	}

	return false;

}

/**
 * @brief Command to add a new enrollment based on user input.
 */
void SimpleUI::AddNewEnrollmentCommand()
{
	unsigned int matriculationNum, courseKey ;
	std::string semester;

	cout << " Please enter the matriculation number of the student " << endl;
	cin >> matriculationNum;

	cout << " Please enter the CourseKey" << endl;
	cin >> courseKey;

	cout << " Please enter the Semester" << endl;
	cin >> semester;

	bool result = studentdb->AddEnrollment(matriculationNum, courseKey,
			semester);

	if(!result)
		std::cerr << "The Enrollment already exists" << std::endl;

}

/**
 * @brief Command to print details of a specific student based on user input.
 */
void SimpleUI::PrintStudentCommand()
{
	unsigned int matrikel_Number;
	cout << " Please enter the matrikel Number:  " << endl;
	cin >> matrikel_Number;

	auto& students = studentdb->getStudents();

	const auto& itt = students.find(matrikel_Number);

	cout << " The Student Details of " << matrikel_Number  << ": "<< endl;
	if(itt != students.end())
	{
		cout << " First_Name: " << itt->second.getFirstName() << endl;
		cout << " Last_Name: " << itt->second.getLastName() << endl;
		cout << " date Of Birth: " << itt->second.getDateOfBirth().day()
									 << "-" << itt->second.getDateOfBirth().month() << "-"
									 << itt->second.getDateOfBirth().year() << endl;
		cout << " street: " << itt->second.getAddress().getStreet() << endl;
		cout << " postalCode: " << itt->second.getAddress().getPostalCode()
									 << endl;
		cout << " cityName: " << itt->second.getAddress().getCityName() << endl;

		auto const& enrollments = itt->second.getEnrollments();

		cout << " Enrollments: " << endl;
		for( const auto& element : enrollments)
		{
			cout << " courseKey: " << element.getCourse()->getCourseKey()
																					<< endl;
			cout << " course title: " << element.getCourse()->getTitle()
																					<< endl;
			cout << " course Major: " << element.getCourse()->getMajor()
																					<< endl;
			cout << " creditPoints: " << element.getCourse()->getCreditPoints()
																							<< endl;

			cout << " semester: " << element.getSemester() << endl;
			cout << " grade: " << element.getGrade() << endl;
		}

	}



}

/**
 * @brief Command to search for students based on user input.
 */
void SimpleUI::SearchStudentCommand()
{
	std::string user_input;
	cout << " Enter the name or a part of a name of the student you want "
			"to search" << endl;


	cin >> user_input;

	const auto& students = studentdb->getStudents();

	for( const auto& element : students)
	{
		std::string firstName = element.second.getFirstName();
		std::string lastName = element.second.getLastName();

		std::string::size_type n;
		std::string::size_type m;

		n = firstName.find(user_input);
		if(n != std::string::npos)
		{
			cout << " Matrikel Number: " << element.second.getMatrikelNumber()
																							<< endl;
			cout << " firtName: " << element.second.getFirstName() << endl;
			cout << " lastName: " << element.second.getLastName() << endl;

		}
		else
		{
			m = lastName.find(user_input);
			if(m != std::string::npos)
			{
				cout << " Matrikel Number: "
						<< element.second.getMatrikelNumber() << endl;
				cout << " firtName: " << element.second.getFirstName() << endl;
				cout << " lastName: " << element.second.getLastName() << endl;

			}

		}
	}

}

/**
 * @brief Command to update student properties based on user input.
 */
void SimpleUI::UpdateStudentCommand()
{
	cout << "Please enter the matrikel Number of the student" << endl;

	unsigned int matrikelNum;

	cin >> matrikelNum;

	//std::map<int, Student>::iterator itt = studentdb->findStudent(matrikelNum);

	const auto& students = studentdb->getStudents();

	auto const& itt = students.find(matrikelNum);

	if( itt != students.end())
	{

		cout << " The Student Details of " << matrikelNum  << ": "<< endl;

		cout << "1. First_Name: " << itt->second.getFirstName() << endl;
		cout << "2. Last_Name: " << itt->second.getLastName() << endl;
		cout << "3. date Of Birth: " << itt->second.getDateOfBirth().day()
									<< "-" << itt->second.getDateOfBirth().month() << "-" <<
									itt->second.getDateOfBirth().year() << endl;
		cout << "4. Address: street:"
				<< itt->second.getAddress().getStreet() << " postalCode: "
				<< itt->second.getAddress().getPostalCode() << "cityName: "
				<< itt->second.getAddress().getCityName() << endl;

		auto const& enrollments = itt->second.getEnrollments();

		cout << "5. Enrollments: " << endl;
		for( const auto& element : enrollments)
		{
			cout << " courseKey: " << element.getCourse()->getCourseKey()
																						<< endl;
			cout << " course title: " << element.getCourse()->getTitle()
																						<< endl;
			cout << " course Major: " << element.getCourse()->getMajor()
																						<< endl;
			cout << " creditPoints: "
					<< element.getCourse()->getCreditPoints() << endl;

			cout << " semester: " << element.getSemester() << endl;
			cout << " grade: " << element.getGrade() << endl;
		}

		cout << "Press 0 to terminate" << endl;


		cout << " Enter the number of the corresponding parameter you "
				"want to Update" << endl;

		int userChoice;
		cin >> userChoice;

		UpdateStudentProperties(userChoice, matrikelNum);


	}
	else
	{
		cout << " No student Found in the database !!!!!" << endl;
	}




}

/**
 * @brief Updates specific properties of a student based on user input.
 * @param userChoice User's choice for updating.
 * @param matrikelNum Matrikel number of the student.
 */
void SimpleUI::UpdateStudentProperties(int userChoice,
		unsigned int matrikelNum)
{
	switch(userChoice)
	{
	case 1:
	{
		std::string first_name;
		cout << " Please enter the updated first name" << endl;
		cin >> first_name;

		studentdb->StudentFirstNameUpdate(matrikelNum, first_name);

		break;

	}
	case 2:
	{
		std::string last_name;
		cout << " Please enter the updated last name" << endl;
		cin >> last_name;

		studentdb->StudentLastNameUpdate(matrikelNum, last_name);

		break;
	}
	case 3:
	{
		std::string dob;

		cout << " Please enter the updated dob in the format"
				"(YYYY-MM-DD)" << endl;
		cin >> dob;

		studentdb->StudentDobUpdate(matrikelNum, dob);

		break;
	}
	case 4:
	{
		unsigned short postalCode;
		std::string street, city;

		cout << " Please enter the updated Address: " << endl;

		cout << "street:  " ;
		cin >> street;

		cout << "city: ";
		cin >> city;

		cout << "postalCode: ";
		cin >> postalCode;

		studentdb->StudentAddressUpdate(matrikelNum, street, postalCode,city);

		break;
	}
	case 5:
	{
		int input, operationInput;
		float grade;
		cout << " Select which enrollment to Update " << endl;
		cin >> input;

		cout << "Select what you want to do:" << endl;
		cout << " 1. Remove the selected enrollment " << endl;
		cout << " 2. Set Grade of the selected enrollment" << endl;

		cin >> operationInput;

		if(operationInput == 2)
		{
			cout << " Please enter the Updated Grade: " << endl;
			cin >> grade;
		}

		studentdb->StudentEnrollmentUpdate(matrikelNum, input, operationInput,
				grade);

		break;
	}
	case 0:
	{
		break;
	}

	}

}

/**
 * @brief Command to write the database to a file based on user input.
 */
void SimpleUI::WritetoFileCommand()
{
	cout << " Please enter the file name" << endl;
	std::string filename;

	cin >> filename;

	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	std::fstream file(filename, file.trunc | file.out);


	if (!file.is_open()) {
		std::cout << "failed to open " << filename << '\n';
	} else {

		studentdb->write(file);

	}

	file.close();


}

/**
 * @brief Command to read data from a file based on user input.
 */
void SimpleUI::ReadFromFileCommand()
{
	cout << "Please enter the file path to read the data from" << endl;
	std::string filepath;

	std::cin.ignore();

	std::getline(std::cin, filepath);

	std::fstream file(filepath,file.in);

	if (!file.is_open()) {
		std::cout << "failed to open " << filepath << '\n';
	} else {

		studentdb->read(file);

	}

	file.close();

}

/**
 * @brief Command to read data from a server based on user input.
 */
void SimpleUI::ReadFromServerCommand()
{
	cout << " Please enter the number of students records to be "
			"created" << endl;

	int numOfStudents;

	cin >> numOfStudents;

	for(int i = 0; i < numOfStudents; i++)
	{



		try
		{
			ptree pt =
					ReadFromServer::readServer("www.hhs.users.h-da.cloud","4242");
			studentdb->getFromPtree(pt);
		}
		catch(const std::exception& e){
			cout << e.what()<< endl;
			++numOfStudents;
		}


	}


}

/**
 * @brief Runs the SimpleUI interface.
 */
void SimpleUI::run()
{
	while(true)
	{
		int user_input;

		cout << " Choose what you want to do" << endl;
		cout << "1. Add new Course" << endl;
		cout << "2. List Courses" << endl;
		cout << "3. Add new Student" << endl;
		cout << "4. Add new Enrollment" << endl;
		cout << "5. Print Students" << endl;
		cout << "6. Search students" << endl;
		cout << "7. Update student properties" << endl;
		cout << "8. Write to File" << endl;
		cout << "9. Read from File" << endl;
		cout << "10.Read from server" << endl;
		cout << "0. Press 0 to terminate the program" << endl;

		cin >> user_input;

		user_options userSelection  = getUserSelection(user_input);

		if(userSelection == TerminateProgram)
		{
			break;
		}

		switch(userSelection)
		{
		case AddNewCourse:
		{
			AddNewCourseCommand();
			break;
		}

		case ListCourse:
		{
			ListCourseCommand();
			break;
		}
		case AddNewStudent:
		{
			AddNewStudentCommand();
			break;
		}
		case AddEnrollment:
		{
			AddNewEnrollmentCommand();
			break;
		}
		case PrintStudent:
		{
			PrintStudentCommand();
			break;
		}
		case SearchStudent:
		{
			SearchStudentCommand();
			break;
		}
		case UpdateStudent:
		{
			UpdateStudentCommand();
			break;
		}
		case WritetoFile:
		{
			WritetoFileCommand();
			break;
		}
		case ReadFromFile:
		{
			ReadFromFileCommand();
			break;
		}
		case ReadFromServer:
		{
			ReadFromServerCommand();
			break;
		}
		case TerminateProgram:
			break;
		case NONE:
			break;

		}
	}

}
