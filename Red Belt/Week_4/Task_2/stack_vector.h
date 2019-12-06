#pragma once

#include <stdexcept>
#include <array>

template <typename T, size_t N>
class StackVector
{
public:
    explicit StackVector(size_t a_size = 0)
        :size_(a_size)
    {
        if (size_ > N)
        {
            throw std::invalid_argument("invalid argument");
        }
    }

    T& operator[](size_t index)
    {
        return stack_vector_[index];
    }

    const T& operator[](size_t index) const
    {
        return stack_vector_[index];
    }

    const auto begin() const 
    {
        return stack_vector_.begin();
    }
    const auto end() const
    {
        //return stack_vector_[size_];
        return stack_vector_.begin() + size_;
    }

    auto begin()
    {
        return stack_vector_.begin();
    }
    auto end()
    {
        return stack_vector_.begin() + size_;
    }
    size_t Capacity() const 
    {
        return stack_vector_.size();
    }

    size_t Size() const
    {
        return size_;
    }

    void PushBack(const T& value)
    {
        if (size_ >= N)
        {
            throw std::overflow_error("overflow_error");
        }

        stack_vector_[size_++] = value;
    }
    T PopBack()
    {
        if (size_ == 0)
        {
            throw std::underflow_error("underflow_error");
        }

        return stack_vector_[--size_];
    }

private:
    size_t size_;
    std::array<T, N> stack_vector_;
};