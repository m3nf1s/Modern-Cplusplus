/*
 * Реализуйте функцию void Reverse(vector<int>& v), которая переставляет элементы вектора в обратном порядке.
 */
 
#include <iostream>
#include <vector>
#include <algorithm>

void Reverse(std::vector<int>& vector)
{
	std::reverse(vector.begin(), vector.end());
}

int main()
{
	std::vector<int> test = { 1, 2, 3, 4, 5, 6, 7, 8, 9};
	Reverse (test);

	for (auto n : test)
	{
		std::cout << n << " ";
	}
}