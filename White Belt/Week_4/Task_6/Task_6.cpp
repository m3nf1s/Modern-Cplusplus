/*
 В файле input.txt записаны вещественные числа, по одному на строчку.
 На стандартный вывод напечатайте эти числа в том же порядке, по одному на строке, но сделайте так,
 чтобы у каждого из них было ровно три знака после десятичной точки
 (округление производится по стандартным правилам, т.е. 0.1234 округляется до 0.123, а 0.1235 до 0.124).
*/

#include "pch.h"
#include <iostream>
#include <fstream>
#include <iomanip>

int main()
{
	std::fstream input("input.txt");
	if (input.is_open())
	{
		double number = 0;
		std::cout << std::fixed << std::setprecision(3);
		while (input >> number)
		{
			std::cout << number << std::endl;
		}
	}
}