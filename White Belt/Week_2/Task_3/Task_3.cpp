// Task_3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

/*
 * Напишите функцию, которая
 * называется PalindromFilter
 * возвращает vector<string>
 * принимает vector<string> words и int minLength и возвращает все строки из вектора words, которые являются палиндромами и имеют длину не меньше minLength
 * Входной вектор содержит не более 100 строк, длина каждой строки не больше 100 символов.
 */

bool IsPalindrom(string word)
{
	for (size_t i = 0; i < word.size() / 2; i++)
	{
		if (word[i] != word[word.size() - i - 1])
			return false;
	}
	return true;
}

vector<string> PalindromFilter (vector<string> words, size_t minLength)
{
	vector<string> newVector;
	for(auto w : words)
	{
		if(IsPalindrom(w) && w.length() >= minLength)
		{
			newVector.push_back(w);
		}
	}
	return newVector;
}

int main()
{
	vector<string> test = { "water", "madam", "aba", "weew", "qwerty", "asdffdsa" };
	vector<string> simple = PalindromFilter(test, 4);

	for (auto w : simple)
		cout << w << " ";
}
