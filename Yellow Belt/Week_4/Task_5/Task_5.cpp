/*
Дано целое положительное число N, не превышающее 9.
Выведите все перестановки чисел от 1 до N в обратном лексикографическом порядке.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

void PrintPermutations(const int size);
std::ostream& operator<< (std::ostream& os, const std::vector<int>& vec);

int main()
{
	int n;
	std::cin >> n;
	PrintPermutations(n);
}

void PrintPermutations(const int size)
{
	std::vector<int> result(size);

	std::iota(std::rbegin(result), std::rend(result), 1);

	do
	{
		std::cout << result << std::endl;
	} while (std::prev_permutation(std::begin(result), std::end(result)));
}

std::ostream& operator<< (std::ostream& os, const std::vector<int>& vec)
{
	bool first = true;
	for (const auto el : vec)
	{
		if (!first)
		{
			os << ' ';
		}
		first = false;
		os << el;			
	}

	return os;
}