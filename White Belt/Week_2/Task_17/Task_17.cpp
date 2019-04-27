/*
 * Два слова называются синонимами друг друга, если они имеют похожие значения. Реализуйте следующие операции над словарём синонимов:
 * 
 * ADD word1 word2 — добавить в словарь пару синонимов (word1, word2).
 * COUNT word — узнать количество синонимов слова word.
 * CHECK word1 word2 — проверить, являются ли слова word1 и word2 синонимами.
 * Слова word1 и word2 считаются синонимами, если среди запросов ADD был хотя бы один запрос ADD word1 word2 или ADD word2 word1.
 * 
 * Формат ввода
 * Сначала вводится количество запросов Q, затем Q строк с описаниями запросов.
 * Гарантируется, что в каждом запросе CHECK и ADD слова word1 и word2 различны.
 * Все слова состоят лишь из латинских букв, цифр и символов подчёркивания.
 * 
 * Формат вывода
 * Для каждого запроса в соответствующей строке выведите ответ на него:
 * В ответ на запрос COUNT word выведите единственное целое число — количество синонимов слова word.
 * В ответ на запрос CHECK word1 word2 выведите строку YES, если word1 и word2 являются синонимами, и NO в противном случае.
 */

#include <iostream>
#include <string>
#include <set>
#include <map>

int main()
{
	std::map <std::string, std::set<std::string>> list_synonyms;

	int command_count;
	std::cin >> command_count;

	for (int i = 0; i < command_count; ++i)
	{
		std::string command;
		std::cin >> command;

		if (command == "ADD")
		{
			std::string first_word, second_word;
			std::cin >> first_word >> second_word;

			list_synonyms[first_word].insert(second_word);
			list_synonyms[second_word].insert(first_word);

			continue;
		}

		if(command == "COUNT")
		{
			std::string word;
			std::cin >> word;

			if (list_synonyms.count(word) == 1)
				std::cout << list_synonyms[word].size() << std::endl;
			else
				std::cout << "0" << std::endl;

			continue;
		}

		if(command == "CHECK")
		{
			std::string first_word, second_word;
			std::cin >> first_word >> second_word;

			if(list_synonyms.count(first_word) == 1)
			{
				if (list_synonyms[first_word].count(second_word) == 1)
					std::cout << "YES" << std::endl;
				else
					std::cout << "NO" << std::endl;
			}
			else
			{
				std::cout << "NO" << std::endl;
			}
		}

	}
}