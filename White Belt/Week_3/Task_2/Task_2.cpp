// Task_2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

/*
Условие
В стандартном потоке дана одна строка, состоящая из числа N и следующих за ним N строк S. Между собой число и строки разделены пробелом.

Отсортируйте строки S в лексикографическом порядке по возрастанию, игнорируя регистр букв, и выведите их в стандартный поток вывода.

Ограничения
0 <= N <= 1000
1 <= |S| <= 15
Каждая строка S[i] может состоять из следующих символов: [0-9,a-z,A-Z]
*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

void PrintVector(const std::vector<std::string>& vec)
{
	for (const std::string& item : vec)
	{
		std::cout << item << ' ';
	}
	std::cout << std::endl;
}

int main()
{
	int length;
	std::cin >> length;

	std::vector<std::string> mass(length);

	for (std::string& symbol : mass)
	{
		std::string word;
		std::cin >> word;
		symbol = word;
	}

	std::sort(std::begin(mass), std::end(mass), [](std::string x, std::string y)
		{
			for (char& symbol : x)
			{
				symbol = tolower(symbol);
			}

			for (char& symbol : y)
			{
				symbol = tolower(symbol);
			}

			return x < y;
		});

	PrintVector(mass);

	return 0;
}