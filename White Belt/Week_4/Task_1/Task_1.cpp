// Task_1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>

struct Specialization
{
public:
	explicit Specialization(std::string new_value)
	{
		value = new_value;
	}
	std::string value;
};

struct Course
{
public:
	Course(std::string new_value)
	{
		value = new_value;
	}
	std::string value;
};

struct Week
{
public:
	Week(std::string new_value)
	{
		value = new_value;
	}
	std::string value;
};

struct LectureTitle
{
public:
	LectureTitle(Specialization spec_name, Course course_name, Week week_name)
	{
		specialization = spec_name.value;
		course = course_name.value;
		week = week_name.value;
	}
	std::string specialization;
	std::string course;
	std::string week;	
};
int main()
{
	LectureTitle title(
		Specialization("C++"),
		Course("White belt"),
		Week("4th")
	);
}
