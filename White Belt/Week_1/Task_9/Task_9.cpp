// Task_9.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <vector>

using namespace std;

/* На вход дано целое положительное число N.
 * Выведите его в двоичной системе счисления без ведущих нулей.
 */
int main()
{
	vector<int> vec;
	int number;
	string a;

	cin >> number;

	while (number != 0)
	{
		vec.push_back(number % 2);
		number /= 2;
	}

	for (int i = vec.size() - 1; i >= 0; i--)
	{
		cout << vec[i];
	}

	return 0;
}


