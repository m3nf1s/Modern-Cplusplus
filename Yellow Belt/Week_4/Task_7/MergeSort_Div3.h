#pragma once

#include <vector>
#include <algorithm>

template <typename RandomIt>
void MergeSort_Div3(RandomIt range_begin, RandomIt range_end)
{
	if (range_end - range_begin < 2)
		return;

	std::vector<typename RandomIt::value_type> elements{ range_begin, range_end };

	auto range_first_middle = std::begin(elements) + (std::end(elements) - std::begin(elements)) / 3;

	auto range_second_middle = std::begin(elements) + ((std::end(elements) - std::begin(elements)) / 3 * 2);

	MergeSort_Div3(std::begin(elements), range_first_middle);
	MergeSort_Div3(range_first_middle, range_second_middle);
	MergeSort_Div3(range_second_middle, std::end(elements));

	std::vector<typename RandomIt::value_type> buffer;

	std::merge(
		std::begin(elements), range_first_middle,
		range_first_middle, range_second_middle,
		std::back_inserter(buffer)
	);

	std::merge(
		std::begin(buffer), std::end(buffer),
		range_second_middle, std::end(elements),
		range_begin
	);
}