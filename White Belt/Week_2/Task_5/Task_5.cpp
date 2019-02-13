// Task_5.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/* Напишите функцию MoveStrings, которая принимает два вектора строк, source и destination, и дописывает все строки из первого вектора в конец второго.
 * После выполнения функции вектор source должен оказаться пустым.
 */

void MoveString(vector<string>& source, vector<string>& destination)
{
	for (auto w : source)
		destination.push_back(w);

	source.clear();
}

int main()
{
	vector<string> first = { "qwe", "rty", "asd", "fgh" };
	vector<string> second = { "keyboard: " };
	MoveString(first, second);

	cout << "first - ";
	for (auto w : first)
		cout <<  w ;

	cout << endl;

	cout << "second - ";
	for (auto w : second)
		cout << w;
}
