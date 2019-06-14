#include "sum_reverse_sort.h"
#include <algorithm>

int Sum(int x, int y)
{
	return x + y;
}

std::string Reverse(std::string s)
{
	std::reverse(std::begin(s), std::end(s));

	return s;
}

void Sort(std::vector<int>& nums)
{
	std::sort(nums.begin(), nums.end());
}