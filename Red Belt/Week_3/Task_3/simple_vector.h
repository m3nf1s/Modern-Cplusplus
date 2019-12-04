#pragma once

#include <cstdlib>
#include <algorithm>

template <typename T>
class SimpleVector
{
public:
	SimpleVector() = default;

	explicit SimpleVector(size_t size)
		: data_(new T[size])
		, size_(size)
		, capacity_(size)
	{
	}

	~SimpleVector()
	{
		delete[] data_;
	}

	T& operator[](size_t index)
	{
		return data_[index];
	}

	T* begin()
	{
		return data_;
	}

	T* end()
	{
		return data_ + size_;
	}

	size_t Size() const
	{
		return size_;
	}

	size_t Capacity() const
	{
		return capacity_;
	}

	void PushBack(const T& value)
	{
		if (size_ >= capacity_)
		{
			size_t new_capacity = capacity_ == 0 ? 1 : 2 * capacity_;
			T* new_data = new T[new_capacity];
			std::copy(begin(), end(), new_data);
			delete[] data_;
			data_ = new_data;
			capacity_ = new_capacity;
		}
		data_[size_++] = value;
	}

private:
	T* data_ = nullptr;
	size_t size_ = 0;
	size_t capacity_ = 0;
};