// Task_4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>

using namespace std;

/*
 * Напишите функцию UpdateIfGreater, которая принимает два целочисленных аргумента: first и second.
 * Если first оказался больше second, Ваша функция должна записывать в second значение параметра first.
 * При этом изменение параметра second должно быть видно на вызывающей стороне.
 */

void UpdateIfGreater (const int& number1, int& number2)
{
	if (number1 > number2)
		number2 = number1;
}

int main()
{
	int number1, number2;
	cin >> number1 >> number2;
	UpdateIfGreater(number1, number2);
	cout << number1 << " " << number2 << endl;
}

