// Task_1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

/*
	Условие

	В стандартном потоке дана одна строка, состоящая из N + 1 целых чисел.
	Первым числом идёт само число N. Далее следуют ещё N чисел, обозначим их за массив A.
	Между собой числа разделены пробелом.

	Отсортируйте массив А по модулю и выведите его в стандартный поток.

	Ограничения
	0 <= N <= 1000
	-1000000 <= A[i] <= 1000000
*/

#include <iostream>
#include <vector>
#include <algorithm>

void PrintVector(const std::vector<int>& vec)
{
	for (const int& item : vec)
	{
		std::cout << item << " ";
	}
	std::cout << std::endl;
}

int main()
{
	size_t length;
	std::cin >> length;
	
	std::vector<int> mass(length);

	for (size_t i = 0; i < length; i++)
	{
		int number;
		std::cin >> number;
		mass[i] = number;
	}

	std::sort(std::begin(mass), std::end(mass), [](int& x, int& y)
	{
		return abs(x) < abs(y);
	});

	PrintVector(mass);

	return 0;
}

