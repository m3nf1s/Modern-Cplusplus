#pragma once

#include <vector>
#include <algorithm>

template <typename Iterator>
class IteratorRange
{
public:
	IteratorRange(Iterator f, Iterator l) : first(f), last(l) {}

	Iterator begin() const { return first; }

	Iterator end() const { return last; }

	size_t size() const { return last - first; }

private:
	Iterator first, last;
};

template <typename Iterator>
auto MakePage(Iterator f, Iterator l, size_t top)
{
	return IteratorRange(f, std::next(f, std::min<size_t>(top, (l - f))));
}