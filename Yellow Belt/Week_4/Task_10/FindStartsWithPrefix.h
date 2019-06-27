#pragma once

#include <utility>
#include <algorithm>
#include <string>

template <typename RandomIt>
std::pair<RandomIt, RandomIt> FindStartsWithPrefix(RandomIt range_begin, RandomIt range_end, const std::string& prefix);

bool Comp(const std::string& lhs, const std::string& rhs);

template <typename RandomIt>
std::pair<RandomIt, RandomIt> FindStartsWithPrefix(RandomIt range_begin, RandomIt range_end, const std::string& prefix)
{
	auto lower = std::lower_bound(range_begin, range_end, prefix);

	auto upper = std::upper_bound(range_begin, range_end, prefix, Comp);

	return { lower, upper };
}