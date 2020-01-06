/*
    Продолжим работать с примером, в котором мы создавали программу учёта личных финансов и работали с форматами JSON и XML.
    На этот раз мы решили добавить в неё возможность конвертировать список расходов из XML в JSON и наоборот.
    
    Для этого мы написали две функции:
    *   Json::Document XmlToJson(const Xml::Document& doc)
    *   Xml::Document JsonToXml(const Json::Document& doc, string root_name)

    Кроме того, мы покрыли их юнит-тестами в функциях TestXmlToJson и TestJsonToXml.
    Но есть одна проблема — весь этот код писал начинающий специалист, который посмотрел все лекции нашего курса,
    но, не решив ни одной задачи, сразу стал применять полученные знания в работе.
    Он обратился к вам за помощью, передал свой код и, сказав: «Что-то у меня не компилируется», ушёл в отпуск.
    Ваша задача — привести в порядок код его функций и тестов, то есть сделать так, чтобы они компилировались и работали.

    Более подробно, функция XmlToJson ожидает на вход документ,
    имеющий структуру <root><spend amount="2500" category="food"></spend>...</root>,
    то есть в корневом узле лежит ноль или больше узлов с именем "spend" и атрибутами "amount" и "category".
    Она должна возвращать объект класса Json::Document, имеющий структуру [{"amount": 2500, "category": "food"}, ...],
    то есть это массив, содержащий столько словарей, сколько было узлов <spend> в XML-документе.
    При этом в словарях узёл по ключу "amount" должен быть целочисленным, а по ключу "category" — строковым.
    Гарантируется, что в тестирующей системе на вход вашей функции будут подаваться только XML-документы,
    соответствующие описанному формату (то есть обрабатывать некорректный ввод в данной задаче не надо).
    
    Функция JsonToXml должна выполнять обратное преобразование.
    Точно так же в нашей тестирующей системе ей на вход будут подаваться
    только JSON-документы, соответствующие описанному формату.
    
    Тесты TestXmlToJson и TestJsonToXml не должны принимать пустые реализации функций XmlToJson и JsonToXml,
    а также реализации, нарушающие формат выходных данных.
    Вам не надо добавлять в тесты другие тестовые случаи,
    надо заставить компилироваться и работать те, которые есть.
    
    На проверку пришлите cpp-файл, который
    *   подключает файлы xml.h и json.h
    *   содержит реализацию функций XmlToJson, JsonToXml, TestJsonToXml, TestXmlToJson

    Вам даны файлы xml.h/cpp и json.h/cpp, приведённые в соответствие с рекомендациями последней лекции.
    Именно они будут использоваться в процессе тестирования вашей посылки.
*/
#include "xml.h"
#include "json.h"

#include "test_runner.h"

#include <vector>
#include <string>
#include <map>

using namespace std;

Json::Document XmlToJson(const Xml::Document& doc)
{
    vector<Json::Node> result;

    for (const Xml::Node& n : doc.GetRoot().Children())
    {
        using Json::Node;

        result.emplace_back(map<string, Node>{
            {"category", Node{ n.AttributeValue<string>("category") }},
            { "amount", Node(n.AttributeValue<int>("amount")) }
        });
    }

    return Json::Document(Json::Node(std::move(result)));
}

Xml::Document JsonToXml(const Json::Document& doc, string root_name)
{    
    using namespace Xml;

    Node root(move(root_name), {});
    for (const auto& n : doc.GetRoot().AsArray())
    {
        root.AddChild(Node("spend", {
          {"category", n.AsMap().at("category").AsString()},
          {"amount", to_string(n.AsMap().at("amount").AsInt())},
            }));
    }
    return Document(root);
}

void TestXmlToJson() 
{
    Xml::Node root("july", {});
    root.AddChild({ "spend", {{"category", "travel"}, {"amount", "23400"}} });
    root.AddChild({ "spend", {{"category", "food"}, {"amount", "5000"}} });
    root.AddChild({ "spend", {{"category", "transport"}, {"amount", "1150"}} });
    root.AddChild({ "spend", {{"category", "sport"}, {"amount", "12000"}} });
    const Xml::Document xml_doc(std::move(root));

    const auto json_doc = XmlToJson(xml_doc);

    const auto& items = json_doc.GetRoot().AsArray();
    ASSERT_EQUAL(items.size(), 4u);

    const vector<string> expected_category = { "travel", "food", "transport", "sport" };
    const vector<int> expected_amount = { 23400, 5000, 1150, 12000 };

    for (size_t i = 0; i < items.size(); ++i) 
    {
        const map<string, Json::Node>& item = items[i].AsMap();
        const string feedback_msg = "i = " + std::to_string(i);
        AssertEqual(item.at("category").AsString(), expected_category[i], feedback_msg);
        AssertEqual(item.at("amount").AsInt(), expected_amount[i], feedback_msg);
    }
}

void TestJsonToXml()
{
    using Json::Node;
    using Json::Document;

    const Document json_doc{ Node(vector<Node>{
      Node(map<string, Node>{
        {"category", Node("food")}, {"amount", Node(2500)}
      }),
      Node(map<string, Node>{
        {"category", Node("transport")}, {"amount", Node(1150)}
      }),
      Node(map<string, Node>{
        {"category", Node("restaurants")}, {"amount", Node(5780)}
      }),
      Node(map<string, Node>{
        {"category", Node("clothes")}, {"amount", Node(7500)}
      }),
      Node(map<string, Node>{
        {"category", Node("travel")}, {"amount", Node(23740)}
      }),
      Node(map<string, Node>{
        {"category", Node("sport")}, {"amount", Node(12000)}
      }),
    }) };

    const string root_name = "month";
    const auto xml_doc = JsonToXml(json_doc, root_name);
    const Xml::Node& root = xml_doc.GetRoot();

    ASSERT_EQUAL(root.Name(), root_name);
    const vector<Xml::Node>& children = root.Children();
    ASSERT_EQUAL(children.size(), 6u);

    const vector<string> expected_category = 
    {
      "food", "transport", "restaurants", "clothes", "travel", "sport"
    };
    const vector<int> expected_amount = { 2500, 1150, 5780, 7500, 23740, 12000 };

    for (size_t i = 0; i < children.size(); ++i)
    {
        const string feedback_msg = "i = " + std::to_string(i);
        const Xml::Node& c = children[i];
        AssertEqual(c.Name(), "spend", feedback_msg);
        AssertEqual(c.AttributeValue<string>("category"), expected_category[i], feedback_msg);
        AssertEqual(c.AttributeValue<int>("amount"), expected_amount[i], feedback_msg);
    }
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestXmlToJson);
    RUN_TEST(tr, TestJsonToXml);
    return 0;
}
