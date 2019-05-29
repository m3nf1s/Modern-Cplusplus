/*
Даны значения температуры, наблюдавшиеся в течение N подряд идущих дней.
Найдите номера дней (в нумерации с нуля) со значением температуры выше среднего арифметического за все N дней.

Гарантируется, что среднее арифметическое значений температуры является целым числом.

Формат ввода
Вводится число N, затем N целых чисел — значения температуры в 0-й, 1-й, ... (N−1)-й день.
Гарантируется, что N не превышает миллиона (10^6), а значения температуры,
измеряющиеся в миллионных долях градусов по Цельсию, лежат в диапазоне от −10^8 до 10^8.
Проверять соблюдение этих ограничений не нужно: вы можете ориентироваться на них при выборе наиболее подходящих типов для переменных.

Формат вывода
Первое число K — количество дней, значение температуры в которых выше среднего арифметического.
Затем K целых чисел — номера этих дней.
*/

#include <iostream>
#include <vector>

int main()
{
	size_t day_count{ 0 };
	int64_t sum{ 0 };
	size_t day{ 0 };

	std::vector<int> temperatures;

	std::cin >> day_count;

	for (size_t i = 0; i < day_count; i++)
	{
		int64_t temperature{ 0 };
		std::cin >> temperature;

		temperatures.push_back(temperature);
		sum += temperature;
	}

	int average = sum / static_cast<int64_t>(day_count);

	for (const int temperature : temperatures)
	{
		if (temperature > average)
			day++;
	}

	std::cout << day << std::endl;

	bool first{ true };
	for (size_t i = 0; i < temperatures.size(); ++i)
	{
		if (temperatures.at(i) > average)
		{
			if (first)
			{
				std::cout << i;
				first = false;
			}
			else
			{
				std::cout << ' ' << i;
			}
		}
	}
}