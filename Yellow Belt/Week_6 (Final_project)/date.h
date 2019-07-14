#pragma once

#include <iostream>

using namespace std;

//хранит в себе дату год-месяц-день
class Date
{
public:
	Date(int year, int month, int day) : year_(year), month_(month), day_(day) {}
	const int year_;
	const int month_;
	const int day_;
};

//парсит дату (год-месяц-день)
//и возвращается готовый класс Date
Date ParseDate(istream& is);

ostream& operator<< (ostream& os, const Date& date);

bool operator< (const Date& lhs, const Date& rhs);
bool operator<= (const Date& lhs, const Date& rhs);
bool operator> (const Date& lhs, const Date& rhs);
bool operator>= (const Date& lhs, const Date& rhs);
bool operator== (const Date& lhs, const Date& rhs);
bool operator!= (const Date& lhs, const Date& rhs);