#pragma once

#include <vector>
#include <algorithm>

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end)
{
	if (range_end - range_begin < 2)
		return;

	std::vector<typename RandomIt::value_type> elements{ range_begin, range_end };

	auto range_middle = std::begin(elements) + (std::end(elements) - std::begin(elements)) / 2;

	MergeSort(std::begin(elements), range_middle);
	MergeSort(range_middle, std::end(elements));

	std::merge(
		std::begin(elements), range_middle,
		range_middle, std::end(elements),
		range_begin
	);
}