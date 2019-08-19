#include <iostream>
#include <iomanip>
#include <tuple>

#include "date.h"

//Парсим дату
Date ParseDate(istream& is)
{
	int year, month, day;
	is >> year;
	is.ignore(1);
	is >> month;
	is.ignore(1);
	is >> day;

	return { year, month, day };
}

ostream& operator<< (ostream& os, const Date& date)
{
	return os << setw(4) << setfill('0') << date.year_ << '-' <<
		setw(2) << setfill('0') << date.month_ << '-' <<
		setw(2) << setfill('0') << date.day_;
}

bool operator< (const Date& lhs, const Date& rhs)
{
	auto lhs_key = tie(lhs.year_, lhs.month_, lhs.day_);
	auto rhs_key = tie(rhs.year_, rhs.month_, rhs.day_);

	return lhs_key < rhs_key;
}

bool operator<= (const Date& lhs, const Date& rhs)
{
	auto lhs_key = tie(lhs.year_, lhs.month_, lhs.day_);
	auto rhs_key = tie(rhs.year_, rhs.month_, rhs.day_);

	return lhs_key <= rhs_key;
}

bool operator> (const Date& lhs, const Date& rhs)
{
	auto lhs_key = tie(lhs.year_, lhs.month_, lhs.day_);
	auto rhs_key = tie(rhs.year_, rhs.month_, rhs.day_);

	return lhs_key > rhs_key;
}

bool operator>= (const Date& lhs, const Date& rhs)
{
	auto lhs_key = tie(lhs.year_, lhs.month_, lhs.day_);
	auto rhs_key = tie(rhs.year_, rhs.month_, rhs.day_);

	return lhs_key >= rhs_key;
}

bool operator== (const Date& lhs, const Date& rhs)
{
	auto lhs_key = tie(lhs.year_, lhs.month_, lhs.day_);
	auto rhs_key = tie(rhs.year_, rhs.month_, rhs.day_);

	return lhs_key == rhs_key;
}

bool operator!= (const Date& lhs, const Date& rhs)
{
	auto lhs_key = tie(lhs.year_, lhs.month_, lhs.day_);
	auto rhs_key = tie(rhs.year_, rhs.month_, rhs.day_);

	return lhs_key != rhs_key;
}