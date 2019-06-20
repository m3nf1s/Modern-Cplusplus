#pragma once

#include <vector>
#include <set>
#include <algorithm>

template <typename T>
std::vector<T> FindGreaterElements(const std::set<T>& elements, const T& border);

template <typename T>
std::vector<T> FindGreaterElements(const std::set<T>& elements, const T& border)
{
	auto it = std::find_if(elements.begin(), elements.end(), [border] (T n)
		{
			return n > border;
		});

	return { it, elements.end() };
}