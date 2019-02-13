#include "pch.h"
#include <iostream>
#include <string>

using namespace std;

/*
 * Напишите функцию, которая
 * называется IsPalindrom
 * возвращает bool
 * принимает параметр типа string и возвращает, является ли переданная строка палиндромом
 * Палиндром - это слово или фраза, которые одинаково читаются слева направо и справа налево.
 * Пустая строка является палиндромом.
 */

bool IsPalindrom (string word)
{
	for (size_t i = 0; i < word.size() / 2; i++)
	{
		if (word[i] != word[word.size() - i - 1])
			return false;
	}
	return true;
}

int main()
{
	string word;
	cin >> word;
	cout << IsPalindrom(word);

	return 0;
}