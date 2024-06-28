/*
 * Student.cpp
 *
 *  Created on: 16 Jan 2024
 *      Author: suhas
 */

#include "Student.h"
#include <fstream>


unsigned int Student::nextMatrikelNumber = 100000;

// Constructor to initialize a student with basic details
Student::Student(std::string firstName, std::string lastName,
		Poco::Data::Date dateOfBirth, std::string street,
		unsigned short postalCode, std::string cityName,
		std::string additionalInfo): firstName(firstName), lastName(lastName),
				address(street,postalCode, cityName,additionalInfo),
				dateOfBirth(dateOfBirth)
{
	this->matrikelNumber = nextMatrikelNumber;

	nextMatrikelNumber ++;

}

/**
 * @brief Gets the matrikel number of the student.
 * @return unsigned int The matrikel number.
 */
const unsigned int Student::getMatrikelNumber() const
{
	return matrikelNumber;
}

Student::~Student()
{

}

/**
 * @brief Gets the address of the student.
 * @return const Address& Reference to the Address object.
 */
const Address& Student::getAddress() const
{
	return address;
}
/**
 * @brief Gets the date of birth of the student.
 * @return const Poco::Data::Date& Reference to the Date object.
 */
const Poco::Data::Date& Student::getDateOfBirth() const
{
	return dateOfBirth;
}
/**
 * @brief Gets the enrollments of the student.
 * @return const std::vector<Enrollment>& Reference to the
 * vector of enrollments.
 */
const std::vector<Enrollment>& Student::getEnrollments() const
{
	return enrollments;
}
/**
 * @brief Gets the first name of the student.
 * @return const std::string& Reference to the first name.
 */
const std::string& Student::getFirstName() const
{
	return firstName;
}
/**
 * @brief Gets the last name of the student.
 * @return const std::string& Reference to the last name.
 */
const std::string& Student::getLastName() const
{
	return lastName;
}
/**
 * @brief Adds a new enrollment for the student.
 * @param course Pointer to the Course object.
 * @param semester The semester of the enrollment.
 * @return bool True if the enrollment is added successfully, false otherwise.
 */
bool Student::AddEnrollment(const Course* course, std::string semester)
{
	for( auto const& element : enrollments)
	{
		if(element.getCourse()->getCourseKey() == course->getCourseKey())
		{
			return false;
		}
	}

	enrollments.push_back(Enrollment(course, semester));
	return true;
}
/**
 * @brief Sets the first name of the student.
 * @param firstName The new first name.
 */
void Student::setFirstName(const std::string &firstName)
{
	this->firstName = firstName;
}
/**
 * @brief Sets the address of the student.
 * @param street The street address.
 * @param PostalCode The postal code.
 * @param city The city name.
 */
void Student::setAddress(
		std::string street, unsigned short PostalCode, std::string city)
{
	this->address = Address(street, PostalCode, city);
}
/**
 * @brief Sets the date of birth of the student.
 * @param dateOfBirth The new date of birth.
 */
void Student::setDateOfBirth(const Poco::Data::Date &dateOfBirth)
{
	this->dateOfBirth = dateOfBirth;
}
/**
 * @brief Sets the last name of the student.
 * @param lastName The new last name.
 */
void Student::setLastName(const std::string &lastName)
{
	this->lastName = lastName;
}
/**
 * @brief Modifies specific properties of an enrollment
 * (e.g., removes or updates the grade).
 * @param pos The position of the enrollment in the vector.
 * @param operation The operation to be performed
 * (1 for remove, 2 for update).
 * @param grade The new grade (applicable for the update operation).
 */
void Student::setEnrollment(int pos, int operation, float grade)
{
	if(operation == 1)
	{
		enrollments.erase(enrollments.begin() + ( pos - 1 ));
	}
	else if(operation == 2)
	{
		enrollments[pos - 1].setGrade(grade);
	}
}
/**
 * @brief Writes the student details to an output stream.
 * @param out The output stream.
 */
void Student::write(std::ostream &out) const
{
	out << std::to_string(matrikelNumber)<< ";" << firstName << ";" << lastName
			<< ";"
			<< std::to_string(dateOfBirth.day()) << "." <<
			std::to_string(dateOfBirth.month()) << "."
			<< std::to_string(dateOfBirth.year()) << ";" <<
			address.getStreet() << ";"
			<< std::to_string(address.getPostalCode()) << ";" <<
			address.getCityName()
			<< ";" << address.getAdditionalInfo();

}
/**
 * @brief Adds an enrollment object directly to the student's record.
 * @param enrollment The Enrollment object to be added.
 */
void Student::AddEnrollment(Enrollment enrollment)
{
	enrollments.push_back(enrollment);
}
/**
 * @brief Gets the next available matrikel number.
 * @return unsigned int The next matrikel number.
 */
unsigned int Student::getNextMatrikelNumber()
{
	return nextMatrikelNumber;
}
/**
 * @brief Sets the next available matrikel number.
 * @param nextMatrikelNumber The new next matrikel number.
 */
void Student::setNextMatrikelNumber(unsigned int nextMatrikelNumber)
{
	this->nextMatrikelNumber = nextMatrikelNumber;
}

/**
 * @brief Sets the matrikel number of the student.
 * @param matrikelNumber The new matrikel number.
 */
void Student::setMatrikelNumber(unsigned int matrikelNumber)
{
	this->matrikelNumber = matrikelNumber;
}
/**
 * @brief Reads a Student object from an input stream.
 * @param in The input stream.
 * @return Student The read Student object.
 */

Student Student::read(std::istream &in)
{

	std::string matrikelNum_str;
	std::getline(in,matrikelNum_str, ';');
	unsigned int matrikelNum = stoi(matrikelNum_str);


	std::string firstName;
	std::getline(in,firstName,';');

	std::string lastName;
	std::getline(in,lastName,';');

	std::string dob_date;
	std::getline(in,dob_date,'.');
	int date = stoi(dob_date);

	std::string dob_month;
	std::getline(in,dob_month,'.');
	int month = stoi(dob_month);

	std::string dob_year;
	std::getline(in,dob_year,';');
	int year = stoi(dob_year);

	Address add = Address::read(in);

	std::string street = add.getStreet();
	unsigned short postalCode = add.getPostalCode();
	std::string cityName = add.getCityName();
	std::string addnInfo = add.getAdditionalInfo();

	Student student(firstName,lastName,Poco::Data::Date(year,month,date),
			street,postalCode,cityName,addnInfo);


	student.setMatrikelNumber(matrikelNum);

	return student;


}
