#pragma once

#include <vector>
#include <algorithm>

template <typename T>
void RemoveDuplicates(std::vector<T>& elements)
{
	std::sort(elements.begin(), elements.end());
	auto it = std::unique(elements.begin(), elements.end());
	elements.erase(it, elements.end());
}