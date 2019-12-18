/*
    Реализуйте шаблонный контейнер PriorityCollection, позволяющий хранить объекты некопируемого типа,
    а также совершать с ними следующие операции:
    *   добавить элемент с нулевым приоритетом;
    *   добавить набор элементов с нулевыми приоритетами;
    *   увеличить на 1 приоритет заданного элемента;
    *   извлечь из контейнера элемент с максимальным приоритетом.
    
    Поскольку добавление элемента заключается в его перемещении в контейнер,
    метод увеличения приоритета не может принимать сам элемент.
    Поэтому метод, добавляющий элементы, для каждого из них должен вернуть некий идентификатор,
    который затем можно использовать для вызова других методов.
    
    Тип идентификатора — PriorityCollection::Id — вы должны выбрать самостоятельно.
    Он должен быть легко копируемым: например, числом, указателем или итератором.
    Примеры определения и использования типа Id вы можете найти в шаблоне решения.

    Гарантии
    1.  Вы можете полагаться на то, что для элементов типа T определены перемещение и сравнение на ==, != и <.
        Все операции над элементами имеют константную сложность.
    2.  Гарантируется, что все добавляемые элементы различны,
        однако добавленный и затем извлечённый элемент может быть добавлен вновь.
    3.  Методы Get и Promote всегда вызываются от валидных с точки зрения метода IsValid идентификаторов.
    4.  Методы GetMax и PopMax вызываются только при наличии элементов в контейнере.
    5.  При наличии нескольких элементов с одинаковым максимальным приоритетом необходимо выбирать и извлекать тот,
        который был добавлен позже остальных.

    Ограничения
    Контейнер должен обрабатывать 10^6 запросов не более чем за 1 секунду.
    Гарантируется, что суммарная длина диапазонов, с которыми вызывается вторая версия метода Add, также не превосходит 10^6.
*/

#include "test_runner.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <utility>
#include <vector>

template <typename T>
class PriorityCollection 
{
public:
    using Id = int;

    // Добавить объект с нулевым приоритетом
    // с помощью перемещения и вернуть его идентификатор
    Id Add(T object)
    {   
        const Id new_id = objects_.size();
        sorted_.insert(std::pair(0, new_id));
        objects_.push_back({ std::move(object) });
        return new_id;
    }

    // Добавить все элементы диапазона [range_begin, range_end)
    // с помощью перемещения, записав выданные им идентификаторы
    // в диапазон [ids_begin, ...)
    template <typename ObjInputIt, typename IdOutputIt>
    void Add(ObjInputIt range_begin, ObjInputIt range_end, IdOutputIt ids_begin)
    {
        while (range_begin != range_end)
        {
            *(ids_begin++) = Add(std::move(*range_begin++));
        }
    }

    // Определить, принадлежит ли идентификатор какому-либо
    // хранящемуся в контейнере объекту
    bool IsValid(Id id) const
    {
        return id >= 0 && id < objects_.size() && objects_[id] != NONE_PRIORITY;
    }

    // Получить объект по идентификатору
    const T& Get(Id id) const
    {        
        return objects_[id].data;
    }

    // Увеличить приоритет объекта на 1
    void Promote(Id id)
    {
        auto& item = objects_[id];
        const int old_priority = item.priority;
        const int new_priority = ++item.priority;
        sorted_.erase({old_priority, id});
        sorted_.insert({ new_priority, id });
    }

    // Получить объект с максимальным приоритетом и его приоритет
    std::pair<const T&, int> GetMax() const
    {
        const auto& last_item = objects_[std::prev(sorted_.end())->second];
        return pair(last_item.data, last_item.priority);
    }

    // Аналогично GetMax, но удаляет элемент из контейнера
    std::pair<T, int> PopMax()
    {
        const auto sorted_objects_it = prev(sorted_.end());
        auto& item = objects_[sorted_objects_it->second];
        sorted_.erase(sorted_objects_it);
        const int priority = item.priority;
        item.priority = NONE_PRIORITY;
        return { move(item.data), priority };
    }

private:
    struct ObjectItem
    {
        T data;
        int priority = 0;
    };
    const static int NONE_PRIORITY = -1;
    std::set<std::pair<int, Id>> sorted_;
    std::vector<ObjectItem> objects_;
};

class StringNonCopyable : public std::string
{
public:
    using std::string::string;  // Позволяет использовать конструкторы строки
    StringNonCopyable(const StringNonCopyable&) = delete;
    StringNonCopyable(StringNonCopyable&&) = default;
    StringNonCopyable& operator=(const StringNonCopyable&) = delete;
    StringNonCopyable& operator=(StringNonCopyable&&) = default;
};

void TestNoCopy() 
{
    PriorityCollection<StringNonCopyable> strings;
    const auto white_id = strings.Add("white");
    const auto yellow_id = strings.Add("yellow");
    const auto red_id = strings.Add("red");

    strings.Promote(yellow_id);
    for (int i = 0; i < 2; ++i) 
    {
        strings.Promote(red_id);
    }
    strings.Promote(yellow_id);
    {
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "red");
        ASSERT_EQUAL(item.second, 2);
    }
    {
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "yellow");
        ASSERT_EQUAL(item.second, 2);
    }
    {
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "white");
        ASSERT_EQUAL(item.second, 0);
    }
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestNoCopy);
    return 0;
}
