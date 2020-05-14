/*
* Напишите функцию, которая
* называется IsPalindrom
* возвращает bool
* принимает параметр типа string и возвращает, является ли переданная строка палиндромом
* Палиндром - это слово или фраза, которые одинаково читаются слева направо и справа налево.
* Пустая строка является палиндромом.
*/
 
#include <iostream>
#include <algorithm>

bool IsPalindrom(const std::string& word)
{
    return std::equal(word.begin(), word.begin() + (word.size() / 2), word.rbegin());
}

int main()
{
    std::string word;
    std::cin >> word;
    std::cout << IsPalindrom(word);

    return 0;
}
