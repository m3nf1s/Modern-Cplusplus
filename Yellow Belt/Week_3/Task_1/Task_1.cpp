/*
Вам дан заголовочный файл sum_reverse_sort.h, содержащий объявления трёх функций
#pragma once
#include <string>
#include <vector>

using namespace std;

int Sum(int x, int y);
string Reverse(string s);
void Sort(vector<int>& nums);

Вам надо прислать cpp-файл, содержащий определения этих функций.
*/
#include <iostream>
#include "sum_reverse_sort.h"

int main()
{
	std::cout << Sum(5, 7) << std::endl;

	std::cout << Reverse("qwerty") << std::endl;

	std::vector<int> vec = { 5,3,2,4,1 };
	Sort(vec);

	for (const auto num : vec)
	{
		std::cout << num << " ";
	}
}
