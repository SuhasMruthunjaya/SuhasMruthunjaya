/*
 * weeklyCourse.h
 *
 *  Created on: 16 Jan 2024
 *      Author: suhas
 */

#ifndef WEEKLYCOURSE_H_
#define WEEKLYCOURSE_H_

#include "Course.h"
#include "Poco/Data/Time.h"
#include "Poco/Data/Date.h"
#include <memory>


/**
 * @brief Represents a weekly course, inheriting from the Course class.
 */
class WeeklyCourse: public Course
{
private:

	Poco::DateTime::DaysOfWeek dayOfWeek; /**< Day of the week when the course
	occurs. */
	Poco::Data::Time startTime; /**< Start time of the weekly course. */
	Poco::Data::Time endTime; /**< End time of the weekly course. */

public:
	/**
	 * @brief Constructor for the WeeklyCourse class.
	 *
	 * @param courseKey Unique identifier for the course.
	 * @param title Title of the course.
	 * @param major Major associated with the course.
	 * @param creditPoints Credit points for the course.
	 * @param dayOfWeek Day of the week when the course occurs.
	 * @param startTime Start time of the weekly course.
	 * @param endTime End time of the weekly course.
	 */
	WeeklyCourse(unsigned int courseKey, std::string title, std::string major,
			float creditPoints, Poco::DateTime::DaysOfWeek dayOfWeek,
			Poco::Data::Time startTime, Poco::Data::Time endTime);
	/**
	 * @brief Destructor for the WeeklyCourse class.
	 */
	~WeeklyCourse();

	/**
	 * @brief Writes the weekly course information to an output stream.
	 *
	 * @param out Output stream to write the information to.
	 */
	void write(std::ostream& out) const;

	/**
	 * @brief Prints the details of the weekly course to an output stream.
	 *
	 * @param out Output stream to print the details to.
	 */
	void print(std::ostream& out) const;

	/**
	 * @brief Reads a weekly course's information from an input stream
	 * and returns a new WeeklyCourse object.
	 *
	 * @param in Input stream to read the information from.
	 * @return A new WeeklyCourse object initialized with the read information.
	 */
	static std::unique_ptr<const Course> read(std::istream& in);
};

#endif /* WEEKLYCOURSE_H_ */
