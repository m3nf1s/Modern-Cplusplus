/*
Как видно из кода, есть два вида команд:
	1) ADD — добавить фигуру в набор;
	2) PRINT — для каждой фигуры в наборе распечатать название, периметр и площадь.
Программа поддерживает три вида фигур: прямоугольник, треугольник и круг.
Их добавление описывается так:
	1) ADD RECT width height — добавить прямоугольник с размерами width и height (например, ADD RECT 2 3).
	2) ADD TRIANGLE a b c — добавить треугольник со сторонами a, b и c (например, ADD TRIANGLE 3 4 5).
	3) ADD CIRCLE r — добавить круг радиуса r (например, ADD CIRCLE 5).

Не меняя функцию main, реализуйте недостающие функции и классы:

	1) базовый класс Figure с чисто виртуальными методами Name, Perimeter и Area;
	2) классы Triangle, Rect и Circle, которые являются наследниками класса Figure и переопределяют его виртуальные методы;
	3) функцию CreateFigure, которая в зависимости от содержимого входного потока создаёт
		shared_ptr<Rect>, shared_ptr<Triangle> или shared_ptr<Circle>.

Гарантируется, что все команды ADD корректны;
	размеры всех фигур — это натуральные числа не больше 1000.
В качестве значения π используйте 3,14.
*/

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <sstream>
#include <iomanip>
#include "Figure.h"



int main()
{
	std::vector<std::shared_ptr<Figure>> figures;
	for (std::string line; std::getline(std::cin, line); )
	{
		std::istringstream is(line);

		std::string command;
		is >> command;
		if (command == "ADD")
		{
			figures.push_back(CreateFigure(is));
		}
		else if (command == "PRINT")
		{
			for (const auto& current_figure : figures)
			{
				std::cout << std::fixed << std::setprecision(3)
					<< current_figure->Name() << " "
					<< current_figure->Perimeter() << " "
					<< current_figure->Area() << std::endl;
			}
		}
	}
	return 0;
}
