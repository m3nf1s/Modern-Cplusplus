/*
	У каждого спортсмена на футболке написан уникальный номер.
	Спортсмены по очереди выходят из раздевалки и должны построиться на стадионе.
	Тренер каждому выходящему спортсмену называет номер того спортсмена, перед которым нужно встать.
	Если спортсмена с названным номером на поле нет, то нужно встать в конец шеренги.

	В стандартном вводе сначала задано натуральное число n, не превосходящее 100000, — количество спортсменов.
	Далее идут n пар неотрицательных целых чисел, не превосходящих 100000.
	Первое число в паре — номер очередного выходящего спортсмена.
	Второе число в паре — номер того спортсмена, перед которым должен встать текущий.

	Напечатайте в стандартный вывод номера спортсменов в порядке построения на поле.

	Ограничение по времени — 0,8 с.
*/

#include <iostream>
#include <list>
#include <vector>

int main()
{
	const int MAX_SPORTSMEN = 100'000;

	using Position = std::list<int>::iterator;

	size_t n_sportsmen;
	std::cin >> n_sportsmen;

	std::list<int> sportsmen;
	std::vector<Position> sportsmen_pos(MAX_SPORTSMEN + 1, sportsmen.begin());

	for (size_t i = 0; i < n_sportsmen; ++i)
	{
		int pos, next_pos;
		std::cin >> pos >> next_pos;
		sportsmen_pos[pos] = sportsmen.insert(sportsmen_pos[next_pos], pos);
	}

	for (auto& i : sportsmen)
	{
		std::cout << i << '\n';
	}
}