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
		return front_.empty() && back_.empty();
	}

	size_t Size() const
	{
		return front_.size() + back_.size();
	}

	const T& operator[] (const size_t index) const
	{
		if (index < front_.size())
		{
			return front_[Size() - 1 - index];
		}

		return back_[index - front_.size()];
	}

	T& operator[] (const size_t index)
	{
		if (index < front_.size())
		{
			return front_[front_.size() - 1 - index];
		}

		return back_[index - front_.size()];
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
		if (front_.empty())
		{
			return back_.front();
		}

		return front_.back();
	}

	T& Front()
	{
		if (front_.empty())
		{
			return back_.front();
		}

		return front_.back();
	}

	const T& Back() const
	{
		if (back_.empty())
		{
			return front_.front();
		}

		return back_.back();
	}

	T& Back()
	{
		if (back_.empty())
		{
			return front_.front();
		}

		return back_.back();
	}

	void PushFront(const T& value)
	{
		front_.push_back(value);
	}

	void PushBack(const T& value)
	{
		back_.push_back(value);
	}

private:
	std::vector<T> front_, back_;

	void CheckIndex(const size_t index)
	{
		if (index >= Size())
		{
			throw std::out_of_range("out of range");
		}
	}
};