#include "Triangle.h"
#include <cmath>

std::string Triangle::Name() const
{
	return name_;
}

double Triangle::Perimeter() const
{
	return side_A_ + side_B_ + side_C_;
}

double Triangle::Area() const
{
	const double p = 0.5 * (Perimeter());

	return std::sqrt(p * (p - side_A_) * (p - side_B_) * (p - side_C_));
}