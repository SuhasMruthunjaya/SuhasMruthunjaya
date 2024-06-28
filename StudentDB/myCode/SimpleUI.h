/*
 * SimpleUI.h
 *
 *  Created on: 16 Jan 2024
 *      Author: suhas
 */

#ifndef SIMPLEUI_H_
#define SIMPLEUI_H_

#include "StudentDb.h"

/**
 * @class SimpleUI
 * @brief Provides a simple user interface for interacting with the Student
 * Database.
 */
class SimpleUI
{
public:
	/**
	 * @brief Enumeration of user options for the SimpleUI.
	 */
	typedef enum{
		AddNewCourse,
		ListCourse,
		AddNewStudent,
		AddEnrollment,
		PrintStudent,
		SearchStudent,
		UpdateStudent,
		WritetoFile,
		ReadFromFile,
		ReadFromServer,
		TerminateProgram,
		NONE
	}user_options;

private:
	StudentDb* studentdb;	// Pointer to the Student Database instance

	/**
	 * @brief Converts user input to the corresponding user_options enumeration.
	 * @param user_input The user's numeric input.
	 * @return user_options The corresponding user option.
	 */
	user_options getUserSelection (unsigned short user_input);

	/**
	 * @brief Command to add a new course based on user input.
	 */
	void AddNewCourseCommand();

	/**
	 * @brief Command to add a weekly course based on user input.
	 * @param dayInput User input for the day.
	 * @param day Reference to the day of the week.
	 * @param starttime Reference to the start time.
	 * @param endtime Reference to the end time.
	 */
	void AddWeeklyCourseCommand(int dayInput,
			Poco::DateTime::DaysOfWeek& day, Poco::Data::Time& starttime,
			Poco::Data::Time& endtime);

	/**
	 * @brief Command to add a blocked course based on user input.
	 * @param startdate Reference to the start date.
	 * @param enddate Reference to the end date.
	 * @param starttime Reference to the start time.
	 * @param endtime Reference to the end time.
	 */
	void AddBlockedCourseCommand(
			Poco::Data::Date& startdate,
			Poco::Data::Date& enddate,
			Poco::Data::Time& starttime,
			Poco::Data::Time& endtime);

	/**
	 * @brief Command to list all courses in the database.
	 */
	void ListCourseCommand();
	/**
	 * @brief Command to add a new student based on user input.
	 */
	void AddNewStudentCommand();

	/**
	 * @brief Validates the format of a date string.
	 * @param dob Date of birth string.
	 * @return bool True if the date is valid, false otherwise.
	 */
	bool isValidDate(std::string dob);
	/**
	 * @brief Command to add a new enrollment based on user input.
	 */
	void AddNewEnrollmentCommand();

	/**
	 * @brief Command to print details of a specific student based on user input.
	 */
	void PrintStudentCommand();

	/**
	 * @brief Command to search for students based on user input.
	 */
	void SearchStudentCommand();
	/**
	 * @brief Command to update student properties based on user input.
	 */
	void UpdateStudentCommand();
	/**
	 * @brief Updates specific properties of a student based on user input.
	 * @param userChoice User's choice for updating.
	 * @param matrikelNum Matrikel number of the student.
	 */
	void UpdateStudentProperties(int userChoice,
			unsigned int metrikelNum);
	/**
	 * @brief Command to write the database to a file based on user input.
	 */
	void WritetoFileCommand();
	/**
	 * @brief Command to read data from a file based on user input.
	 */
	void ReadFromFileCommand();
	/**
	 * @brief Command to read data from a server based on user input.
	 */
	void ReadFromServerCommand();

	/**
	 * @brief Converts numeric input to Poco::DateTime::DaysOfWeek.
	 * @param dayInput User input for the day.
	 * @return Poco::DateTime::DaysOfWeek The corresponding day of the week.
	 */
	Poco::DateTime::DaysOfWeek dayofweek(int dayInput);

public:

	/**
	 * @brief Constructor for the SimpleUI class.
	 * @param db Reference to the Student Database instance.
	 */
	SimpleUI(StudentDb& db);

	/**
	 * @brief Runs the SimpleUI interface.
	 */
	void run();
};

#endif /* SIMPLEUI_H_ */
