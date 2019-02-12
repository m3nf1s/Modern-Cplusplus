// Task_4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>

using namespace std;
/*
 * Дано два натуральных числа A и B, не превышающих 1 000 000.
 * Напишите программу, которая вычисляет целую часть частного от деления A на B.
 * Если B = 0, выведите "Impossible".
 */

int main()
{
	int a, b;

	cin >> a >> b;

	if (b != 0)
		cout << a / b << endl;
	else
		cout << "Impossible" << endl;
}	

