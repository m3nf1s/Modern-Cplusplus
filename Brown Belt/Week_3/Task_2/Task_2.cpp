/*
    Иногда на практике встречаются объекты, создание которых занимает значительное время,
    однако они бывают нужны не при каждом запуске программы.
    Например, клиент системы контроля версий может обращаться к локальным файлам,
    а может — к удалённому репозиторию.
    Тогда устанавливать соединение с удалённым репозиторием можно,
    только если пользователь решил к нему обратиться.
    
    Для представления таких объектов может быть полезен шаблон LazyValue<T>.
    У него есть константный метод const T& Get(), который возвращает ссылку на созданный объект.
    В своём конструкторе LazyValue принимает инициализирующую функцию,
    которая используется при первом вызове метода Get для создания хранимого объекта.
    Последующие вызовы Get просто возвращают ссылку на хранимый объект.
    
    Таким образом, объект класса LazyValue<T> не тратит время
    на создание хранимого объекта до первого вызова метода Get.
    
    Вам дан интерфейс шаблона LazyValue. Реализуйте его.
    
    Более подробный список требований:    
    *   Объект класса LazyValue<T> не должен конструировать объект типа T при своём создании
    *   При первом вызове метода LazyValue<T>::Get должен создаваться объект типа T с помощью функции,
        переданной в конструктор LazyValue<T>
    *   Последующие вызовы метода Get не должны вызывать функцию, переданную в конструктор
    *   Если за время жизни объекта LazyValue<T> метод Get не был вызван ни разу,
        то инициализирующая функция не должна быть вызвана.
    *   Шаблон LazyValue должен поддерживать работу с типами без конструктора по умолчанию
*/
#include "test_runner.h"

#include <functional>
#include <string>
#include <optional>

template <typename T>
class LazyValue
{
public:
    explicit LazyValue(std::function<T()> init)
        : function_(std::move(init))
    {
    }

    bool HasValue() const
    {
        return value_.has_value();
    }

    const T& Get() const
    {
        if (!value_)
        {
            value_ = function_();
        }
        return *value_;
    }

private:
    std::function<T()> function_;
    mutable std::optional<T> value_;
};

void UseExample()
{
    const std::string big_string = "Giant amounts of memory";
    
    LazyValue<std::string> lazy_string([&big_string] { return big_string; });
    
    ASSERT(!lazy_string.HasValue());
    ASSERT_EQUAL(lazy_string.Get(), big_string);
    ASSERT_EQUAL(lazy_string.Get(), big_string);
}

void TestInitializerIsntCalled()
{
    bool called = false;
    
    {
        LazyValue<int> lazy_int([&called] 
            {
                called = true;
                return 0;
            });
    }
    ASSERT(!called);
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, UseExample);
    RUN_TEST(tr, TestInitializerIsntCalled);
    return 0;
}
