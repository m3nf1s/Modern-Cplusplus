#pragma once

#include "iterator_range.h"

#include <vector>

template <typename Iterator>
class Paginator
{
public:
	Paginator(Iterator first, Iterator last, size_t page_size)
	{	
		while (first != last)
		{
			_pages.push_back(MakePage(first, last, page_size));
			first = _pages[_pages.size() - 1].end();
		}
	}

	auto begin() const { return _pages.begin(); }

	auto end() const { return _pages.end(); }

	size_t size() const { return _pages.size(); }

private:
	std::vector<IteratorRange<Iterator>> _pages;
};

template <typename Container>
auto Paginate(Container& c, size_t page_size)
{
	return Paginator(c.begin(), c.end(), page_size);
}