/*
 * Course.h
 *
 *  Created on: 16 Jan 2024
 *      Author: suhas
 */

#ifndef COURSE_H_
#define COURSE_H_

#include <string>
#include <map>

/**
 * @class Course
 * @brief Base class representing a course.
 */
class Course
{
private:
	static std::map<unsigned char, std::string> majorById;

	unsigned int courseKey;
	std::string title;
	unsigned char major;
	float creditPoints;

public:
	/**
	 * @brief Constructor for the Course class.
	 *
	 * @param courseKey The course key.
	 * @param title The title of the course.
	 * @param major The major associated with the course.
	 * @param creditPoints The credit points for the course.
	 */
	Course(unsigned int courseKey, std::string title, std::string major,
			float creditPoints);
	/**
	 * @brief Virtual destructor for the Course class.
	 */
	virtual ~Course() = 0;
	/**
	 * @brief Getter for the course key.
	 *
	 * @return const unsigned int The course key.
	 */
	const unsigned int getCourseKey() const;
	/**
	 * @brief Getter for the credit points.
	 *
	 * @return float The credit points.
	 */
	float getCreditPoints() const;
	/**
	 * @brief Getter for the major.
	 *
	 * @return const std::string& The major.
	 */
	const std::string& getMajor() const;
	/**
	 * @brief Getter for the title.
	 *
	 * @return const std::string& The title.
	 */
	const std::string& getTitle() const;

	/**
	 * @brief Writes the Course information to the output stream. - Console
	 *
	 * @param out The output stream.(Console)
	 */
	virtual void write(std::ostream& out) const;

	/**
	 * @brief Pure virtual function for printing the Course information
	 * to the output stream.
	 *
	 * @param out The output stream.
	 */
	virtual void print(std::ostream& out) const = 0;




};

#endif /* COURSE_H_ */
