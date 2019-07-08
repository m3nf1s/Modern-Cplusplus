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