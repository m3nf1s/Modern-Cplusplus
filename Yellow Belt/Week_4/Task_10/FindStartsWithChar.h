#pragma once

#include <utility>
#include <algorithm>
#include <string> 

template <typename RandomIt>
std::pair<RandomIt, RandomIt> FindStartsWithChar(RandomIt range_begin, RandomIt range_end, char prefix);

template <typename RandomIt>
std::pair<RandomIt, RandomIt> FindStartsWithChar(RandomIt range_begin, RandomIt range_end, char prefix)
{
	auto lower = std::lower_bound(range_begin, range_end, std::string(1, prefix));

	auto upper = std::upper_bound(range_begin, range_end, std::string(1, prefix),
		[](const std::string& lhs, const std::string& rhs)
		{
			std::string buffer = rhs;
			buffer.resize(lhs.size());

			if (lhs != buffer && lhs < rhs)
			{
				return true;
			}

			return false;
		});

	return { lower, upper };
}