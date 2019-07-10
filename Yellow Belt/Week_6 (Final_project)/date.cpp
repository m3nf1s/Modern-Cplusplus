#include "date.h"

Date ParseDate(istream& is)
{
	int year, month, day;
	is >> year;
	is.ignore(1);
	is >> month;
	is.ignore(1);
	is >> day;
	is.ignore(1);

	return { year, month, day };
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