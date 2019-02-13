// Task_1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>

/*
 * Напишите функцию, которая
 * называется Factorial
 * возвращает int
 * принимает int и возвращает факториал своего аргумента.
 * Гарантируется, что аргумент функции по модулю не превышает 10. Для отрицательных аргументов функция должна возвращать 1.
 */

/// <summary>
/// Нахождение факторила числа
/// </summary>
/// <param name="number">Факториал числа</param>
/// <returns>Факториал</returns>
int Factorial (int number)
{
	int fac = 1;
	if (number > 1)
	{
		for (int i = 1; i <= number; i++)
			fac *= i;

		return fac;
	}
	return fac;
}

int main()
{
	int number;
	std::cin >> number;
	std::cout << Factorial(number) << std::endl;

	return 0;
}

