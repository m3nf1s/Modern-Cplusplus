// Task_12.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

/*
 * Реализуйте справочник столиц стран.
 * 
 * На вход программе поступают следующие запросы:
 * 
 * CHANGE_CAPITAL country new_capital — изменение столицы страны country на new_capital, либо добавление такой страны с такой столицей, если раньше её не было.
 * RENAME old_country_name new_country_name — переименование страны из old_country_name в new_country_name.
 * ABOUT country — вывод столицы страны country.
 * DUMP — вывод столиц всех стран.
 * 
 *   * Формат ввода
 *   В первой строке содержится количество запросов Q, в следующих Q строках — описания запросов.
 *   Все названия стран и столиц состоят лишь из латинских букв, цифр и символов подчёркивания.
 *   
 *   Формат вывода
 *   Выведите результат обработки каждого запроса:
 *   
 *   В ответ на запрос CHANGE_CAPITAL country new_capital выведите:
 *   Introduce new country country with capital new_capital, если страны country раньше не существовало;
 *   Country country hasn't changed its capital, если страна country до текущего момента имела столицу new_capital;
 *   Country country has changed its capital from old_capital to new_capital, если страна country до текущего момента имела столицу old_capital, название которой не совпадает с названием new_capital.
 *   
 *   В ответ на запрос RENAME old_country_name new_country_name выведите
 *   Incorrect rename, skip, если новое название страны совпадает со старым, страна old_country_name не существует или страна new_country_name уже существует;
 *   Country old_country_name with capital capital has been renamed to new_country_name, если запрос корректен и страна имеет столицу capital.
 *   
 *   В ответ на запрос ABOUT country выведите
 *   Country country doesn't exist, если страны с названием country не существует;
 *   Country country has capital capital, если страна country существует и имеет столицу capital.
 *   
 *   В ответ на запрос DUMP выведите
 *   There are no countries in the world, если пока не было добавлено ни одной страны;
 *   разделённые пробелами пары country/capital, описывающие столицы всех стран и упорядоченные по названию страны, если в мире уже есть хотя бы одна страна.
 */
#include "pch.h"
#include <iostream>
#include <string>
#include <map>

int main()
{
	int count_commands;
	std::map<std::string, std::string> directory;

	std::cin >> count_commands;

	for (int i = 0; i < count_commands; i++)
	{
		std::string command;
		std::cin >> command;

		if (command == "CHANGE_CAPITAL")
		{
			std::string country, new_capital;
			std::cin >> country >> new_capital;
		
			if (!directory[country].empty())
			{
				if (directory[country] != new_capital)
				{
					std::string old_capital = directory[country];
					std::cout << "Country " << country << " has changed its capital from " << old_capital << " to " << new_capital << std::endl;
				}
				else
				{
					std::cout << "Country " << country << " hasn't changed its capital" << std::endl;
				}
			}
			else
			{
				std::cout << "Introduce new country " << country << " with capital " << new_capital << std::endl;
			}
			directory[country] = new_capital;
			continue;
		}

		if (command == "RENAME")
		{
			std::string old_country_name, new_country_name;
			std::cin >> old_country_name >> new_country_name;

			if (old_country_name == new_country_name || directory.count(old_country_name) == 0 || directory.count(new_country_name) == 1)
			{
				std::cout << "Incorrect rename, skip" << std::endl;
			}
			else
			{
				std::cout << "Country " << old_country_name << " with capital " << directory[old_country_name] << " has been renamed to " << new_country_name << std::endl;
				directory[new_country_name] = directory[old_country_name];
				directory.erase(old_country_name);
			}

			continue;
		}

		if(command == "ABOUT")
		{
			std::string country;
			std::cin >> country;

			if (directory.count(country) == 1)
			{
				std::cout << "Country " << country << " has capital " << directory[country] << std::endl;
			}
			else
			{
				std::cout << "Country " << country << " doesn't exist" << std::endl;
			}

			continue;
		}

		if (command == "DUMP")
		{
			if (!directory.empty())
			{
				for (const auto& pair : directory)
				{
					std::cout << pair.first << "/" << pair.second << std::endl;
				}
			}
			else
				std::cout << "There are no countries in the world" << std::endl;
		}
	}

	return 0;
}