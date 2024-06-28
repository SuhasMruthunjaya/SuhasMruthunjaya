/*
 * Enrollment.cpp
 *@brief Implementation file for the Enrollment class.
 *  Created on: 16 Jan 2024
 *      Author: suhas
 */

#include "Enrollment.h"
#include <stdexcept>


/**
 * @brief Constructor for the Enrollment class.
 *
 * @param course Pointer to the enrolled course.
 * @param semester The semester in which the course was taken.
 * @param grade The grade obtained in the course.
 */

Enrollment::Enrollment(const Course* course, std::string semester, float grade)
{

	this->course = course;
	this->semester = semester;
	this->grade = grade;
}
/**
 * @brief Getter for the grade obtained in the course.
 *
 * @return float The grade obtained.
 */
float Enrollment::getGrade() const
{
	return grade;
}
/**
 * @brief Getter for the grade obtained in the course.
 *
 * @return float The grade obtained.
 */
void Enrollment::setGrade(float grade)
{
	this->grade = grade;
}
/**
 * @brief Getter for the enrolled course.
 *
 * @return const Course* Pointer to the enrolled course.
 */
const Course* Enrollment::getCourse() const
{
	return course;
}
/**
 * @brief Getter for the semester in which the course was taken.
 *
 * @return const std::string& The semester.
 */
const std::string& Enrollment::getSemester() const
{
	return semester;
}
/**
 * @brief Writes the enrollment information to the output stream.
 *
 * @param out The output stream.
 */
void Enrollment::write(std::ostream &out) const
{
	out << std::to_string(course->getCourseKey()) + ";" +
			semester + ";" + std::to_string(grade);

}
/**
 * @brief Reads and creates an Enrollment object from the input stream.
 *
 * @param in The input stream.
 * @param course_map A map containing course keys and corresponding Course
 * objects.
 * @return Enrollment The created Enrollment object.
 */
Enrollment Enrollment::read(std::istream &in,
		const std::map<int, std::unique_ptr<const Course> >& course_map)
{

	std::string courseKeyStr;
	std::getline(in, courseKeyStr, ';');

	unsigned int courseKey = std::stoi(courseKeyStr);

	const auto& it  = course_map.find(courseKey);

	if(it != course_map.end())
	{
		std::string semester ;
		std::getline(in, semester, ';');

		std::string grade_str;
		std::getline(in, grade_str, '\n');

		float grade = std::stof(grade_str);

		// Get the Course pointer
		const Course* course = &(*(it->second));

		// Create and return Enrollment object
		return Enrollment(course,semester, grade);
	}
	else
	{
		throw std::runtime_error(" The courseKey is not found in the "
				"Courses database");
	}

}
