/*
    Разработайте класс Translator, позволяющий сохранять двуязычные пары слов и затем переводить слова
        с одного языка на другой с использованием уже добавленных пар.

    Более конкретно, объект t типа Translator должен допускать следующие действия:
    *   Создание с помощью конструктора по умолчанию. В этом случае база переводов пуста.
    *   Добавление двуязычной пары: t.Add(source, target).
        После такого вызова считается, что слово source на языке 1 соответствует слову target на языке 2.
        Переданные в метод Add строки могут быть уничтожены раньше объекта t.
    *   Перевод с языка 1 на язык 2: t.TranslateForward(source).
        Если ранее уже был вызов t.Add(source_copy, target)для некоторой строки target и строки source_copy,
            равной source (или являющейся ей), нужно вернуть target.
        Если такого вызова не было, нужно вернуть пустую строку.
        Если таких вызовов было несколько, нужно вернуть target для последнего из них.
    *   Перевод с языка 2 на язык 1: t.TranslateBackward(target).
        Если ранее уже был вызов t.Add(source, target_copy)для некоторой строки source и строки target_copy,
            равной target (или являющейся ей), нужно вернуть source.
        Если такого вызова не было, нужно вернуть пустую строку.
        Если таких вызовов было несколько, нужно вернуть source для последнего из них.
    
    Ограничения
    Каждая строка должна храниться в экземпляре класса Translator не более одного раза.
    При нарушении этого ограничения вы получите ошибку «Memory limit exceeded».
*/
#include "test_runner.h"

#include <string_view>
#include <vector>
#include <string>
#include <map>
#include <deque>
class Translator
{
public:
    Translator() = default;

    void Add(std::string_view source, std::string_view target)
    {
        std::string_view src = CloneStringView(source);
        std::string_view trg = CloneStringView(target);

        forward_dict_[src] = trg;
        backward_dict_[trg] = src;
    }
    std::string_view TranslateForward(std::string_view source) const
    {
        if (forward_dict_.count(source))
        {
            return forward_dict_.at(source);
        }

        return {};
    }
    std::string_view TranslateBackward(std::string_view target) const
    {
        if (backward_dict_.count(target))
        {
            return backward_dict_.at(target);
        }

        return {};
    }

private:
    std::map<std::string_view, std::string_view> forward_dict_;
    std::map<std::string_view, std::string_view> backward_dict_;
    std::deque<std::string> data_;

    std::string_view CloneStringView(std::string_view str)
    {
        auto it_forward = forward_dict_.find(str);
        auto it_backward = backward_dict_.find(str);

        if (it_forward != forward_dict_.end())
        {
            return it_forward->first;
        }
        else if (it_backward != backward_dict_.end())
        {
            return it_backward->first;
        }

        return data_.emplace_back(str);
    }
};

void TestSimple()
{
    Translator translator;
    translator.Add(std::string("okno"), std::string("window"));
    translator.Add(std::string("stol"), std::string("table"));

    ASSERT_EQUAL(translator.TranslateForward("okno"), "window");
    ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
    ASSERT_EQUAL(translator.TranslateBackward("stol"), "");
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestSimple);
    return 0;
}