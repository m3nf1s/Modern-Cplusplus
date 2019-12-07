/*
    Вам необходимо разработать простейшую систему сбора статистики вылетов для небольших авиакомпаний.
    Высокоуровнево требования выглядят следующим образом:

    1.  Система сбора статистики должна представлять собой класс AirportCounter,
            умеющий в произвольный момент времени для заданного аэропорта вернуть текущее количество вылетов из него.
    2.  Набор возможных аэропортов фиксирован в виде enum и потому не может изменяться в рамках одного сеанса
            работы системы статистики, то есть в рамках одного экземпляра AirportCounter.
        Таким образом, класс AirportCounter необходимо шаблонизировать типом этого enum:
            если назвать такой enum TAirport, получим шаблонный класс AirportCounter<TAirport>.
    3.  Гарантируется (по крайней мере, обещано заказчиком),
            что по enum аэропортов можно будет легко определить количество элементов в нём,
            а также перебрать сами элементы.
        А именно, любой используемый enum будет иметь вид enum class SomeCityAirport { Airport1, Airport2, ..., AirportN, Last_ };,
            то есть будет содержать некоторое количество элементов-аэропортов и элемент Last_ в качестве последнего.
        Поскольку в этом enum не будут заданы числовые значения для элементов, можно полагаться на то,
            что они будут пронумерованы подряд от 0 до N-1, а выражение static_cast<uint32_t>(SomeCityAirport::Last_)
            будет содержать количество аэропортов (N).
    4.  Класс должен уметь конструироваться по списку аэропортов вылета,
            а также позволять обновлять этот список: добавить вылет из какого-то аэропорта,
            удалить один вылет (например, ошибочно добавленный) или удалить из истории все вылеты из некоторого аэропорта.
    
    Тестирование
    Прежде чем перейти к более детальному описанию интерфейса класса, опишем процесс тестирования задачи.

    Вам будут даны все тесты, на которых будет проверяться шаблонный класс AirportCounter.
    Ваша задача — добиться не только корректной работы на этих тестах, но и уложиться на них в 2 секунды.
    (Считайте, что заказчик предоставил вам подробнейшие сценарии использования вашего класса,
        которые затем были преобразованы в конкретные бенчмарки.)

    Таким образом, вы должны выбрать способ реализации класса, ориентируясь лишь на конкретные бенчмарки.

    Отметим, что данные бенчмарки составлены на основе реального примера из высоконагруженного сервиса,
        замедление которого даже на десятки процентов недопустимо.
    Именно поэтому в этой задаче важно не только спроектировать решение с приемлемой асимптотической сложностью,
        но и «разогнать» его на конкретных примерах.
*/
#include "profiler.h"
#include "test_runner.h"

#include <algorithm>
#include <array>
#include <iostream>
#include <random>
#include <vector>
#include <map>

template <typename TAirport>
class AirportCounter
{
public:
    AirportCounter()
    {
        airport_system_.fill(0);
    }

    template <typename TIterator>
    AirportCounter(TIterator begin, TIterator end)
        : AirportCounter()
    {
        for (; begin != end; ++begin)
        {
            ++airport_system_[static_cast<size_t>(*begin)];
        }
    }

    size_t Get(TAirport airport) const
    {
        return airport_system_[static_cast<size_t>(airport)];
    }

    void Insert(TAirport airport)
    {
        ++GetCountDepartures(airport);
    }

    void EraseOne(TAirport airport)
    {
        if (GetCountDepartures(airport) > 0)
        {
            --GetCountDepartures(airport);
        }
    }

    void EraseAll(TAirport airport)
    {
        airport_system_[static_cast<size_t>(airport)] = 0;
    }

    using Item = std::pair<TAirport, size_t>;
    using Items = std::array<Item, static_cast<size_t>(TAirport::Last_)>;
    
    Items GetItems() const
    {
        Items items;

        for (size_t i = 0; i < airport_system_.size(); ++i)
        {
            items[i] = { static_cast<TAirport>(i), airport_system_[i] };
        }
        return items;
    }

private:
    std::array<size_t, static_cast<size_t>(TAirport::Last_)> airport_system_;

    size_t& GetCountDepartures(TAirport airport)
    {
        return airport_system_[static_cast<size_t>(airport)];
    }
};

void TestMoscow()
{
    enum class MoscowAirport
    {
        VKO,
        SVO,
        DME,
        ZIA,
        Last_
    };

    const std::vector<MoscowAirport> airports =
    {
        MoscowAirport::SVO,
        MoscowAirport::VKO,
        MoscowAirport::ZIA,
        MoscowAirport::SVO,
    };
    AirportCounter<MoscowAirport> airport_counter(std::begin(airports), std::end(airports));

    ASSERT_EQUAL(airport_counter.Get(MoscowAirport::VKO), 1);
    ASSERT_EQUAL(airport_counter.Get(MoscowAirport::SVO), 2);
    ASSERT_EQUAL(airport_counter.Get(MoscowAirport::DME), 0);
    ASSERT_EQUAL(airport_counter.Get(MoscowAirport::ZIA), 1);

    using Item = AirportCounter<MoscowAirport>::Item;
    std::vector<Item> items;
    for (const auto& item : airport_counter.GetItems())
    {
        items.push_back(item);
    }
    ASSERT_EQUAL(items.size(), 4);

#define ASSERT_EQUAL_ITEM(idx, expected_enum, expected_count)                                                   \
    do                                                                                                          \
    {                                                                                                           \
        ASSERT_EQUAL(static_cast<size_t>(items[idx].first), static_cast<size_t>(MoscowAirport::expected_enum)); \
        ASSERT_EQUAL(items[idx].second, expected_count);                                                        \
    } while (false)

    ASSERT_EQUAL_ITEM(0, VKO, 1);
    ASSERT_EQUAL_ITEM(1, SVO, 2);
    ASSERT_EQUAL_ITEM(2, DME, 0);
    ASSERT_EQUAL_ITEM(3, ZIA, 1);

    airport_counter.Insert(MoscowAirport::VKO);
    ASSERT_EQUAL(airport_counter.Get(MoscowAirport::VKO), 2);

    airport_counter.EraseOne(MoscowAirport::SVO);
    ASSERT_EQUAL(airport_counter.Get(MoscowAirport::SVO), 1);

    airport_counter.EraseAll(MoscowAirport::VKO);
    ASSERT_EQUAL(airport_counter.Get(MoscowAirport::VKO), 0);
}

enum class SmallCountryAirports
{
    Airport_1,
    Airport_2,
    Airport_3,
    Airport_4,
    Airport_5,
    Airport_6,
    Airport_7,
    Airport_8,
    Airport_9,
    Airport_10,
    Airport_11,
    Airport_12,
    Airport_13,
    Airport_14,
    Airport_15,
    Last_
};

void TestManyConstructions()
{
    std::default_random_engine rnd(20180623);
    std::uniform_int_distribution<size_t> gen_airport(
        0, static_cast<size_t>(SmallCountryAirports::Last_) - 1
    );

    std::array<SmallCountryAirports, 2> airports;
    for (auto& x : airports)
    {
        x = static_cast<SmallCountryAirports>(gen_airport(rnd));
    }

    uint64_t total = 0;
    for (int step = 0; step < 100'000'000; ++step)
    {
        AirportCounter<SmallCountryAirports> counter(begin(airports), end(airports));
        total += counter.Get(SmallCountryAirports::Airport_1);
    }
    ASSERT(total < 1000);
}

enum class SmallTownAirports
{
    Airport_1,
    Airport_2,
    Last_
};

void TestManyGetItems()
{
    std::default_random_engine rnd(20180701);
    std::uniform_int_distribution<size_t> gen_airport(
        0, static_cast<size_t>(SmallTownAirports::Last_) - 1
    );

    std::array<SmallTownAirports, 2> airports;
    for (auto& x : airports)
    {
        x = static_cast<SmallTownAirports>(gen_airport(rnd));
    }

    uint64_t total = 0;
    for (int step = 0; step < 100'000'000; ++step)
    {
        AirportCounter<SmallTownAirports> counter(begin(airports), end(airports));
        total += counter.Get(SmallTownAirports::Airport_1);
        for (const auto [airport, count] : counter.GetItems())
        {
            total += count;
        }
    }
    ASSERT(total > 0);
}

void TestMostPopularAirport()
{
    std::default_random_engine rnd(20180624);
    std::uniform_int_distribution<size_t> gen_airport(
        0, static_cast<size_t>(SmallCountryAirports::Last_) - 1
    );

    std::array<std::pair<SmallCountryAirports, SmallCountryAirports>, 1000> dayly_flight_report;
    for (auto& x : dayly_flight_report)
    {
        x =
        {
          static_cast<SmallCountryAirports>(gen_airport(rnd)),
          static_cast<SmallCountryAirports>(gen_airport(rnd))
        };
    }

    const int days_to_explore = 365 * 500;

    std::vector<SmallCountryAirports> most_popular(days_to_explore);

    for (int day = 0; day < days_to_explore; ++day)
    {
        AirportCounter<SmallCountryAirports> counter;
        for (const auto& [source, dest] : dayly_flight_report)
        {
            counter.Insert(source);
            counter.Insert(dest);
        }

        const auto items = counter.GetItems();
        most_popular[day] = std::max_element(std::begin(items), std::end(items), [](auto lhs, auto rhs)
            {
                return lhs.second < rhs.second;
            })->first;
    }

    ASSERT(all_of(begin(most_popular), end(most_popular), [&](SmallCountryAirports a)
        {
        return a == most_popular.front();
        }));
}

int main()
{
    TestRunner tr;

    // По условию, суммарное время работы всех тестов не должно превышать
    // двух секунд. Если ваше время будет лишь чуть больше двух секунд,
    // попробуйте отправить ваше решение в тестирующую систему. Возможно,
    // там более мощное железо, и ваше решение будет принято.

    // Кроме того, не забудьте включить оптимизации при компиляции кода.

    LOG_DURATION("Total tests duration");
    RUN_TEST(tr, TestMoscow);
    RUN_TEST(tr, TestManyConstructions);
    RUN_TEST(tr, TestManyGetItems);
    RUN_TEST(tr, TestMostPopularAirport);
    return 0;
}