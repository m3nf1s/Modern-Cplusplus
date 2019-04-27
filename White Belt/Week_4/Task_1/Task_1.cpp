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

#include <iostream>
#include <string>

struct Specialization
{
	explicit Specialization(const std::string& new_value)
	{
		value = new_value;
	}
	std::string value;
};

struct Course
{
	explicit Course(const std::string& new_value)
	{
		value = new_value;
	}
	std::string value;
};

struct Week
{
	explicit Week(const std::string& new_value)
	{
		value = new_value;
	}
	std::string value;
};

struct LectureTitle
{
	explicit LectureTitle(const Specialization& spec_name, const Course& course_name, const Week& week_name)
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