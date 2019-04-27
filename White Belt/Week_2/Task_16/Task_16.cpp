/*
 * Напишите функцию BuildMapValuesSet, принимающую на вход словарь map<int, string> и возвращающую множество значений этого словаря:
 */

#include <iostream>
#include <string>
#include <map>
#include <set>

std::set<std::string> BuildMapValuesSet (const std::map<int, std::string>& m)
{
	std::set<std::string> result;
	for (const auto& item : m)
	{
		result.insert(item.second);
	}

	return result;
}

int main()
{
	std::set<std::string> values = BuildMapValuesSet(
		{
			{1,"odd"},
			{2,"even"},
			{3,"odd"},
			{4,"even"},
			{5,"odd"}
		});

	for (const auto& value : values)
	{
		std::cout << value << std::endl;
	}
}