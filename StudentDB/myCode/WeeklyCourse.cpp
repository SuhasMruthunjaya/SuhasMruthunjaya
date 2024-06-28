/*
 * weeklyCourse.cpp
 *
 *  Created on: 16 Jan 2024
 *      Author: suhas
 */

#include "WeeklyCourse.h"
#include <string>
#include <fstream>

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
WeeklyCourse::WeeklyCourse(unsigned int courseKey, std::string title,
		std::string major, float creditPoints,
		Poco::DateTime::DaysOfWeek dayOfWeek,
		Poco::Data::Time startTime,Poco::Data::Time endTime): Course(courseKey,
				title,major,creditPoints), dayOfWeek(dayOfWeek),
				startTime(startTime),
				endTime(endTime)
{

}
/**
 * @brief Destructor for the WeeklyCourse class.
 */
WeeklyCourse::~WeeklyCourse()
{
}

/**
 * @brief Writes the weekly course information to an output stream.
 *
 * @param out Output stream to write the information to.
 */
void WeeklyCourse::write(std::ostream &out) const
{
	out << "W;";

	Course::write(out);


	out << std::to_string(dayOfWeek) <<";" << std::to_string(startTime.hour())
							<<":" << std::to_string(startTime.minute()) <<":"
							<< std::to_string(startTime.second()) << ";" <<
							std::to_string(endTime.hour()) << ":" <<
							std::to_string(endTime.minute()) << ":" <<
							std::to_string(endTime.second());


}
/**
 * @brief Prints the details of the weekly course to an output stream.
 *
 * @param out Output stream to print the details to.
 */
void WeeklyCourse::print(std::ostream &out) const
{
	out << " Weekly Course: " << std::endl;

	out << " course key: " << std::to_string(this->getCourseKey()) << std::endl;
	out << " title: " << this->getTitle() << std::endl;
	out << " major: " << this->getMajor() << std::endl;
	out << " creditPoints: " << std::to_string(this->getCreditPoints())
							<< std::endl;
	out << " day of week: " << std::to_string(this->dayOfWeek) << std::endl;
	out << " startTime: " << std::to_string(this->startTime.hour()) <<":"<<
			std::to_string(this->startTime.minute()) <<":"<<
			std::to_string(this->startTime.second()) << std::endl;

	out << " endTime: " << std::to_string(this->endTime.hour()) <<":"<<
			std::to_string(this->endTime.minute()) <<":"<<
			std::to_string(this->endTime.second());

}
/**
 * @brief Reads a weekly course's information from an input stream
 * and returns a new WeeklyCourse object.
 *
 * @param in Input stream to read the information from.
 * @return A new WeeklyCourse object initialized with the read information.
 */
std::unique_ptr<const Course> WeeklyCourse::read(std::istream &in)
{
	std::string courseID_str;
	std::getline(in, courseID_str, ';');

	std::string title_str;
	std::getline(in, title_str, ';');


	std::string major_str;
	std::getline(in, major_str, ';');

	std::string creditPoints_str;
	std::getline(in, creditPoints_str, ';');

	std::string daysofweek;
	std::getline(in, daysofweek, ';');

	std::string starthour;
	std::getline(in, starthour, ':');

	std::string startminute;
	std::getline(in, startminute, ':');

	std::string startsecond;
	std::getline(in, startsecond, ';');

	std::string endhour;
	std::getline(in, endhour, ':');

	std::string endminute;
	std::getline(in, endminute, ':');

	std::string endsecond;
	std::getline(in, endsecond, '\n');

	unsigned int courseID = std::stoi(courseID_str);
	float creditPoints = std::stof(creditPoints_str);
	int days_of_week = std::stoi(daysofweek);

	Poco::DateTime::DaysOfWeek days = Poco::DateTime::DaysOfWeek(days_of_week);

	int start_hour = std::stoi(starthour);
	int start_minute = std::stoi(startminute);
	int start_second = std::stoi(startsecond);

	Poco::Data::Time starttime(start_hour, start_minute, start_second);

	int end_hour = std::stoi(endhour);
	int end_minute = std::stoi(endminute);
	int end_second = std::stoi(endsecond);

	Poco::Data::Time endtime(end_hour, end_minute,end_second);


	return std::unique_ptr<const Course> (new WeeklyCourse(courseID, title_str,
			major_str, creditPoints,
			days, starttime, endtime));


	return 0;

}
