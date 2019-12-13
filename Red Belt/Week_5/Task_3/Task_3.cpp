/*
    В видеолекции мы с вами познакомились с конструктором копирования и оператором присваивания,
        а также написали конструктор копирования для SimpleVector.
    В этой задаче вам нужно реализовать оператор присваивания для SimpleVector.
    Вам дан cpp-файл, который подключает заголовочный файл simple_vector.h и содержит небольшой набор юнит-тестов. 
    Пришлите на проверку файл simple_vector.h с реализацией оператора присваивания.
*/
#include "simple_vector.h"
#include "test_runner.h"

#include <numeric>
#include <vector>
#include <tuple>

void TestCopyAssignment()
{
    SimpleVector<int> numbers(10);
    std::iota(numbers.begin(), numbers.end(), 1);

    SimpleVector<int> dest;
    ASSERT_EQUAL(dest.Size(), 0u);

    dest = numbers;
    ASSERT_EQUAL(dest.Size(), numbers.Size());
    ASSERT(dest.Capacity() >= dest.Size());
    ASSERT(std::equal(dest.begin(), dest.end(), numbers.begin()));
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestCopyAssignment);
}