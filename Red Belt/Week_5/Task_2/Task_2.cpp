/*
    Дан набор строк.
    Необходимо разбить их на группы, в каждой из которых все строки имеют одинаковый набор символов.
    
    Например, если даны строки law, port, top, laptop, pot, paloalto, wall, awl, нужно разбить их на 4 группы:
    *   строки, состоящие только из букв a, l и w: law, wall, awl;
    *   строки, состоящие только из букв o, p, r и t: port;
    *   строки, состоящие только из букв o, p и t: top, pot;
    *   строки, состоящие только из букв a, l, o, p, t: laptop, paloalto.

    Разбиение на группы должно быть реализовано в виде функции
    Здесь Group<String> — синоним для vector<String>.
    Наличие такого синонима позволяет записать возвращаемый тип функции GroupHeavyString в виде vector<Group<String>>,
        что читается понятнее, чем vector<vector<String>>.
    
    Слова в каждой группе должны располагаться в том же порядке, что и в исходном наборе.
    При этом порядок самих групп значения не имеет.
    
    Строка типа String не обязана состоять из символов типа char.
    Тип символа можно получить с помощью выражения typename String::value_type или Char<String>,
        если определить соответствующий синоним.
    
    Сам тип String может быть, например, обычной строкой (string) или вектором символов.
    
    Про тип Char<String> известно следующее:
    
    Объекты этого типа можно сравнивать с помощью операторов == и <.
    «Тяжёлыми» могут быть не только сами строки, но и отдельные символы.
    Поэтому их можно свободно перемещать, но скопировать каждый символ в функции можно не более одного раза
        (без учёта копирования при передаче аргумента strings по значению).
    В противном случае вы получите вердикт «неправильный ответ» с соответствующим комментарием.

    Ограничения
    За 1 секунду функция должна обработать максимум 100000 строк длины не более 100.
    При оценке сложности можете считать, что копирование каждого символа стоит порядка 100 элементарных операций.
*/
#include "test_runner.h"

#include <algorithm>
#include <string>
#include <vector>
#include <map>

// Объявляем Group<String> для произвольного типа String
// синонимом vector<String>.
// Благодаря этому в качестве возвращаемого значения
// функции можно указать не малопонятный вектор векторов,
// а вектор групп — vector<Group<String>>.
template <typename String>
using Group = std::vector<String>;

// Ещё один шаблонный синоним типа
// позволяет вместо громоздкого typename String::value_type
// использовать Char<String>
template <typename String> 
using Char = typename String::value_type;

template <typename String>
using Key = String;


template <typename String>
Key<String> ComputeStringKey(const String& string) 
{
    String chars = string;
    std::sort(begin(chars), end(chars));
    chars.erase(std::unique(begin(chars), end(chars)), end(chars));
    return chars;
}

template <typename String>
std::vector<Group<String>> GroupHeavyStrings(std::vector<String> strings)
{
    std::map<Key<String>, Group<String>> groups_map;
    for (String& string : strings)
    {
        groups_map[ComputeStringKey(string)].push_back(std::move(string));
    }
    std::vector<Group<String>> groups;
    for (auto& [key, group] : groups_map)
    {
        groups.push_back(std::move(group));
    }
    return groups;
}


void TestGroupingABC()
{
    std::vector<std::string> strings = { "caab", "abc", "cccc", "bacc", "c" };
    auto groups = GroupHeavyStrings(strings);
    ASSERT_EQUAL(groups.size(), 2);
    std::sort(begin(groups), end(groups));  // Порядок групп не имеет значения
    ASSERT_EQUAL(groups[0], std::vector<std::string>({ "caab", "abc", "bacc" }));
    ASSERT_EQUAL(groups[1], std::vector<std::string>({ "cccc", "c" }));
}

void TestGroupingReal()
{
    std::vector<std::string> strings = { "law", "port", "top", "laptop", "pot", "paloalto", "wall", "awl" };
    auto groups = GroupHeavyStrings(strings);
    ASSERT_EQUAL(groups.size(), 4);
    std::sort(begin(groups), end(groups));  // Порядок групп не имеет значения
    ASSERT_EQUAL(groups[0], std::vector<std::string>({ "laptop", "paloalto" }));
    ASSERT_EQUAL(groups[1], std::vector<std::string>({ "law", "wall", "awl" }));
    ASSERT_EQUAL(groups[2], std::vector<std::string>({ "port" }));
    ASSERT_EQUAL(groups[3], std::vector<std::string>({ "top", "pot" }));
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestGroupingABC);
    RUN_TEST(tr, TestGroupingReal);
    return 0;
}
