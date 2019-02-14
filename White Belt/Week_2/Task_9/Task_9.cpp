#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <cmath>



/*
 * Люди стоят в очереди, но никогда не уходят из её начала, зато могут приходить в конец и уходить оттуда.
 * Более того, иногда некоторые люди могут прекращать и начинать беспокоиться из-за того, что очередь не продвигается.
 * 
 * Реализуйте обработку следующих операций над очередью:
 * WORRY i: пометить i-го человека с начала очереди (в нумерации с 0) как беспокоящегося;
 * QUIET i: пометить i-го человека как успокоившегося;
 * COME k: добавить k спокойных человек в конец очереди;
 * COME -k: убрать k человек из конца очереди;
 * WORRY_COUNT: узнать количество беспокоящихся людей в очереди.
 * Изначально очередь пуста.
 * 
 * Формат ввода
 * Количество операций Q, затем описания операций.
 *  
 * Для каждой операции WORRY i и QUIET i гарантируется, что человек с номером i существует в очереди на момент операции.
 * Для каждой операции COME -k гарантируется, что k не больше текущего размера очереди.
 * 
 * Формат вывода
 * Для каждой операции WORRY_COUNT выведите одно целое число — количество беспокоящихся людей в очереди.
 */

using namespace std;

int main()
{
	int comands_count;
	cin >> comands_count;

	vector<bool> queue;
	for (int i = 0; i < comands_count; i++)
	{
		string comand;
		cin >> comand;

		if (comand == "COME")
		{
			int length;
			cin >> length;
			for (int j = 0; j < abs(length); j++)
			{
				if (length > 0)
					queue.push_back(false);
				else
					if (length < 0)
						queue.pop_back();
			}
		}

		if (comand == "WORRY")
		{
			int index;
			cin >> index;
			queue[index] = true;
		}

		if (comand == "QUIET")
		{
			int index;
			cin >> index;
			queue[index] = false;
		}

		if (comand == "WORRY_COUNT")
		{
			int worryCount = 0;
			for (bool f : queue)
				if (f)
					worryCount++;
			cout << worryCount << endl;
		}
	}
}
