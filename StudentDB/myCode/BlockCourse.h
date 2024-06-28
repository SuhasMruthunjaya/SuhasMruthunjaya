/*
 * BlockCourse.h
 *
 *  Created on: 16 Jan 2024
 *      Author: suhas
 */

#ifndef BLOCKCOURSE_H_
#define BLOCKCOURSE_H_

#include "Course.h"
#include <Poco/Data/Date.h>
#include <Poco/Data/Time.h>
#include <memory>

/**
 * @class BlockCourse
 * @brief Represents a course with specific start and end dates and times.
 */

class BlockCourse: public Course
{
private:
	Poco::Data::Date startDate;
	Poco::Data::Date endDate;
	Poco::Data::Time startTime;
	Poco::Data::Time endTime;



public:

	/**
	 * @brief Constructor for the BlockCourse class.
	 *
	 * @param courseKey The course key.
	 * @param title The title of the course.
	 * @param major The major associated with the course.
	 * @param creditPoints The credit points for the course.
	 * @param startDate The start date of the block course.
	 * @param endDate The end date of the block course.
	 * @param startTime The start time of the block course.
	 * @param endTime The end time of the block course.
	 */
	BlockCourse(unsigned int courseKey, std::string title, std::string major,
			float creditPoints,
			Poco::Data::Date startDate, Poco::Data::Date endDate,
			Poco::Data::Time startTime, Poco::Data::Time endTime );

	/**
	 * @brief Destructor for the BlockCourse class.
	 */
	 ~BlockCourse();

	/**
	 * @brief Writes the BlockCourse information to the output stream.
	 *
	 * @param out The output stream.
	 */
	void write(std::ostream& out) const;

	/**
	 * @brief Prints the BlockCourse information to the output stream
	 * (Console).
	 *
	 * @param out The output stream.
	 */
	void print(std::ostream& out) const;

	/**
	 * @brief Reads a BlockCourse from the input stream.
	 *
	 * @param in The input stream.
	 * @return std::unique_ptr<const Course> A pointer to the created
	 *  BlockCourse.
	 */
	static std::unique_ptr<const Course> read(std::istream& in);
};

#endif /* BLOCKCOURSE_H_ */
