#pragma once

#include "Figure.h"

class Rect : public Figure
{
public:
	Rect(const std::string& name, const double& height, const double& width) : name_(name), height_(height), width_(width) {}

	std::string Name() const override;

	double Perimeter() const override;

	double Area() const override;

private:
	const std::string name_;
	const double height_;
	const double width_;
};