/*
    Условие
    Представим, что у нас есть web-сервер, который обслуживает запросы к интернет-магазину.
    Он поддерживает следующий набор запросов по протоколу HTTP:    
    *   GET / HTTP/1.1 — получить главную страницу магазина
    *   POST /order HTTP/1.1 — разместить новый заказ
    *   POST /product HTTP/1.1 — добавить новый товар в магазин (команда админки)
    *   GET /order HTTP/1.1 — получить детали заказа
    *   PUT /product HTTP/1.1 — то же самое, что и POST /order HTTP/1.1
    *   GET /basket HTTP/1.1 — получить состав текущей корзины клиента
    *   DELETE /product HTTP/1.1 — удалить товар из интернет-магазина (команда админки)
    *   GET /help HTTP/1.1 — получить страницу о том, как пользоваться интернет-магазином

    С точки зрения протокола HTTP, первые части приведённых выше запросов («GET», «POST», «PUT», «DELETE») называются методами.
    Вторые части называются URI (Uniform Resource Identifier).
    Третья часть — это версия протокола.
    Таким образом, наш web-сервер поддерживает 4 метода: GET, POST, PUT, DELETE
        и 5 URI: «/», «/order», «/product», «/basket», «/help».
    
    Главный системный администратор нашего сервера озаботился его масштабированием и для начала он решил изучить статистику использования.
    Он хочет для каждого метода и каждого URI посчитать, сколько раз он встречался в запросах к серверу за последний месяц.
    Он попросил вас помочь с этим.
    
    У вас уже есть какая-то кодовая база для изучения запросов к серверу, и вы хотите воспользоваться ею, чтобы сэкономить время.
    У вас есть заголовочный файл http_request.h, содержащий структуру HttpRequest.
    Кроме того, есть заголовочный файл stats.h, содержащий объявления класса Stats и функции ParseRequest.
    Наконец, у вас есть готовая функция ServeRequests.
    Вам нужно, основываясь на реализации функции ServeRequests, реализовать класс Stats и функцию ParseRequest.
    
    Дополнительные требования к классу Stats:
    *   метод GetMethodStats возвращает словарь, в котором для каждого метода хранится,
            сколько раз он встретился в качестве аргумента метода AddMethod;
    *   метод GetUriStats работает аналогично для URI;
    *   если метод, переданный в метод AddMethod, не поддерживается нашим сервером (список поддерживаемых методов приведён выше),
            то нужно на единицу увеличить счётчик для метода «UNKNOWN» (подробнее см. юнит-тесты в заготовке решения);
    *   если URI, переданный в метод AddUri, не поддерживается нашим сервером,
            то нужно на единицу увеличить счётчик для URI «unknown».
    На проверку пришлите архив, состоящий из файлов stats.h и stats.cpp (а также любых других файлов, которые вы посчитаете нужным добавить в свой проект).
    При этом ваши файлы не должны содержать реализацию функции ServeRequests
        (если ваша посылка будет содержать функцию ServeRequests, вы получите ошибку компиляции).
*/

#include "test_runner.h"
#include "http_request.h"
#include "stats.h"

#include <map>
#include <string_view>

Stats ServeRequests(std::istream& input) 
{
    Stats result;
    for (std::string line; std::getline(input, line); )
    {
        const HttpRequest req = ParseRequest(line);
        result.AddUri(req.uri);
        result.AddMethod(req.method);
    }
    return result;
}

void TestBasic() 
{
    const std::string input =
        R"(GET / HTTP/1.1
    POST /order HTTP/1.1
    POST /product HTTP/1.1
    POST /product HTTP/1.1
    POST /product HTTP/1.1
    GET /order HTTP/1.1
    PUT /product HTTP/1.1
    GET /basket HTTP/1.1
    DELETE /product HTTP/1.1
    GET / HTTP/1.1
    GET / HTTP/1.1
    GET /help HTTP/1.1
    GET /upyachka HTTP/1.1
    GET /unexpected HTTP/1.1
    HEAD / HTTP/1.1)";

    const std::map<std::string_view, int> expected_method_count =
    {
      {"GET", 8},
      {"PUT", 1},
      {"POST", 4},
      {"DELETE", 1},
      {"UNKNOWN", 1},
    };
    const std::map<std::string_view, int> expected_url_count =
    {
      {"/", 4},
      {"/order", 2},
      {"/product", 5},
      {"/basket", 1},
      {"/help", 1},
      {"unknown", 2},
    };

    std::istringstream is(input);
    const Stats stats = ServeRequests(is);

    ASSERT_EQUAL(stats.GetMethodStats(), expected_method_count);
    ASSERT_EQUAL(stats.GetUriStats(), expected_url_count);
}

void TestAbsentParts() 
{
    // Методы GetMethodStats и GetUriStats должны возвращать словари
    // с полным набором ключей, даже если какой-то из них не встречался
    const std::map<std::string_view, int> expected_method_count =
    {
      {"GET", 0},
      {"PUT", 0},
      {"POST", 0},
      {"DELETE", 0},
      {"UNKNOWN", 0},
    };
    const std::map<std::string_view, int> expected_url_count =
    {
      {"/", 0},
      {"/order", 0},
      {"/product", 0},
      {"/basket", 0},
      {"/help", 0},
      {"unknown", 0},
    };
    const Stats default_constructed;

    ASSERT_EQUAL(default_constructed.GetMethodStats(), expected_method_count);
    ASSERT_EQUAL(default_constructed.GetUriStats(), expected_url_count);
}

int main() 
{
    TestRunner tr;
    RUN_TEST(tr, TestBasic);
    RUN_TEST(tr, TestAbsentParts);
}