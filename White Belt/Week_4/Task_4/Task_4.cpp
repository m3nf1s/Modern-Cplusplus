/*
 * В этом задании вам предстоит написать две небольшие программы.
 * Каждый пункт - отдельная задача, решение отправляйте в поле с соответствующим номером.
 * 
 * Часть 1
 * Ваша программа должна считать содержимое файла input.txt и напечатать его на экран без изменений.
 * Гарантируется, что содержимое файла input.txt заканчивается переводом строки.
 */

#include "pch.h"
#include <fstream>
#include <string>
#include <iostream>

int main()
{
	std::ifstream input("input.txt");

	if (input.is_open())
	{
		std::string line;
		while (std::getline(input, line))
		{
			std::cout << line << std::endl;
		}
	}
}