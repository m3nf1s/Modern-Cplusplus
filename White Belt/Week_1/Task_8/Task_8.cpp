// Task_8.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>

using namespace std;

/*
 * В stdin даны два натуральных числа.
 * Выведите в stdout их наибольший общий делитель.
 */
int main()
{
	int number1, number2;

	cin >> number1 >> number2;

	while (number1 > 0 && number2 > 0)
	{
		if (number1 > number2)
			number1 %= number2;
		else
			number2 %= number1;
	}

	cout << number1 + number2;
}

