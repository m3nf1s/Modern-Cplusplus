// Task_10.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

/*
 * У каждого из нас есть ежемесячные дела, каждое из которых нужно выполнять в конкретный день каждого месяца: оплата счетов за электричество, абонентская плата за связь и пр.
 * Вам нужно реализовать работу со списком таких дел, а именно, обработку следующих операций:
 * 
 * ADD i s
 * Добавить дело с названием s в день i.
 * 
 * NEXT
 * Закончить текущий месяц и начать новый.
 * Если новый месяц имеет больше дней, чем текущий, добавленные дни изначально не будут содержать дел.
 * Если же в новом месяце меньше дней, дела со всех удаляемых дней необходимо будет переместить на последний день нового месяца.
 * 
 * Обратите внимание, что количество команд этого типа может превышать 11.
 * 
 * DUMP i
 * Вывести все дела в день i.
 * 
 * Изначально текущим месяцем считается январь.
 * Количества дней в месяцах соответствуют Григорианскому календарю с той лишь разницей, что в феврале всегда 28 дней.
 * 
 * Формат ввода
 * Сначала число операций Q, затем описания операций.
 * 
 * Названия дел s уникальны и состоят только из латинских букв, цифр и символов подчёркивания.
 * Номера дней i являются целыми числами и нумеруются от 1 до размера текущего месяца.
 * 
 * Формат вывода
 * Для каждой операции типа DUMP в отдельной строке выведите количество дел в соответствующий день, а затем их названия, разделяя их пробелом.
 * Порядок вывода дел в рамках каждой операции значения не имеет.
 */

int main()
{
	int day_of_month = 0;

	const vector<int> days_of_month = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	vector<vector<string>> affairs(days_of_month[day_of_month]);

	int count_of_commands;

	cin >> count_of_commands;

	for (int i = 0; i < count_of_commands; i++)
	{
		string command;

		cin >> command;

		if (command == "ADD")
		{
			int day;
			string task;
			cin >> day >> task;
			affairs[day - 1].push_back(task);

			continue;
		}

		if (command == "NEXT")
		{
			vector<vector<string>> buff = affairs;
			if (++day_of_month > 11)
				day_of_month = 0;

			affairs.resize(days_of_month[day_of_month]);

			if (affairs.size() < buff.size())
			{
				for (int i = affairs.size(); i < buff.size(); i++)
				{
					affairs[affairs.size() - 1].insert(end(affairs[affairs.size() - 1]), begin(buff[i]), end(buff[i]));
				}
			}

			continue;
		}

		if (command == "DUMP")
		{
			int day;
			cin >> day;
			cout << affairs[day - 1].size() << " ";
			for (auto s : affairs[day - 1])
				cout << s << " ";
			cout << endl;

			continue;
		}
	}
}

