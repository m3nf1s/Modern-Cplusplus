#include "pch.h"
#include <iostream>
#include <string>

/*
Дана структура LectureTitle:
	struct LectureTitle {
	  string specialization;
	  string course;
	  string week;
	};
Допишите конструктор и структуры Specialization, Course, Week так, чтобы объект LectureTitle можно было создать с помощью кода
	LectureTitle title(
	Specialization("C++"),
	Course("White belt"),
	Week("4th")
	);
но нельзя было с помощью следующих фрагментов кода:

LectureTitle title("C++", "White belt", "4th");

LectureTitle title(string("C++"), string("White belt"), string("4th"));

LectureTitle title = {"C++", "White belt", "4th"};

LectureTitle title = {{"C++"}, {"White belt"}, {"4th"}};

LectureTitle title(
	Course("White belt"),
	Specialization("C++"),
	Week("4th")
);

LectureTitle title(
	Specialization("C++"),
	Week("4th"),
	Course("White belt")
);	

*/

struct Specialization
{
	explicit Specialization(std::string new_value)
	{
		value = new_value;
	}
	std::string value;
};

struct Course
{
	explicit Course(std::string new_value)
	{
		value = new_value;
	}
	std::string value;
};

struct Week
{
	explicit Week(std::string new_value)
	{
		value = new_value;
	}
	std::string value;
};

struct LectureTitle
{
	explicit LectureTitle(Specialization spec_name, Course course_name, Week week_name)
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
