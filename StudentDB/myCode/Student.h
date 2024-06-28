/*
 * Student.h
 *
 *  Created on: 16 Jan 2024
 *      Author: suhas
 */

#ifndef STUDENT_H_
#define STUDENT_H_

#include <string>
#include "Poco/Data/Date.h"
#include "Address.h"
#include "Enrollment.h"
#include <vector>

class Student
{
private:

	// Static member to track the next available matrikelNumber
	static unsigned int nextMatrikelNumber ;

	// Member variables for student details
	unsigned int matrikelNumber;
	std::string firstName;
	std::string lastName;
	Address address;

	Poco::Data::Date dateOfBirth;
	std::vector <Enrollment> enrollments;



public:
	// Constructor to initialize a student with basic details
	Student(std::string firstName, std::string lastName,
			Poco::Data::Date dateOfBirth,
			std::string street, unsigned short postalCode, std::string cityName,
			std::string additionalInfo = "NaN");

	// Destructor to clean up resources if needed
	virtual ~Student();

	/**
	 * @brief Gets the matrikel number of the student.
	 * @return unsigned int The matrikel number.
	 */
	const unsigned int getMatrikelNumber() const;

	/**
	 * @brief Adds a new enrollment for the student.
	 * @param course Pointer to the Course object.
	 * @param semester The semester of the enrollment.
	 * @return bool True if the enrollment is added successfully, false otherwise.
	 */
	bool AddEnrollment (const Course* course, std::string semester);

	/**
	 * @brief Adds an enrollment object directly to the student's record.
	 * @param enrollment The Enrollment object to be added.
	 */
	void AddEnrollment(Enrollment enrollment);


	/**
	 * @brief Gets the address of the student.
	 * @return const Address& Reference to the Address object.
	 */
	const Address& getAddress() const;

	/**
	 * @brief Gets the date of birth of the student.
	 * @return const Poco::Data::Date& Reference to the Date object.
	 */
	const Poco::Data::Date& getDateOfBirth() const;

	/**
	 * @brief Gets the enrollments of the student.
	 * @return const std::vector<Enrollment>& Reference to the
	 * vector of enrollments.
	 */
	const std::vector<Enrollment>& getEnrollments() const;

	/**
	 * @brief Gets the first name of the student.
	 * @return const std::string& Reference to the first name.
	 */
	const std::string& getFirstName() const;

	/**
	 * @brief Gets the last name of the student.
	 * @return const std::string& Reference to the last name.
	 */
	const std::string& getLastName() const;

	/**
	 * @brief Sets the first name of the student.
	 * @param firstName The new first name.
	 */
	void setFirstName(const std::string &firstName);

	/**
	 * @brief Sets the address of the student.
	 * @param street The street address.
	 * @param PostalCode The postal code.
	 * @param city The city name.
	 */
	void setAddress(
			std::string street, unsigned short PostalCode, std::string city);

	/**
	 * @brief Sets the date of birth of the student.
	 * @param dateOfBirth The new date of birth.
	 */
	void setDateOfBirth(const Poco::Data::Date &dateOfBirth);

	/**
	 * @brief Sets the last name of the student.
	 * @param lastName The new last name.
	 */
	void setLastName(const std::string &lastName);

	/**
	 * @brief Modifies specific properties of an enrollment
	 * (e.g., removes or updates the grade).
	 * @param pos The position of the enrollment in the vector.
	 * @param operation The operation to be performed
	 * (1 for remove, 2 for update).
	 * @param grade The new grade (applicable for the update operation).
	 */
	void setEnrollment(int pos, int operation, float grade);
	/**
	 * @brief Writes the student details to an output stream.
	 * @param out The output stream.
	 */

	void write(std::ostream& out) const;

	/**
	 * @brief Reads a Student object from an input stream.
	 * @param in The input stream.
	 * @return Student The read Student object.
	 */
	static Student read(std::istream& in);

	/**
	 * @brief Sets the matrikel number of the student.
	 * @param matrikelNumber The new matrikel number.
	 */
	void setMatrikelNumber(unsigned int matrikelNumber);

	/**
	 * @brief Sets the next available matrikel number.
	 * @param nextMatrikelNumber The new next matrikel number.
	 */
	void setNextMatrikelNumber(unsigned int nextMatrikelNumber);

	/**
	 * @brief Gets the next available matrikel number.
	 * @return unsigned int The next matrikel number.
	 */
	unsigned int getNextMatrikelNumber();
};

#endif /* STUDENT_H_ */
