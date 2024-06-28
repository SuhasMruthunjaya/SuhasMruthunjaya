/*
 * StudentDb.h
 *
 *  Created on: 16 Jan 2024
 *      Author: suhas
 */

#ifndef STUDENTDB_H_
#define STUDENTDB_H_

#include <map>
#include <memory>
#include "Student.h"
#include "Course.h"
#include "WeeklyCourse.h"
#include "BlockCourse.h"

#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/json_parser.hpp"


class StudentDb
{

private:
	// Map to store students using their matrikel number as the key
	std::map<int, Student> students;
	// Map to store courses using their course key as the key
	std::map<int, std::unique_ptr<const Course>> courses;


public:
	StudentDb();
	virtual ~StudentDb();

	// Method to add a course to the database
	void AddCourse(unsigned int courseKey, std::string title, std::string major,
			float creditPoints, int user_selection,
			Poco::DateTime::DaysOfWeek day,Poco::Data::Time starttime,
			Poco::Data::Time endtime, Poco::Data::Date startdate,
			Poco::Data::Date enddate);

	// Getter for the courses map
	const std::map<int, std::unique_ptr<const Course>>& getCourses() const;

	// Method to add a student to the database
	void AddStudent(std::string firstName, std::string lastName,
			Poco::Data::Date dateOfBirth,
			std::string street, unsigned short postalCode, std::string cityName,
			std::string additionalInfo);

	// Getter for the students map
	const std::map<int, Student>& getStudents() const;

	// Method to add an enrollment for a student in a course
	bool AddEnrollment(unsigned int matriculationNum, unsigned int coursekey,
			std::string semester);

	// Update Methods

	/**
	 * @brief Updates the first name of a student.
	 * @param matrikelNum The matrikel number of the student.
	 * @param first_name The new first name.
	 */
	void StudentFirstNameUpdate(unsigned int matrikelNum,
			std::string first_name);



	/**
	 * @brief Updates the last name of a student.
	 * @param matrikelNum The matrikel number of the student.
	 * @param last_name The new last name.
	 */
	void StudentLastNameUpdate(unsigned int matrikelNum, std::string last_name);

	/**
	 * @brief Updates the date of birth of a student.
	 * @param matrikelNum The matrikel number of the student.
	 * @param dob The new date of birth in the format "YYYY-MM-DD".
	 */
	void StudentDobUpdate(unsigned int matrikelNum, std::string dob);

	/**
	 * @brief Updates the address of a student.
	 * @param matrikelNum The matrikel number of the student.
	 * @param street The new street address.
	 * @param PostalCode The new postal code.
	 * @param city The new city name.
	 */
	void StudentAddressUpdate(unsigned int matrikelNum,
			std::string street, unsigned short PostalCode,
			std::string city);

	/**
	 * @brief Updates an enrollment for a student (e.g., remove or
	 * update the grade).
	 * @param matrikelNum The matrikel number of the student.
	 * @param pos The position of the enrollment in the student's record.
	 * @param operation The operation to be performed (1 for remove,
	 * 2 for update).
	 * @param grade The new grade (applicable for the update operation).
	 */
	void StudentEnrollmentUpdate(unsigned int matrikelNum, int pos,
			int operation, float grade);

	// Method to write the database details to an output stream

	void write(std::ostream& out);

	// Method to read the database details from an input stream

	void read(std::istream& in);

	// Method to populate the database from a property tree

	void getFromPtree(boost::property_tree::ptree& pt);


};


#endif /* STUDENTDB_H_ */
