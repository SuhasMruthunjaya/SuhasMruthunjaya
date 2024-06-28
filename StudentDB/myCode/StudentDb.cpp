/*
 * StudentDb.cpp
 *
 *  Created on: 16 Jan 2024
 *      Author: suhas
 */

#include "StudentDb.h"
#include <sstream>
#include <fstream>
#include <string>
#include <boost/asio.hpp>
#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/json_parser.hpp"


//StudentDb Constructor
StudentDb::StudentDb()
{

}

//StudentDb Destructor
StudentDb::~StudentDb()
{

}

// Method to add a course to the database
void StudentDb::AddCourse(unsigned int courseKey, std::string title,
		std::string major, float creditPoints, int user_selection,
		Poco::DateTime::DaysOfWeek day, Poco::Data::Time starttime,
		Poco::Data::Time endtime, Poco::Data::Date startdate,
		Poco::Data::Date enddate)
{

	if(user_selection == 1)
	{
		std::unique_ptr<const Course> course_ptr = std::unique_ptr<const Course>
		(new WeeklyCourse(courseKey,
				title, major, creditPoints, day, starttime, endtime));

		courses[courseKey] = std::move(course_ptr);
	}
	else if(user_selection == 2)
	{
		std::unique_ptr<const Course> course_ptr(new BlockCourse(courseKey,
				title, major, creditPoints, startdate, enddate,
				starttime, endtime));

		courses[courseKey] = std::move(course_ptr);

	}

}

// Method to add a student to the database
void StudentDb::AddStudent(std::string firstName, std::string lastName,
		Poco::Data::Date dateOfBirth, std::string street,
		unsigned short postalCode, std::string cityName,
		std::string additionalInfo)
{

	Student student(firstName, lastName, dateOfBirth, street, postalCode,cityName,
			additionalInfo);

	students.insert({student.getMatrikelNumber(), student});

}

// Getter for the courses map
const std::map<int, std::unique_ptr<const Course> >& StudentDb::getCourses()
const
{
	return courses;
}

// Getter for the students map
const std::map<int, Student>& StudentDb::getStudents() const
{
	return students;
}

// Method to add an enrollment for a student in a course
bool StudentDb::AddEnrollment(unsigned int matriculationNum,
		unsigned int coursekey, std::string semester)
{
	bool result = false;

	const auto& itt = students.find(matriculationNum);

	if( itt !=  students.end())
	{
		const auto& iterator = courses.find(coursekey);

		if(iterator != courses.end() )
		{
			// student and course both present
			const Course* course = &(*iterator->second);

			result = itt->second.AddEnrollment(course,semester);

		}

	}

	return result;
}
/**
 * @brief Updates the first name of a student.
 * @param matrikelNum The matrikel number of the student.
 * @param first_name The new first name.
 */
void StudentDb::StudentFirstNameUpdate(unsigned int matrikelNum,
		std::string first_name)
{

	auto it = students.find(matrikelNum);

	if(it != students.end())
	{
		it->second.setFirstName(first_name);
	}
}
/**
 * @brief Updates the last name of a student.
 * @param matrikelNum The matrikel number of the student.
 * @param last_name The new last name.
 */
void StudentDb::StudentLastNameUpdate(unsigned int matrikelNum,
		std::string last_name)
{
	auto it = students.find(matrikelNum);

	if(it != students.end())
	{
		it->second.setLastName(last_name);
	}

}
/**
 * @brief Updates the date of birth of a student.
 * @param matrikelNum The matrikel number of the student.
 * @param dob The new date of birth in the format "YYYY-MM-DD".
 */
void StudentDb::StudentDobUpdate(unsigned int matrikelNum, std::string dob)
{
	auto it = students.find(matrikelNum);

	if(it != students.end())
	{
		int year, month, date;
		char dash1 , dash2;

		std::istringstream iss(dob);

		iss >> year >> dash1 >> month >> dash2 >> date;

		Poco::Data::Date obj(year, month, date);

		it->second.setDateOfBirth(obj);

	}

}
/**
 * @brief Updates the address of a student.
 * @param matrikelNum The matrikel number of the student.
 * @param street The new street address.
 * @param PostalCode The new postal code.
 * @param city The new city name.
 */
void StudentDb::StudentAddressUpdate(unsigned int matrikelNum,
		std::string street, unsigned short PostalCode, std::string city)
{
	auto it = students.find(matrikelNum);

	if(it != students.end())
	{
		it->second.setAddress(street,PostalCode,city);

	}

}
/**
 * @brief Updates an enrollment for a student (e.g., remove or update the grade).
 * @param matrikelNum The matrikel number of the student.
 * @param pos The position of the enrollment in the student's record.
 * @param operation The operation to be performed (1 for remove, 2 for update).
 * @param grade The new grade (applicable for the update operation).
 */
void StudentDb::StudentEnrollmentUpdate(unsigned int matrikelNum, int pos,
		int operation, float grade)
{
	auto it = students.find(matrikelNum);

	if(it != students.end())
	{
		it->second.setEnrollment(pos, operation, grade);
	}

}
// Method to write the database details to an output stream

void StudentDb::write(std::ostream &out)
{
	out << courses.size();
	out << std::endl;

	for(auto const& element : courses)
	{
		element.second->write(out);
		out << std::endl;
	}

	out << students.size();
	out << std::endl;

	for(auto const& student : students)
	{
		student.second.write(out);
		out << std::endl;
	}

	for(auto const& _student : students)
	{
		out << _student.second.getEnrollments().size();
		out << std::endl;

		for(auto const& enrollment : _student.second.getEnrollments())
		{
			out << _student.second.getMatrikelNumber() << ";";
			enrollment.write(out);

			out << std::endl;

		}
	}


}

// Method to read the database details from an input stream
void StudentDb::read(std::istream &in)
{
	students.clear();

	courses.clear();

	std::string count;

	in >> count;

	in.ignore();

	for ( int i = 0; i < std::stoi(count); i++)
	{
		std::string course_type ;
		std::getline(in, course_type, ';');

		if(course_type == "W")
		{
			std::unique_ptr<const Course> course_ptr =  WeeklyCourse::read(in);

			courses[course_ptr->getCourseKey()] = std::move(course_ptr);

		}
		else if(course_type == "B")
		{


			std::unique_ptr<const Course> course_ptr = BlockCourse::read(in);

			courses[course_ptr->getCourseKey()] = std::move(course_ptr);

		}
	}

	std::string studentCount;

	std::getline(in, studentCount);


	for(int i = 0; i < std::stoi(studentCount) ; i++)
	{

		Student student = Student::read(in);

		students.insert({student.getMatrikelNumber(), student});
	}

	unsigned int new_nextMatrikelNumber = std::prev(students.end())->first;

	std::prev(students.end())->
			second.setNextMatrikelNumber(++new_nextMatrikelNumber);


	std::string enrollment_count;

	while(std::getline(in,enrollment_count))
	{
		for(int i = 0; i < std::stoi(enrollment_count) ; i++)
		{
			std::string matrikNum_str;
			std::getline(in, matrikNum_str, ';');
			unsigned int matrik_num = std::stoi(matrikNum_str);


			auto it = students.find(matrik_num);

			if(it != students.end())
			{

				auto const& course_map = getCourses();

				it->second.AddEnrollment(Enrollment::read(in, course_map));
			}
		}
	}
}

// Method to populate the database from a property tree
void StudentDb::getFromPtree(boost::property_tree::ptree& pt)
{
	try
	{
		std::string firstName = pt.get<std::string>("name.firstName");
		std::string lastName = pt.get<std::string>("name.lastName");
		int date = pt.get<int>("dateOfBirth.date");
		int month = pt.get<int>("dateOfBirth.month");
		int year = pt.get<int>("dateOfBirth.year");
		std::string street = pt.get<std::string>("location.street");
		std::string postalCodeStr =
				pt.get<std::string>("location.postCode");
		unsigned short postalCode = std::stoi(postalCodeStr);
		std::string cityName = pt.get<std::string>("location.city");
		std::string addInfo = pt.get<std::string>("location.state");
		Poco::Data::Date dob(year,month,date);
		AddStudent(firstName, lastName, dob , street, postalCode,
				cityName,addInfo);
	}
	catch(std::exception& e)
	{
		throw std::runtime_error("Invalid Inputs, taking another "
				"student detail10");
	}

}
