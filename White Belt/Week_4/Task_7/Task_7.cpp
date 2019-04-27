/*
	В первой строке файла input.txt записаны два числа N и M.
	Далее в файле находится таблица из N строк и M столбцов, представленная в формате CSV (comma-separated values).
	Такой формат часто используется для текстового представления таблиц с данными
	в файле несколько строк, значения из разных ячеек внутри строки отделены друг от друга запятыми.
	Ваша задача — вывести данные на экран в виде таблицы, размер ячейки которой равен 10, соседние ячейки отделены друг от друга пробелом.
	После последней ячейки пробела быть не должно.
	Гарантируется, что в таблице будет ровно N строк и M столбцов, значение каждой из ячеек — целое число.
*/

#include <iostream>
#include <fstream>
#include <iomanip>

int main()
{
	std::ifstream input("input.txt");
	if (input.is_open())
	{
		int rows, columns;

		input >> rows;
		input.ignore(1);
		input >> columns;

		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < columns; ++j)
			{
				int number;
				input >> number;
				input.ignore(1);

				if (j != columns - 1)
				{
					std::cout << std::setw(10) << number << ' ';
				}
				else
				{
					std::cout << std::setw(10) << number << std::endl;
				}
			}
		}
	}
}