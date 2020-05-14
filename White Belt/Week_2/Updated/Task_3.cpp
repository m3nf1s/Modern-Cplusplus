/*
 * Напишите функцию, которая
 * называется PalindromFilter
 * возвращает vector<string>
 * принимает vector<string> words и int minLength и возвращает все строки из вектора words, которые являются палиндромами и имеют длину не меньше minLength
 * Входной вектор содержит не более 100 строк, длина каждой строки не больше 100 символов.
 */
 
#include <iostream>
#include <vector>
#include <algorithm>

bool IsPalindrom(const std::string& word)
{
    return std::equal(word.begin(), word.begin() + (word.size() / 2), word.rbegin());
}

std::vector<std::string> PalindromFilter (std::vector<std::string> words, size_t minLength)
{
    const auto it = std::remove_if(words.begin(), words.end(),
        [minLength](const std::string& word)
        {
            return word.size() < minLength || !IsPalindrom(word);
        });

    words.erase(it, words.end());

    return words;
}

int main()
{
    std::vector<std::string> test = { "water", "madam", "aba", "weew", "qwerty", "asdffdsa" };
    std::vector<std::string> simple = PalindromFilter(test, 4);

    for (const auto& word : simple)
    {
        std::cout << word << " ";
    }
}
