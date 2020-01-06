/*
    В лекциях мы разработали библиотеки для загрузки данных из форматов XML и JSON,
    поместив каждую из них в своё пространство имён.
    В этой задаче вам нужно сделать то же самое для формата INI.
    Вам надо разработать библиотеку со следующим интерфейсом:
        using Section = unordered_map<string, string>;
        
        class Document {
        public:
          Section& AddSection(string name);
          const Section& GetSection(const string& name) const;
          size_t SectionCount() const;
        
        private:
          unordered_map<string, Section> sections;
        };
        
        Document Load(istream& input);

    Требования:
    
    *   Содержимое библиотеки должно находиться в пространстве имён Ini
    *   Интерфейс, приведённый выше, должен быть объявлен в файле ini.h
    *   На проверку пришлите архив с полной реализацией библиотеки, в архиве должен быть файл ini.h
    *   В процессе тестирования функции Load ей на вход будет подаваться текст в формате
    *   Гарантируется, что в наших тестах используются только корректные ini-файлы,
        то есть строки вида ключ=значение всегда находятся внутри какой-то секции и содержат ровно один символ '='
    *   Строка ini-файла либо пустая, либо не содержит ведущих пробелов
    *   Примеры применения библиотеки смотрите в юнит-тестах в файле test_ini.cpp
*/
#include "test_runner.h"
#include "ini.h"

#include <sstream>

void TestLoadIni() 
{
    std::istringstream input(
        R"([july]
food=2500
sport=12000
travel=23400
clothes=5200

[august]
food=3250
sport=10000
travel=0
clothes=8300
jewelery=25000

[]
games=35670
movies=
=12345
)"
);
    const Ini::Document doc = Ini::Load(input);

    ASSERT_EQUAL(doc.SectionCount(), 3u);

    const Ini::Section expected_july = 
    {
      {"food", "2500"},
      {"sport", "12000"},
      {"travel", "23400"},
      {"clothes", "5200"},
    };

    const Ini::Section expected_august = 
    {
      {"food", "3250"},
      {"sport", "10000"},
      {"travel", "0"},
      {"clothes", "8300"},
      {"jewelery", "25000"},
    };

    ASSERT_EQUAL(doc.GetSection("july"), expected_july);
    ASSERT_EQUAL(doc.GetSection("august"), expected_august);
}

void TestDocument()
{
    Ini::Document doc;
    ASSERT_EQUAL(doc.SectionCount(), 0u);

    // Обратите внимание, как мы используем указатель для работы
    // с последней добавленной секцией. Эта техника может вам пригодиться
    // для реализации функции Load
    Ini::Section* section = &doc.AddSection("one");
    ASSERT_EQUAL(doc.SectionCount(), 1u);

    section->insert({ "name_1", "value_1" });
    section->insert({ "name_2", "value_2" });

    section = &doc.AddSection("two");
    section->insert({ "name_1", "value_1" });
    section->insert({ "name_2", "value_2" });
    section->insert({ "name_3", "value_3" });

    section = &doc.AddSection("three");
    section->insert({ "name_1", "value_1" });

    ASSERT_EQUAL(doc.SectionCount(), 3u);
    const Ini::Section expected_one = { {"name_1", "value_1"}, {"name_2", "value_2"} };
    const Ini::Section expected_two = 
    {
      {"name_1", "value_1"}, {"name_2", "value_2"}, {"name_3", "value_3"}
    };
    const Ini::Section expected_three = { {"name_1", "value_1"} };

    ASSERT_EQUAL(doc.GetSection("one"), expected_one);
    ASSERT_EQUAL(doc.GetSection("two"), expected_two);
    ASSERT_EQUAL(doc.GetSection("three"), expected_three);
}

void TestUnknownSection()
{
    Ini::Document doc;
    doc.AddSection("primary");

    try
    {
        doc.GetSection("secondary");
        Assert(
            false,
            "Ini::Document::GetSection() should throw std::out_of_range for unknown section"
        );
    }
    catch (std::out_of_range&)
    {
    }
    catch (...)
    {
        Assert(
            false,
            "Ini::Document::GetSection() throws unexpected exception for unknown section"
        );
    }
}

void TestDuplicateSections()
{
    Ini::Document doc;
    doc.AddSection("one").insert({ "key_1", "value_1" });
    doc.AddSection("one").insert({ "key_2", "value_2" });

    const Ini::Section expected = { {"key_1", "value_1"}, {"key_2", "value_2"} };
    ASSERT_EQUAL(doc.GetSection("one"), expected);
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestLoadIni);
    RUN_TEST(tr, TestDocument);
    RUN_TEST(tr, TestUnknownSection);
    RUN_TEST(tr, TestDuplicateSections);
    return 0;
}
