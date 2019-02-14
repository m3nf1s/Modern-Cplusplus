// Task_8.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

/*
 * Даны значения температуры, наблюдавшиеся в течение N подряд идущих дней.
 * Найдите номера дней (в нумерации с нуля) со значением температуры выше среднего арифметического за все N дней.
 * Гарантируется, что среднее арифметическое значений температуры является целым числом.
 * 
 * Формат ввода
 * Вводится число N, затем N неотрицательных целых чисел — значения температуры в 0-й, 1-й, ... (N−1)-й день.
 * 
 * Формат вывода
 * Первое число K — количество дней, значение температуры в которых выше среднего арифметического.
 * Затем K целых чисел — номера этих дней.
 */
int main()
{
	int length;
	int sum = 0;
	int days = 0;
	cin >> length;

	vector<int> temperatures(length);

	for (int& temperature : temperatures)
	{
		cin >> temperature;
		sum += temperature;
	}

	int average = sum / length;

	for (int temperature : temperatures)
		if (temperature > average)
			days++;

	cout << days << endl;

	for (int i = 0; i < temperatures.size(); i++)
		if (temperatures[i] > average)
			cout << i << " ";

	return 0;
}
