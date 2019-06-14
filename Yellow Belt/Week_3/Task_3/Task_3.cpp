/*
Вам дано полное определение класса Rectangle:
class Rectangle {
public:
	Rectangle(int width, int height) : width_(width), height_(height)
	{
	}

	int GetArea() const {
		return width_ * height_;
	}

	int GetPerimeter() const {
		return 2 * (width_ + height_);
	}

	int GetWidth() const { return width_; }
	int GetHeight() const { return height_; }

private:
	int width_, height_;
};

Пришлите заголовочный файл rectangle.h, содержащий объявление класса Rectangle.
Это должен быть полноценный заголовочный файл, который можно использовать в большом проекте.
В частности, в нём должна быть решена проблема двойного включения.
*/

#include <iostream>
#include "Rectangle.h"

int main()
{
	Rectangle r(5,10);
	std::cout << "Area: " << r.GetArea() << std::endl;
	std::cout << "Perimeter: " << r.GetPerimeter() << std::endl;
}