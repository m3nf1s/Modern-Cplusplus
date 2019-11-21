#pragma once

#include <vector>
#include <stdexcept>

template<typename T>
class Deque
{
public:
	Deque() = default;

	bool Empty() const
	{
		return _front.empty() && _back.empty();
	}

	size_t Size() const
	{
		return _front.size() + _back.size();
	}

	const T& operator[] (const size_t index) const
	{
		if (index < _front.size())
		{
			return _front[Size() - 1 - index];
		}

		return _back[index - _front.size()];
	}

	T& operator[] (const size_t index)
	{
		if (index < _front.size())
		{
			return _front[_front.size() - 1 - index];
		}

		return _back[index - _front.size()];
	}

	const T& At(const size_t index) const
	{
		CheckIndex(index);

		return operator[](index);
	}

	T& At(const size_t index)
	{
		CheckIndex(index);

		return operator[](index);
	}

	const T& Front() const
	{
		if (_front.empty())
		{
			return _back.front();
		}

		return _front.back();
	}

	T& Front()
	{
		if (_front.empty())
		{
			return _back.front();
		}

		return _front.back();
	}

	const T& Back() const
	{
		if (_back.empty())
		{
			return _front.front();
		}

		return _back.back();
	}

	T& Back()
	{
		if (_back.empty())
		{
			return _front.front();
		}

		return _back.back();
	}

	void PushFront(const T& value)
	{
		_front.push_back(value);
	}

	void PushBack(const T& value)
	{
		_back.push_back(value);
	}

private:
	std::vector<T> _front, _back;

	void CheckIndex(const size_t index)
	{
		if (index >= Size())
		{
			throw std::out_of_range("out of range");
		}
	}
};