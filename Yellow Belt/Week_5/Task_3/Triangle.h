#pragma once

#include "Figure.h"

class Triangle : public Figure
{
public:
	Triangle(const std::string& name, const double& side_a, const double& side_b, const double& side_c)
		: name_(name), side_A_(side_a), side_B_(side_b), side_C_(side_c){}

	std::string Name() const override;

	double Perimeter() const override;

	double Area() const override;

private:
	const std::string name_;
	const double side_A_;
	const double side_B_;
	const double side_C_;
};