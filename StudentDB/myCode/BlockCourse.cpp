/*
 * BlockCourse.cpp
 *
 *  Created on: 16 Jan 2024
 *      Author: suhas
 */

#include "BlockCourse.h"
#include <fstream>
#include <sstream>

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
BlockCourse::BlockCourse(unsigned int courseKey, std::string title,
		std::string major, float creditPoints,
		Poco::Data::Date startDate, Poco::Data::Date endDate,
		Poco::Data::Time startTime, Poco::Data::Time endTime):
		Course(courseKey, title, major,creditPoints), startDate(startDate),
		endDate(endDate), startTime(startTime), endTime(endTime)

{

}

/**
 * @brief Destructor for the BlockCourse class.
 */
BlockCourse::~BlockCourse()
{
}


/**
 * @brief Writes the BlockCourse information to the output stream.
 *
 * @param out The output stream.
 */
void BlockCourse::write(std::ostream &out) const
{
	out << "B;";

	Course::write(out);

	out << std::to_string(startDate.day()) <<":" <<
			std::to_string(startDate.month()) <<":" <<
			std::to_string(startDate.year())
			<<";" << std::to_string(endDate.day()) << ":" <<
			std::to_string(endDate.month()) << ":" <<
			std::to_string(endDate.year()) << ";" <<
			std::to_string(startTime.hour()) <<":"
			<< std::to_string(startTime.minute()) <<":" <<
			std::to_string(startTime.second()) << ";" <<
			std::to_string(endTime.hour()) << ":" <<
			std::to_string(endTime.minute()) << ":" <<
			std::to_string(endTime.second()) ;

}

/**
 * @brief Prints the BlockCourse information to the output stream
 * (Console).
 *
 * @param out The output stream.
 */
void BlockCourse::print(std::ostream &out) const
{
	out << " Block Course: " << std::endl;

	out << " course key: " << std::to_string(this->getCourseKey())
								<< std::endl;
	out << " title: " << this->getTitle() << std::endl;
	out << " major: " << this->getMajor() << std::endl;
	out << " creditPoints: " << std::to_string(this->getCreditPoints())
								<< std::endl;

	out << "StartDate: " << std::to_string(this->startDate.day()) <<"."<<
			std::to_string(this->startDate.month()) <<"."<<
			std::to_string(this->startDate.year()) << std::endl;

	out << "EndDate: " << std::to_string(this->endDate.day()) << "." <<
			std::to_string(this->endDate.month()) << "." <<
			std::to_string(this->endDate.year()) << std::endl;

	out << "StartTime: " << std::to_string(this->startTime.hour()) << ":" <<
			std::to_string(this->startTime.minute()) << ":" <<
			std::to_string(this->startTime.second()) << std::endl;

	out << "endTime: " << std::to_string(this->endTime.hour()) << ":" <<
			std::to_string(this->endTime.minute()) << ":" <<
			std::to_string(this->endTime.second()) << std::endl;


}

/**
 * @brief Reads a BlockCourse from the input stream.
 *
 * @param in The input stream.
 * @return std::unique_ptr<const Course> A pointer to the created
 *  BlockCourse.
 */
std::unique_ptr<const Course> BlockCourse::read(std::istream &in)
{

	std::string courseID_str;
	std::getline(in, courseID_str, ';');
	unsigned int courseKey;
	courseKey = std::stoi(courseID_str);

	std::string title;
	std::getline(in, title, ';');

	std::string major;
	std::getline(in, major, ';');

	std::string creditPoints_str;
	std::getline(in, creditPoints_str, ';');
	float creditPoints = std::stof(creditPoints_str);

	std::string startDate_str;
	std::getline(in, startDate_str, ';');

	std::istringstream startStream(startDate_str);

	int startDay, startMonth, startYear;
	char dot1, dot2;

	startStream >> startDay >> dot1 >> startMonth >> dot2 >> startYear;

	Poco::Data::Date startDate;

	startDate.assign(startYear, startMonth, startDay);

	std::string endDate_str;
	std::getline(in, endDate_str, ';');


	std::istringstream endStream(endDate_str);

	int endDay, endMonth, endYear;

	endStream >>  endDay >> dot1 >> endMonth >> dot2>> endYear;

	Poco::Data::Date endDate;

	endDate.assign(endYear, endMonth, endDay);


	std::string startHourStr, startMinuteStr, startSecondStr;
	std::string endHourStr, endMinuteStr, endSecondStr;

	std::getline(in, startHourStr, ':');
	std::getline(in, startMinuteStr, ':');
	std::getline(in, startSecondStr, ';');

	int startHour = std::stoi(startHourStr);
	int startMinute = std::stoi(startMinuteStr);
	int startSecond = std::stoi(startSecondStr);

	Poco::Data::Time starttime(startHour, startMinute, startSecond);

	std::getline(in, endHourStr, ':');
	std::getline(in, endMinuteStr, ':');
	std::getline(in, endSecondStr, '\n');

	int endHour = std::stoi(endHourStr);
	int endMinute = std::stoi(endMinuteStr);
	int endSecond = std::stoi(endSecondStr);

	Poco::Data::Time endtime(endHour, endMinute, endSecond);


	std::unique_ptr<const Course> ptr (new BlockCourse(courseKey, title,
			major, creditPoints, startDate, endDate, starttime, endtime));

	return ptr;
}
