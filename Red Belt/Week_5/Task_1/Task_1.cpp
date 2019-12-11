/*
    Дан диапазон объектов некоторого типа.
    Напишите функцию, переставляющую его элементы в соответствии с порядком,
        определённым так называемой считалкой Иосифа с заданным размером шага.
    Гарантируется, что итераторы range_begin и range_end являются итераторами произвольного доступа,
        то есть допускают вычитание одного из другого и сложение с числом.
    Кроме того, вы можете полагаться на то, что step_size > 0.
    Тип переупорядочиваемых объектов можно получить с помощью выражения typename RandomIt::value_type.
    Объекты этого типа запрещено копировать.
    При наличии копирования этих объектов вы получите ошибку компиляции.

    Ограничения
    Максимальный размер диапазона — 10^5, максимальный размер шага — 10^2.
    Время выполнения одного вызова функции ограничено 1 секундой.

    Решение с копированиями
    Вам дано решение данной задачи, копирующее элементы и не укладывающееся в ограничения по времени, но в остальном корректное.
    Вы можете исправить его или написать своё.
*/

#include "test_runner.h"

#include <cstdint>
#include <iterator>
#include <numeric>
#include <vector>
#include <utility>
#include <list>

template <typename RandomIt>
void MakeJosephusPermutation(RandomIt first, RandomIt last, uint32_t step_size)
{
    std::list<typename RandomIt::value_type> pool;
    std::move(first, last, std::back_inserter(pool));

    int cur_pos = 0;
    int last_pos = 0;
    auto it = pool.begin();

    while (!pool.empty())
    {
        *(first++) = std::move(*it);

        pool.erase(it++);

        if (pool.empty())
        {
            break;
        }

        last_pos = cur_pos;
        cur_pos = (cur_pos + step_size - 1) % pool.size();

        std::advance(it, (cur_pos - last_pos));
    }
}

std::vector<int> MakeTestVector() 
{
    std::vector<int> numbers(10);
    std::iota(std::begin(numbers), std::end(numbers), 0);
    return numbers;
}

void TestIntVector() 
{
    const std::vector<int> numbers = MakeTestVector();
    {
        std::vector<int> numbers_copy = numbers;
        MakeJosephusPermutation(begin(numbers_copy), end(numbers_copy), 1);
        ASSERT_EQUAL(numbers_copy, numbers);
    }
    {
        std::vector<int> numbers_copy = numbers;
        MakeJosephusPermutation(begin(numbers_copy), end(numbers_copy), 3);
        ASSERT_EQUAL(numbers_copy, std::vector<int>({ 0, 3, 6, 9, 4, 8, 5, 2, 7, 1 }));
    }
}

// Это специальный тип, который поможет вам убедиться, что ваша реализация
// функции MakeJosephusPermutation не выполняет копирование объектов.
// Сейчас вы, возможно, не понимаете как он устроен, однако мы расскажем,
// почему он устроен именно так, далее в блоке про move-семантику —
// в видео «Некопируемые типы»

struct NoncopyableInt 
{
    int value;

    NoncopyableInt(const NoncopyableInt&) = delete;
    NoncopyableInt& operator=(const NoncopyableInt&) = delete;

    NoncopyableInt(NoncopyableInt&&) = default;
    NoncopyableInt& operator=(NoncopyableInt&&) = default;
};

bool operator == (const NoncopyableInt& lhs, const NoncopyableInt& rhs) 
{
    return lhs.value == rhs.value;
}

std::ostream& operator << (std::ostream& os, const NoncopyableInt& v) 
{
    return os << v.value;
}

void TestAvoidsCopying() 
{
    std::vector<NoncopyableInt> numbers;
    numbers.push_back({ 1 });
    numbers.push_back({ 2 });
    numbers.push_back({ 3 });
    numbers.push_back({ 4 });
    numbers.push_back({ 5 });

    MakeJosephusPermutation(std::begin(numbers), std::end(numbers), 2);

    std::vector<NoncopyableInt> expected;
    expected.push_back({ 1 });
    expected.push_back({ 3 });
    expected.push_back({ 5 });
    expected.push_back({ 4 });
    expected.push_back({ 2 });

    ASSERT_EQUAL(numbers, expected);
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestIntVector);
    RUN_TEST(tr, TestAvoidsCopying);
    return 0;
}