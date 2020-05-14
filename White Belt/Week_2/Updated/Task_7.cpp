/*
 * Реализуйте функцию vector<int> Reversed(const vector<int>& v), возвращающую копию вектора v, в которой числа переставлены в обратном порядке.
 */

#include <iostream>
#include <vector>

std::vector<int> Reversed(const std::vector<int>& vector)
{
	return { vector.rbegin(), vector.rend() };
}

int main()
{
	const std::vector<int> test = { 1, 5, 3, 4, 2 };
	const std::vector<int> simple = Reversed(test);

	for (auto n : simple)
	{
		std::cout << n << " ";
	}
}