// Task_7.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
 * Реализуйте функцию vector<int> Reversed(const vector<int>& v), возвращающую копию вектора v, в которой числа переставлены в обратном порядке.
 */

vector<int> Reversed(const vector<int>& v)
{
	vector<int> buff;
	for (int i = v.size() - 1; i >= 0; i--)
		buff.push_back(v[i]);
	return buff;
}

int main()
{
	vector<int> test = { 1, 5, 3, 4, 2 };
	vector<int> simple = Reversed(test);

	for (auto n : simple)
		cout << n << " ";
}
