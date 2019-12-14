/*
    Дан вектор токенов.
    Напишите функцию, разбивающую токены на предложения.

    Token — шаблонный тип, про который известно лишь то,
        что он имеет константный метод IsEndSentencePunctuation, возвращающий true,
        если токен является знаком пунктуации, заканчивающим предложение, и false в противном случае.
    Объекты этого типа запрещено копировать.
    При наличии копирования этих объектов вы получите ошибку компиляции.
    
    Sentence — синоним для типа vector.
    Предложением считается последовательность токенов, заканчивающаяся подряд идущими токенами,
        являющимися знаками пунктуации конца предложения. Иными словами, любое предложение должно состоять из двух частей:    
    *   токены, для которых IsEndSentencePunctuation возвращает false
        (такие токены обязаны присутствовать в предложении за исключением, возможно, первого предложения);
    *   токены, для которых IsEndSentencePunctuation возвращает true
        (такие токены обязаны присутствовать в предложении за исключением, возможно, последнего предложения).

    Ограничения
    Максимальное количество токенов — 10^6.
    Время выполнения одного вызова функции ограничено 1 секундой.
*/
#include "test_runner.h"

#include <vector>
#include <utility>

// Объявляем Sentence<Token> для произвольного типа Token
// синонимом vector<Token>.
// Благодаря этому в качестве возвращаемого значения
// функции можно указать не малопонятный вектор векторов,
// а вектор предложений — vector<Sentence<Token>>.
template <typename Token>
using Sentence = std::vector<Token>;

// Класс Token имеет метод bool IsEndSentencePunctuation() const
template <typename Token>
std::vector<Sentence<Token>> SplitIntoSentences(std::vector<Token> tokens)
{
    // Напишите реализацию функции, не копируя объекты типа Token
    std::vector<Sentence<Token>> result;
    Sentence<Token> sentence;
    auto it = tokens.begin();
    bool isEnd = false;
    while (it != tokens.end())
    {
        if(it->IsEndSentencePunctuation())
        {
            isEnd = true;
        }       
        if (isEnd && !(it->IsEndSentencePunctuation()))
        {
            isEnd = false;
            result.push_back(std::move(sentence));
        }

        sentence.push_back(std::move(*it));
        ++it;
    }
    result.push_back(std::move(sentence));
    return result;
}

struct TestToken 
{
    std::string data;
    bool is_end_sentence_punctuation = false;

    bool IsEndSentencePunctuation() const 
    {
        return is_end_sentence_punctuation;
    }
    bool operator==(const TestToken& other) const 
    {
        return data == other.data && is_end_sentence_punctuation == other.is_end_sentence_punctuation;
    }
};

std::ostream& operator<<(std::ostream& stream, const TestToken& token) 
{
    return stream << token.data;
}

// Тест содержит копирования объектов класса TestToken.
// Для проверки отсутствия копирований в функции SplitIntoSentences
// необходимо написать отдельный тест.
void TestSplitting() 
{
    ASSERT_EQUAL(
        SplitIntoSentences(std::vector<TestToken>({ {"Split"}, {"into"}, {"sentences"}, {"!"} })),
        std::vector<Sentence<TestToken>>({
            {{"Split"}, {"into"}, {"sentences"}, {"!"}}
            })
    );


    ASSERT_EQUAL(
        SplitIntoSentences(std::vector<TestToken>({ {"Split"}, {"into"}, {"sentences"}, {"!", true} })),
        std::vector<Sentence<TestToken>>({
            {{"Split"}, {"into"}, {"sentences"}, {"!", true}}
            })
    );

    ASSERT_EQUAL(
        SplitIntoSentences(std::vector<TestToken>({ {"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}, {"Without"}, {"copies"}, {".", true} })),
        std::vector<Sentence<TestToken>>({
            {{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}},
            {{"Without"}, {"copies"}, {".", true}},
            })
            );
}

int main() 
{
    TestRunner tr;
    RUN_TEST(tr, TestSplitting);
    return 0;
}