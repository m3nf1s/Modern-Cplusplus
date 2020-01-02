/*
    В заготовке решения задачи «Шаблон Synchronized» мы уже слегка коснулись идеи о том,
    что уменьшение размера критической секции позволяет повысить скорость работы многопоточной программы. 
    В этой задаче мы разовьём её больше.
    
    Давайте представим, что у нас есть map, к которому обращаются несколько потоков.
    Чтобы синхронизировать доступ к нему, мы можем каждое обращение к этому map'у
    защитить мьютексом (например, завернув наш map в шаблон Synchronized).
    Теперь давайте представим, что у нас есть Synchronized<map<int, int>>, в котором хранятся все ключи от 1 до 10000.
    Интуитивно кажется, что когда из одного потока мы обращаемся к ключу 10, а из другого — например, к ключу 6712,
    то нет смысла защищать эти обращения одним и тем же мьютексом.
    Это отдельные области памяти, а внутреннюю структуру словаря мы никак не изменяем.
    При этом, если мы будем обращаться к ключу 6712 одновременно из нескольких потоков,
    то синхронизация, несомненно, понадобится.
    
    Отсюда возникает идея — разбить наш словарь на нескольких подсловарей
    с непересекающимся набором ключей и защитить каждый из них отдельным мьютексом.
    Тогда при обращении разных потоков к разным ключам они нечасто будут попадать в один и тот же подсловарь,
    а значит, смогут параллельно его обрабатывать.
    Эту идею вам предстоит реализовать в этой задаче.

    *   static_assert в начале класса говорит, что в данной задаче предполагается,
            что ключами ConcurrentMap'а могут быть только целые числа.
    *   Конструктор класса ConcurrentMap<K, V> принимает количество подсловарей,
            на которые надо разбить всё пространство ключей.
    *   operator[] должен вести себя так же, как аналогичный оператор у map — если ключ key присутствует в словаре,
            он должен возвращать объект класса Access, содержащий ссылку на соответствующее ему значение;
            если же key отсутствует в словаре, в него надо добавить пару (key, V()) и вернуть объект класса Access,
            содержащий ссылку на только что добавленное значение.
    *   Структура Access, должна вести себя так же, как и в шаблоне Synchronized, — предоставлять ссылку
            на значение словаря и обеспечивать синхронизацию доступа к нему.
    *   Метод BuildOrdinaryMap должен сливать вместе части словаря и возвращать весь словарь целиком.
            При этом он должен быть потокобезопасным, то есть корректно работать,
            когда другие потоки выполняют операции с ConcurrentMap.
*/
#include "test_runner.h"
#include "profile.h"

#include <algorithm>
#include <numeric>
#include <vector>
#include <string>
#include <random>
#include <future>
#include <mutex>
#include <map>

template <typename T>
T Abs(T x)
{
    return x < 0 ? (-1) * x : x;
}

auto Lock(std::mutex& m)
{
    return std::lock_guard<std::mutex>{m};
}

template <typename K, typename V>
class ConcurrentMap
{
private:
    std::vector<std::pair<std::mutex, std::map<K, V>>> segments;

public:
    static_assert(std::is_convertible_v<K, uint64_t>, "ConcurrentMap supports only integer keys");

    struct Access
    {
        std::lock_guard<std::mutex> guard;
        V& ref_to_value;

        Access(const K& key, std::pair<std::mutex, std::map<K,V>>& segment)
            : guard(segment.first)
            , ref_to_value(segment.second[key])
        {}
    };

    explicit ConcurrentMap(size_t bucket_count)
        : segments(bucket_count)
    {
    }

    Access operator[](const K& key)
    {
        std::pair<std::mutex, std::map<K, V>>& segment = segments[Abs(key) % segments.size()];
        return { key, segment };
    }

    std::map<K, V> BuildOrdinaryMap()
    {
        std::map<K, V> result;

        for (auto& [mutex, segment] : segments)
        {
            auto g = Lock(mutex);
            result.insert(segment.begin(), segment.end());
        }

        return result;
    }
};

void RunConcurrentUpdates(ConcurrentMap<int, int>& cm, size_t thread_count, int key_count)
{
    auto kernel = [&cm, key_count](int seed) 
    {
        std::vector<int> updates(key_count);
        std::iota(std::begin(updates), std::end(updates), -key_count / 2);
        std::shuffle(std::begin(updates), std::end(updates), std::default_random_engine(seed));

        for (int i = 0; i < 2; ++i) 
        {
            for (auto key : updates)
            {
                cm[key].ref_to_value++;
            }
        }
    };

    std::vector<std::future<void>> futures;
    for (size_t i = 0; i < thread_count; ++i) 
    {
        futures.push_back(std::async(kernel, i));
    }
}

void TestConcurrentUpdate() 
{
    const size_t thread_count = 3;
    const size_t key_count = 50000;

    ConcurrentMap<int, int> cm(thread_count);
    RunConcurrentUpdates(cm, thread_count, key_count);

    const auto result = cm.BuildOrdinaryMap();
    ASSERT_EQUAL(result.size(), key_count);
    for (auto& [k, v] : result) 
    {
        AssertEqual(v, 6, "Key = " + std::to_string(k));
    }
}

void TestReadAndWrite() 
{
    ConcurrentMap<size_t, std::string> cm(5);

    auto updater = [&cm]
    {
        for (size_t i = 0; i < 50000; ++i)
        {
            cm[i].ref_to_value += 'a';
        }
    };
    auto reader = [&cm]
    {
        std::vector<std::string> result(50000);
        for (size_t i = 0; i < result.size(); ++i) 
        {
            result[i] = cm[i].ref_to_value;
        }
        return result;
    };

    auto u1 = std::async(updater);
    auto r1 = std::async(reader);
    auto u2 = std::async(updater);
    auto r2 = std::async(reader);

    u1.get();
    u2.get();

    for (auto f : { &r1, &r2 })
    {
        auto result = f->get();
        ASSERT(std::all_of(result.begin(), result.end(), [](const std::string& s) 
            {
                return s.empty() || s == "a" || s == "aa";
            }));
    }
}

void TestSpeedup() 
{
    {
        ConcurrentMap<int, int> single_lock(1);

        LOG_DURATION("Single lock");
        RunConcurrentUpdates(single_lock, 4, 50000);
    }
    {
        ConcurrentMap<int, int> many_locks(100);

        LOG_DURATION("100 locks");
        RunConcurrentUpdates(many_locks, 4, 50000);
    }
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestConcurrentUpdate);
    RUN_TEST(tr, TestReadAndWrite);
    RUN_TEST(tr, TestSpeedup);
}
