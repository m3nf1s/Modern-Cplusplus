#include "FindStartsWithPrefix.h"

bool Comp(const std::string& lhs, const std::string& rhs)
{
	std::string buffer = rhs;
	buffer.resize(lhs.size());

	if (lhs != buffer && lhs < rhs)
		return true;

	return false;
}