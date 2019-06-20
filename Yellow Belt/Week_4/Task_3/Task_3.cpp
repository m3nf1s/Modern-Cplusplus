/*
Напишите функцию SplitIntoWords, разбивающую строку на слова по пробелам.
Гарантируется, что:
	1) строка непуста;
	2) строка состоит лишь из латинских букв и пробелов;
	3) первый и последний символы строки не являются пробелами;
	4) строка не содержит двух пробелов подряд.
Подсказка
Рекомендуется следующий способ решения задачи:
	1) искать очередной пробел с помощью алгоритма find;
	2) создавать очередное слово с помощью конструктора строки по двум итераторам.
*/

#include <iostream>
#include <vector>
#include <algorithm>

std::vector<std::string> SplitIntoWords(const std::string& s);

int main() 
{
	std::string s = "C Cpp Java Python"; //4 С/Cpp/Java/Python

	std::vector<std::string> words = SplitIntoWords(s);
	std::cout << words.size() << " ";
	for (auto it = std::begin(words); it != std::end(words); ++it)
	{
		if (it != std::begin(words)) {
			std::cout << "/";
		}
		std::cout << *it;
	}
	std::cout << std::endl;

	return 0;
}

std::vector<std::string> SplitIntoWords(const std::string& s)
{
	std::vector<std::string> result;

	auto it_begin = s.begin();
	auto it_end = s.begin();

	for (auto it = s.begin(); it != s.end(); ++it)
	{
		if (*it == ' ')
		{
			it_end = it;
			result.push_back({ it_begin, it_end });
			if (it != s.end())
			{
				it_begin = ++it;
			}
		}
	}

	result.push_back({ it_begin , s.end() });

	return result;
}