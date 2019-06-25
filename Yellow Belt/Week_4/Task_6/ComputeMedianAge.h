#pragma once

#include <algorithm>

template <typename InputIt>
int ComputeMedianAge(InputIt range_begin, InputIt range_end)
{
	if (range_begin == range_end)
	{
		return 0;
	}

	std::vector<typename InputIt::value_type> range_copy(range_begin, range_end);

	auto middle = std::begin(range_copy) + range_copy.size() / 2;

	std::nth_element(
		std::begin(range_copy), middle, std::end(range_copy),
		[](const Person& lhs, const Person& rhs)
		{
			return lhs.age < rhs.age;
		}
	);

	return middle->age;
}