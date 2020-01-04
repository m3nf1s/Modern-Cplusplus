/*
    В этой тренировочной задаче вам надо поддержать загрузку расходов из формата XML
    в нашей программе управления личными финансами.
    При этом вам надо воспользоваться готовой библиотекой работы с XML.
    Более конкретно, вам надо написать функцию vector<Spending> LoadFromXml(istream& input).
    Spending — это структура из вводной лекции.

    Поток input содержит описание расходов в формате XML.

    Важно отметить:    
    *   формат текста в потоке input всегда строго такой, как в примере:
        есть один корневой узел, который содержит несколько узлов <spend> с атрибутами "amount" и "category"
    *   функция Load из выданной вам библиотеки работы с XML умеет загружать описанный выше формат
    *   мы выдаём вам не реальную библиотеку разбора XML, а лишь минимальный код, достаточный для работы описанным форматом данных
    *   цель этой задачи — не показать, как правильно парсить XML, а познакомить вас с кодом,
        на котором мы в дальнейшем будем разбирать пространства имён, поэтому очень важно,
        чтобы вы реализовали функцию LoadFromXml через содержимое нашей библиотеки работы с XML.
*/
#include "xml.h"
#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

struct Spending 
{
    std::string category;
    int amount;
};

bool operator == (const Spending& lhs, const Spending& rhs) 
{
    return lhs.category == rhs.category && lhs.amount == rhs.amount;
}

std::ostream& operator << (std::ostream& os, const Spending& s) 
{
    return os << '(' << s.category << ": " << s.amount << ')';
}

int CalculateTotalSpendings(const std::vector<Spending>& spendings)
{
    int result = 0;
    for (const Spending& s : spendings)
    {
        result += s.amount;
    }
    return result;
}

std::string MostExpensiveCategory(const std::vector<Spending>& spendings)
{
    auto compare_by_amount =
        [](const Spending& lhs, const Spending& rhs)
        {
            return lhs.amount < rhs.amount;
        };
    return max_element(begin(spendings), end(spendings), compare_by_amount)->category;
}

std::vector<Spending> LoadFromXml(std::istream& input)
{
    Document doc = Load(input);
    std::vector<Spending> result;

    for (const Node& node : doc.GetRoot().Children())
    {
        result.push_back(
            { 
                node.AttributeValue<std::string>("category"),
                node.AttributeValue<int>("amount")
            });
    }

    return result;
}

void TestLoadFromXml()
{
    std::istringstream xml_input(R"(<july>
    <spend amount="2500" category="food"></spend>
    <spend amount="1150" category="transport"></spend>
    <spend amount="5780" category="restaurants"></spend>
    <spend amount="7500" category="clothes"></spend>
    <spend amount="23740" category="travel"></spend>
    <spend amount="12000" category="sport"></spend>
  </july>)");

    const std::vector<Spending> spendings = LoadFromXml(xml_input);

    const std::vector<Spending> expected = 
    {
      {"food", 2500},
      {"transport", 1150},
      {"restaurants", 5780},
      {"clothes", 7500},
      {"travel", 23740},
      {"sport", 12000}
    };
    ASSERT_EQUAL(spendings, expected);
}

void TestXmlLibrary() 
{
    // Тест демонстрирует, как пользоваться библиотекой из файла xml.h

    std::istringstream xml_input(R"(<july>
    <spend amount="2500" category="food"></spend>
    <spend amount="23740" category="travel"></spend>
    <spend amount="12000" category="sport"></spend>
  </july>)");

    Document doc = Load(xml_input);
    const Node& root = doc.GetRoot();
    ASSERT_EQUAL(root.Name(), "july");
    ASSERT_EQUAL(root.Children().size(), 3u);

    const Node& food = root.Children().front();
    ASSERT_EQUAL(food.AttributeValue<std::string>("category"), "food");
    ASSERT_EQUAL(food.AttributeValue<int>("amount"), 2500);

    const Node& sport = root.Children().back();
    ASSERT_EQUAL(sport.AttributeValue<std::string>("category"), "sport");
    ASSERT_EQUAL(sport.AttributeValue<int>("amount"), 12000);

    Node july("july", {});
    Node transport("spend", { {"category", "transport"}, {"amount", "1150"} });
    july.AddChild(transport);
    ASSERT_EQUAL(july.Children().size(), 1u);
}

int main() 
{
    TestRunner tr;
    RUN_TEST(tr, TestXmlLibrary);
    RUN_TEST(tr, TestLoadFromXml);
}
