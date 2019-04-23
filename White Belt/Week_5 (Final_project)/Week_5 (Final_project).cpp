// Week_5 (Final_project).cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <string>

class Date {
public:
	Date(const int new_year, const int new_month, const int new_day)
	{
		if (new_month > 12 && new_month <= 0)
			throw std::invalid_argument("Month value is invalid: " + new_month);

		if (new_day > 31 && new_day <= 0)
			throw std::invalid_argument("Day value is invalid: " + new_day);

		_year = new_year;
		_month = new_month;
		_day = new_day;
	}

	int GetYear() const
	{
		return _year;
	}

	int GetMonth() const
	{
		return _month;
	}

	int GetDay() const
	{
		return _day;
	}

private:
	int _year;
	int _month;
	int _day;
};

bool operator<(const Date& lhs, const Date& rhs);

class Database {
public:
	void AddEvent(const Date& date, const std::string& event);
	bool DeleteEvent(const Date& date, const std::string& event);
	int  DeleteDate(const Date& date);

	/* ??? */ Find(const Date& date) const;

	void Print() const;
};

int main() {
	Database db;

	std::string command;
	while (std::getline(std::cin, command)) {
		// Считайте команды с потока ввода и обработайте каждую
	}

	return 0;
}