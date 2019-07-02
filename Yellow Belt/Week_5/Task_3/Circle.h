#pragma once

#include "Figure.h"

class Circle : public Figure
{
public:
	Circle(const std::string& name, const double& radius) : name_(name), radius_(radius) {}

	std::string Name() const override;

	double Perimeter() const override;

	double Area() const override;
private:
	const std::string name_;
	const double radius_;
};