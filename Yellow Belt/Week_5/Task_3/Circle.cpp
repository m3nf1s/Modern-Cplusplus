#include "Circle.h"

std::string Circle::Name() const
{
	return name_;
}

double Circle::Perimeter() const
{
	const double pi = 3.14;
	return 2 * radius_ * pi;
}

double Circle::Area() const
{
	const double pi = 3.14;
	return pi * radius_ * radius_;
}