/*
    Мы хотим научиться встраивать структуру Point3D в контейнер unordered_set<Point3D, Hasher>.
    Для этого вам нужно реализовать структуру Hasher и оператор сравнения.

    В своей реализации используйте стандартную хеш-функцию std::hash<CoordType>
    для хеширования координат и комбинируйте полученные хеши с помощью полинома, как показано в лекции.
    
    Требования:
    
    *   хеш-функция должна зависеть от всех координат точки
    *   хеш-функция должна равномерно рассеивать точки в трёхмерном пространстве;
        это её свойство проверяется тестом TestDistribution в заготовке решения.
*/

#include "test_runner.h"

#include <limits>
#include <random>
#include <unordered_set>
#include <tuple>
#include <cmath>

using CoordType = int;

struct Point3D
{
    CoordType x;
    CoordType y;
    CoordType z;

    bool operator==(const Point3D& other) const 
    {
        return std::tie(x, y, z) == std::tie(other.x, other.y, other.z);
    }
};

struct Hasher 
{
    size_t operator() (const Point3D& point) const
    {
        const size_t x = 2'946'901;
        const std::hash<CoordType> coord_hash;
        
        return (coord_hash(point.x) * x * x + coord_hash(point.y) * x + coord_hash(point.z));
    }
};

void TestSmoke()
{
    std::vector<Point3D> points = 
    {
      {1, 2, 3},
      {0, 2, 3},
      {1, 0, 3},
      {1, 2, 0},
    };

    std::unordered_set<Point3D, Hasher> point_set;
    for (const auto& point : points) 
    {
        point_set.insert(point);
    }

    ASSERT_EQUAL(points.size(), point_set.size());
    for (const auto& point : points)
    {
        ASSERT_EQUAL(point_set.count(point), static_cast<size_t>(1));
    }
}

void TestPurity()
{
    Point3D point = { 1, 2, 3 };
    Hasher hasher;

    auto hash = hasher(point);
    for (size_t t = 0; t < 100; ++t)
    {
        ASSERT_EQUAL(hasher(point), hash);
    }
};

void TestX() {
    auto seed = 42;
    std::mt19937 gen(seed);
    std::uniform_int_distribution<CoordType> dist(
        std::numeric_limits<CoordType>::min(),
        std::numeric_limits<CoordType>::max()
    );

    Hasher hasher;

    bool component_matters = false;
    for (size_t t = 0; t < 1000; ++t) 
    {
        Point3D point = { dist(gen), dist(gen), dist(gen) };
        Point3D other_point = point;
        other_point.x = dist(gen);

        component_matters |= (hasher(point) != hasher(other_point));
    }

    ASSERT(component_matters);
}

void TestY()
{
    auto seed = 42;
    std::mt19937 gen(seed);
    std::uniform_int_distribution<CoordType> dist(
        std::numeric_limits<CoordType>::min(),
        std::numeric_limits<CoordType>::max()
    );

    Hasher hasher;

    bool component_matters = false;
    for (size_t t = 0; t < 1000; ++t) 
    {
        Point3D point = { dist(gen), dist(gen), dist(gen) };
        Point3D other_point = point;
        other_point.y = dist(gen);

        component_matters |= (hasher(point) != hasher(other_point));
    }

    ASSERT(component_matters);
}

void TestZ() 
{
    auto seed = 42;
    std::mt19937 gen(seed);
    std::uniform_int_distribution<CoordType> dist(
        std::numeric_limits<CoordType>::min(),
        std::numeric_limits<CoordType>::max()
    );

    Hasher hasher;

    bool component_matters = false;
    for (size_t t = 0; t < 1000; ++t)
    {
        Point3D point = { dist(gen), dist(gen), dist(gen) };
        Point3D other_point = point;
        other_point.z = dist(gen);

        component_matters |= (hasher(point) != hasher(other_point));
    }

    ASSERT(component_matters);
}

void TestDistribution()
{
    auto seed = 42;
    std::mt19937 gen(seed);
    std::uniform_int_distribution<CoordType> dist(
        std::numeric_limits<CoordType>::min(),
        std::numeric_limits<CoordType>::max()
    );

    Hasher hasher;

    // выбираем число бакетов не очень большим простым числом
    // (unordered_set, unordered_map используют простые числа бакетов
    // в реализациях GCC и Clang, для непростых чисел бакетов
    // возникают сложности со стандартной хеш-функцией в этих реализациях)
    const size_t num_buckets = 2053;

    // мы хотим, чтобы число точек в бакетах было ~100'000
    const size_t perfect_bucket_size = 50;
    const size_t num_points = num_buckets * perfect_bucket_size;
    std::vector<size_t> buckets(num_buckets);
    for (size_t t = 0; t < num_points; ++t) 
    {
        Point3D point = { dist(gen), dist(gen), dist(gen) };
        ++buckets[hasher(point) % num_buckets];
    }

    // Статистика Пирсона:
    // https://en.wikipedia.org/wiki/Pearson's_chi-squared_test
    //
    // Численной мерой равномерности распределения также может выступать
    // энтропия, но для ее порогов нет хорошей статистической интерпретации
    double pearson_stat = 0;
    for (auto bucket_count : buckets) 
    {
        size_t count_diff = bucket_count - perfect_bucket_size;
        pearson_stat +=
            count_diff * count_diff / static_cast<double>(perfect_bucket_size);
    }

    // проверяем равномерность распределения методом согласия Пирсона
    // со статистической значимостью 0.95:
    //
    // если подставить вместо ++buckets[hasher(point) % num_buckets]
    // выражение ++buckets[dist(gen) % num_buckets], то с вероятностью 95%
    // ASSERT ниже отработает успешно,
    //
    // т.к. статистика Пирсона приблизительно распределена по chi^2
    // с числом степеней свободы, равным num_buckets - 1,
    // и 95 процентиль этого распределения равен:
    // >>> scipy.stats.chi2.ppf(0.95, 2052)
    const double critical_value = 2158.4981036918693;
    ASSERT(pearson_stat < critical_value);
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestSmoke);
    RUN_TEST(tr, TestPurity);
    RUN_TEST(tr, TestX);
    RUN_TEST(tr, TestY);
    RUN_TEST(tr, TestZ);
    RUN_TEST(tr, TestDistribution);

    return 0;
}
