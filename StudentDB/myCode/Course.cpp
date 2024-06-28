/*
 * Course.cpp
 *
 *  Created on: 16 Jan 2024
 *      Author: suhas
 */

#include "Course.h"
#include <iostream>
#include <fstream>

#include "WeeklyCourse.h"


// Static member initialization
std::map<unsigned char, std::string> Course::majorById;

/**
 * @brief Constructor for the Course class.
 *
 * @param courseKey The course key.
 * @param title The title of the course.
 * @param major The major associated with the course.
 * @param creditPoints The credit points for the course.
 */
Course::Course(unsigned int courseKey, std::string title, std::string major,
		float creditPoints)
{

	this->courseKey = courseKey;
	this->title = title;
	this->creditPoints = creditPoints;

	// Extracting the first character of the major string and using
	// it as the major identifier
	this->major = major[0];

	// Mapping the major identifier to the full major name
	majorById[major[0]] = major;

}

/**
 * @brief Destructor for the Course class.
 */
Course::~Course()
{

}

/**
 * @brief Getter for the course key.
 *
 * @return const unsigned int The course key.
 */
const unsigned int Course::getCourseKey() const
{
	return courseKey;
}

/**
 * @brief Getter for the credit points.
 *
 * @return float The credit points.
 */
float Course::getCreditPoints() const
{
	return creditPoints;
}

/**
 * @brief Getter for the major.
 *
 * @return const std::string& The major.
 */
const std::string& Course::getMajor() const
{
	return majorById[major];
}

/**
 * @brief Getter for the title.
 *
 * @return const std::string& The title.
 */
const std::string& Course::getTitle() const
{
	return title;
}

/**
 * @brief Writes the Course information to the output stream.
 *
 * @param out The output stream.
 */
void Course::write(std::ostream &out) const
{
	out << std::to_string(courseKey) << ";" << title << ";" <<
			majorById[major]<< ";" << std::to_string(creditPoints) << ";";
}


