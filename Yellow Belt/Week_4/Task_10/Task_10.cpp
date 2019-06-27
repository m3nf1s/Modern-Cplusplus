/*
Напишите функцию FindStartsWith:

	1) принимающую отсортированный набор строк в виде итераторов range_begin,
		range_end и один символ prefix;
	2) возвращающую диапазон строк, начинающихся с символа prefix, в виде пары итераторов.

	template <typename RandomIt>
	pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, char prefix);

Если итоговый диапазон пуст, его границы должны указывать на то место в контейнере,
	куда можно без нарушения порядка сортировки вставить любую строку,
	начинающуюся с символа prefix (подобно алгоритму equal_range).
Гарантируется, что строки состоят лишь из строчных латинских букв и символ prefix также является строчной латинской буквой.

Поиск должен осуществляться за логарифмическую сложность — например, с помощью двоичного поиска.

Часть 2. Группировка по префиксу
Напишите более универсальный вариант функции FindStartsWith, принимающий в качестве префикса произвольную строку,
	состоящую из строчных латинских букв.

	template <typename RandomIt>
	pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, const string& prefix);
*/

#include <iostream>
#include <vector>
#include "FindStartsWithChar.h"
#include "FindStartsWithPrefix.h"

int main() 
{
	const std::vector<std::string> sorted_strings = { "moscow", "murmansk", "vologda" };

	const auto m_result = FindStartsWithChar(begin(sorted_strings), end(sorted_strings), 'm');
	for (auto it = m_result.first; it != m_result.second; ++it)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;

	const auto p_result = FindStartsWithChar(begin(sorted_strings), end(sorted_strings), 'p');
	
	std::cout << (p_result.first - begin(sorted_strings)) << " " <<
		(p_result.second - begin(sorted_strings)) << std::endl;

	const auto z_result = FindStartsWithChar(begin(sorted_strings), end(sorted_strings), 'z');
	
	std::cout << (z_result.first - begin(sorted_strings)) << " " <<
		(z_result.second - begin(sorted_strings)) << std::endl;
	/*------------------------------------------------------------------------------------------------------*/
	const std::vector<std::string> sorted_strings_ = { "moscow", "motovilikha", "murmansk" };

	const auto mo_result = FindStartsWithPrefix(begin(sorted_strings_), end(sorted_strings_), "mo");

	for (auto it = mo_result.first; it != mo_result.second; ++it)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;

	const auto mt_result = FindStartsWithPrefix(begin(sorted_strings_), end(sorted_strings_), "mt");

	std::cout << (mt_result.first - begin(sorted_strings_)) << " " << (mt_result.second - begin(sorted_strings_)) << std::endl;

	const auto na_result = FindStartsWithPrefix(begin(sorted_strings_), end(sorted_strings_), "na");
	std::cout << (na_result.first - begin(sorted_strings_)) << " " << (na_result.second - begin(sorted_strings_)) << std::endl;

	return 0;
}