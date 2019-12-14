#include <cstdint>
#include <utility>
#include <algorithm>

// Реализуйте SimpleVector в этом файле
// и отправьте его на проверку

template <typename T>
class SimpleVector 
{
public:
    SimpleVector() = default;

    explicit SimpleVector(size_t size)
        : data_(new T[size])
        , capacity_(size)
        , size_(size)
    {      
    }

    SimpleVector(SimpleVector<T>&& other)
        : data_(other.data_)
        , capacity_(other.capacity_)
        , size_(other.size_)
    {
        other.data_ = nullptr;
        other.capacity_ = other.size_ = 0;
    }

    ~SimpleVector()
    {
        delete[] data_;
        capacity_ = size_ = 0;
    }

    void operator= (SimpleVector<T>&& other)
    {
        delete[] data_;
        data_ = other.data_;
        capacity_ = other.capacity_;
        size_ = other.size_;

        other.data_ = nullptr;
        other.capacity_ = other.size_ = 0;
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

    const T* begin() const 
    {
        return data_;
    }
    const T* end() const 
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

    void PushBack(T value)
    {
        if (size_ >= capacity_)
        {
            size_t new_cap = capacity_ == 0 ? 1 : capacity_ * 2;
            T* new_data = new T[new_cap];
            std::move(begin(), end(), temp);

            delete[] data_;
            data_ = new_data;
            capacity_ = new_cap;
        }
        data_[size_++] = std::move(value);
    }

private:
    T* data_ = nullptr;
    size_t size_ = 0;
    size_t capacity_ = 0;
};
