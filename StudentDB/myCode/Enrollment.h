/*
 * Enrollment.h
 *
 *  Created on: 16 Jan 2024
 *      Author: suhas
 */

#ifndef ENROLLMENT_H_
#define ENROLLMENT_H_

#include <string>
#include "Course.h"
#include <map>
#include <memory>

/**
 * @class Enrollment
 * @brief Represents the enrollment of a student in a course.
 */
class Enrollment
{
private:
	float grade;				///< Grade obtained in the course.
	std::string semester;		///< Semester in which the course was taken.
	const Course* course;		///< Pointer to the enrolled course.

public:
	/**
	 * @brief Constructor for the Enrollment class.
	 *
	 * @param course Pointer to the enrolled course.
	 * @param semester The semester in which the course was taken.
	 * @param grade The grade obtained in the course (default is 0.0).
	 */
	Enrollment(const Course* course, std::string semester, float grade = 0.0);

	/**
	 * @brief Getter for the enrolled course.
	 *
	 * @return const Course* Pointer to the enrolled course.
	 */
	const Course* getCourse() const;

	/**
	 * @brief Getter for the grade obtained in the course.
	 *
	 * @return float The grade obtained.
	 */
	float getGrade() const;

	/**
	 * @brief Getter for the semester in which the course was taken.
	 *
	 * @return const std::string& The semester.
	 */
	const std::string& getSemester() const;

	/**
	 * @brief Setter for the grade obtained in the course.
	 *
	 * @param grade The new grade to set.
	 */
	void setGrade(float grade);

	/**
	 * @brief Writes the enrollment information to the output stream.
	 *
	 * @param out The output stream.
	 */
	void write(std::ostream& out) const;

	/**
	 * @brief Reads and creates an Enrollment object from the input stream.
	 *
	 * @param in The input stream.
	 * @param course_map A map containing course keys and corresponding Course
	 * objects.
	 * @return Enrollment The created Enrollment object.
	 */
	static Enrollment read(std::istream& in,
			const std::map<int, std::unique_ptr<const Course> >& course_map);
};

#endif /* ENROLLMENT_H_ */
