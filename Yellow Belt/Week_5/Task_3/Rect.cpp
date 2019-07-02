#include "Rect.h"

std::string Rect::Name() const
{
	return name_;
}

double Rect::Perimeter() const
{
	return 2 * (height_ + width_);
}

double Rect::Area() const
{
	return height_ * width_;
}