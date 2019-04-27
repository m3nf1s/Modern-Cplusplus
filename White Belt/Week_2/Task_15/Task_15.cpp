/*
 * Дан набор строк. Найдите количество уникальных строк в этом наборе.
 * 
 * Формат ввода
 * Сначала вводится количество строк N, затем — сами N строк, разделённые пробелом.
 * Все строки состоят лишь из латинских букв, цифр и символов подчёркивания.
 * 
 * Формат вывода
 * Выведите единственное целое число — количество уникальных строк в данном наборе.
 */

#include <iostream>
#include <set>
#include <string>

int main()
{
	std::set<std::string> unique_string;

	int command_count;
	std::cin >> command_count;

	for (int i = 0; i < command_count; i++)
	{
		std::string word;
		std::cin >> word;

		unique_string.insert(word);
	}

	std::cout << unique_string.size() << std::endl;
}