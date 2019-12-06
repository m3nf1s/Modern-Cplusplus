/*
    В блоке про модель памяти мы говорили, что динамическая память нужна для хранения тех объектов,
        которые должны жить дольше, чем создавшая их функция.
    Кроме того мы говорили, что можно создать такой вектор, который не использует память из кучи, а хранит все свои объекты на стеке.
    В этой задаче вам предстоит это сделать.
    Вы совсем недавно познакомились с контейнером array, который хранит все свои данные на стеке.
    Реализуйте интерфейс вектора поверх него.
    Более формально, реализуйте шаблон класса template <typename T, size_t N> StackVector<T, N>,
        где T — тип элемента вектора, а N — его максимальная вместимость.
    
    *   Метод Capacity должен возвращать вместимость вектора, то есть количество объектов,
            которое в него в принципе может поместиться.
    *   Метод Size должен возвращать текущее количество объектов в векторе
    *   Конструктор принимает размер вектора (по аналогии со стандартным вектором).
        Если аргумент конструктора оказался больше вместимости вектора, конструктор должен выбрасывать исключение invalid_argument
    *   Методы begin/end должны возвращать итераторы на начало и текущий конец вектора;
        их тип не указан, вы должны выбрать его самостоятельно
    *   Метод PushBack добавляет новый элемент в конец вектора.
        Если текущий размер вектора равен его вместимости,
            метод PushBack должен выбрасывать стандартное исключение overflow_error
    *   Метод PopBack уменьшает размер вектора на один и возвращает элемент вектора, который был последним.
        Если вектор пуст, метод PopBack должен выбрасывать стандартное исключение underflow_error

    Интерфейс класса StackVector описан в файле stack_vector.h, приложенном к этой задаче.
    Часть требований к нему сформулирована в виде юнит-тестов в файле stack_vector.cpp.

    Обратите внимание, как отличается поведение метода PushBack в классе StackVector от метода PushBack в классе SimpleVector,
        который вы реализовывали ранее в блоке про модель памяти.
    SimpleVector::PushBack выделял дополнительную память в куче, если размер вектора оказывался равен ёмкости.
    В случае с классом StackVector мы должны на этапе компиляции задать максимальную ёмкость вектора и,
        если она оказывается исчерпана, нам больше неоткуда взять память, и мы просто бросаем исключение.
    В этом состоит недостаток реализации вектора на стеке по сравнению с обычным вектором.
    
    С другой стороны, файл stack_vector.cpp содержит бенчмарк, который демонстрирует преимущество StackVector перед обычным вектором.
    Этот бенчмарк моделирует ситуацию, когда мы считываем из потока количество объектов N,
        а затем добавляем в вектор N объектов с помощью метода push_back (тестовые данные разложены в vector<vector<int>>,
        чтобы исключить из бенчмарка время, необходимое на парсинг).
    Когда вы реализуете шаблон StackVector, сравните его производительность с вектором.
*/

#include "stack_vector.h"

#include "test_runner.h"
#include "profiler.h"

#include <random>
#include <stdexcept>

void TestConstruction()
{
    StackVector<int, 10> v;
    ASSERT_EQUAL(v.Size(), 0u);
    ASSERT_EQUAL(v.Capacity(), 10u);

    StackVector<int, 8> u(5);
    ASSERT_EQUAL(u.Size(), 5u);
    ASSERT_EQUAL(u.Capacity(), 8u);

    try
    {
        StackVector<int, 10> u(50);
        Assert(false, "Expect invalid_argument for too large size");
    }
    catch (std::invalid_argument&)
    {
    }
    catch (...)
    {
        Assert(false, "Unexpected exception for too large size");
    }
}

void TestPushBack()
{
    StackVector<int, 5> v;
    for (size_t i = 0; i < v.Capacity(); ++i)
    {
        v.PushBack(i);
    }

    try
    {
        v.PushBack(0);
        Assert(false, "Expect overflow_error for PushBack in full vector");
    }
    catch (std::overflow_error&)
    {
    }
    catch (...)
    {
        Assert(false, "Unexpected exception for PushBack in full vector");
    }
}

void TestPopBack()
{
    StackVector<int, 5> v;
    for (size_t i = 1; i <= v.Capacity(); ++i)
    {
        v.PushBack(i);
    }
    for (int i = v.Size(); i > 0; --i)
    {
        ASSERT_EQUAL(v.PopBack(), i);
    }

    try
    {
        v.PopBack();
        Assert(false, "Expect underflow_error for PopBack from empty vector");
    }
    catch (std::underflow_error&)
    {
    }
    catch (...)
    {
        Assert(false, "Unexpected exception for PopBack from empty vector");
    }
}

int main()
{
    {
        TestRunner tr;
        RUN_TEST(tr, TestConstruction);
        RUN_TEST(tr, TestPushBack);
        RUN_TEST(tr, TestPopBack);
    }

    std::cerr << "Running benchmark..." << std::endl;
    const size_t max_size = 2500;

    std::default_random_engine re;
    std::uniform_int_distribution<int> value_gen(1, max_size);

    std::vector<std::vector<int>> test_data(50000);
    for (auto& cur_vec : test_data)
    {
        cur_vec.resize(value_gen(re));
        for (int& x : cur_vec)
        {
            x = value_gen(re);
        }
    }

    {
        LOG_DURATION("vector w/o reserve");
        for (auto& cur_vec : test_data)
        {
            std::vector<int> v;
            for (int x : cur_vec)
            {
                v.push_back(x);
            }
        }
    }
    {
        LOG_DURATION("vector with reserve");
        for (auto& cur_vec : test_data)
        {
            std::vector<int> v;
            v.reserve(cur_vec.size());
            for (int x : cur_vec)
            {
                v.push_back(x);
            }
        }
    }
    {
        LOG_DURATION("StackVector");
        for (auto& cur_vec : test_data)
        {
            StackVector<int, max_size> v;
            for (int x : cur_vec)
            {
                v.PushBack(x);
            }
        }
    }
    std::cerr << "Done" << std::endl;
}
