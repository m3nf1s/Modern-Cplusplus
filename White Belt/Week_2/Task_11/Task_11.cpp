// Task_11.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

/*
 * Слова называются анаграммами друг друга, если одно из них можно получить перестановкой букв в другом.
 * Например, слово «eat» можно получить перестановкой букв слова «tea», поэтому эти слова являются анаграммами друг друга.
 * Даны пары слов, проверьте для каждой из них, являются ли слова этой пары анаграммами друг друга.
 * 
 * Указание
 * Один из способов проверки того, являются ли слова анаграммами друг друга, заключается в следующем.
 * Для каждого слова с помощью словаря подсчитаем, сколько раз в нём встречается каждая буква.
 * Если для обоих слов эти словари равны (а это проверяется с помощью обычного оператора ==), то слова являются анаграммами друг друга, в противном случае не являются.
 * 
 * При этом построение такого словаря по слову удобно вынести в отдельную функцию BuildCharCounters.
 * 
 * Формат ввода
 * Сначала дано число пар слов N, затем в N строках содержатся пары слов, которые необходимо проверить.
 * Гарантируется, что все слова состоят лишь из строчных латинских букв.
 * 
 * Формат вывода
 * Выведите N строк: для каждой введённой пары слов YES, если эти слова являются анаграммами, и NO в противном случае.
 */

#include "pch.h"
#include <iostream>
#include <map>
#include <string>
#include <vector>

std::map <char,int> BuildCharCounters (const std::string& word)
{
	std::map<char, int> result;

	for (int i = 0; i < word.length(); i++)
		result[word[i]]++;

	return result;
}

int main()
{
	int countWords;
	std::vector<std::string> answers;

	std::cin >> countWords;

	for (int i = 0; i  < countWords; i++)
	{
		std::string firstWord, secondWord;
		std::cin >> firstWord >> secondWord;

		if (BuildCharCounters(firstWord) == BuildCharCounters(secondWord))
			answers.push_back("YES");
		else
			answers.push_back("NO");
	}

	for (const auto& answer : answers)
	{
		std::cout << answer << std::endl;
	}

	return 0;
}

