/*
    ������ �� �������� ����������� �������, �������� ������� �������� ������������ �����,
    ������ ��� ������ ����� �� ��� ������ ������� ���������.
    ��������, ������ ������� �������� ������ ����� ���������� � ��������� ������,
    � ����� � � ��������� �����������.
    ����� ������������� ���������� � �������� ������������ �����,
    ������ ���� ������������ ����� � ���� ����������.
    
    ��� ������������� ����� �������� ����� ���� ������� ������ LazyValue<T>.
    � ���� ���� ����������� ����� const T& Get(), ������� ���������� ������ �� ��������� ������.
    � ���� ������������ LazyValue ��������� ���������������� �������,
    ������� ������������ ��� ������ ������ ������ Get ��� �������� ��������� �������.
    ����������� ������ Get ������ ���������� ������ �� �������� ������.
    
    ����� �������, ������ ������ LazyValue<T> �� ������ �����
    �� �������� ��������� ������� �� ������� ������ ������ Get.
    
    ��� ��� ��������� ������� LazyValue. ���������� ���.
    
    ����� ��������� ������ ����������:    
    *   ������ ������ LazyValue<T> �� ������ �������������� ������ ���� T ��� ���� ��������
    *   ��� ������ ������ ������ LazyValue<T>::Get ������ ����������� ������ ���� T � ������� �������,
        ���������� � ����������� LazyValue<T>
    *   ����������� ������ ������ Get �� ������ �������� �������, ���������� � �����������
    *   ���� �� ����� ����� ������� LazyValue<T> ����� Get �� ��� ������ �� ����,
        �� ���������������� ������� �� ������ ���� �������.
    *   ������ LazyValue ������ ������������ ������ � ������ ��� ������������ �� ���������
*/
#include "test_runner.h"

#include <functional>
#include <string>
#include <optional>

template <typename T>
class LazyValue
{
public:
    explicit LazyValue(std::function<T()> init)
        : function_(std::move(init))
    {
    }

    bool HasValue() const
    {
        return value_.has_value();
    }

    const T& Get() const
    {
        if (!value_)
        {
            value_ = function_();
        }
        return *value_;
    }

private:
    std::function<T()> function_;
    mutable std::optional<T> value_;
};

void UseExample()
{
    const std::string big_string = "Giant amounts of memory";
    
    LazyValue<std::string> lazy_string([&big_string] { return big_string; });
    
    ASSERT(!lazy_string.HasValue());
    ASSERT_EQUAL(lazy_string.Get(), big_string);
    ASSERT_EQUAL(lazy_string.Get(), big_string);
}

void TestInitializerIsntCalled()
{
    bool called = false;
    
    {
        LazyValue<int> lazy_int([&called] 
            {
                called = true;
                return 0;
            });
    }
    ASSERT(!called);
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, UseExample);
    RUN_TEST(tr, TestInitializerIsntCalled);
    return 0;
}
