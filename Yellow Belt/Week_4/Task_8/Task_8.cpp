/*
Напишите функцию FindNearestElement,
	для множества целых чисел numbers и данного числа border возвращающую итератор на элемент множества,
	ближайший к border.
Если ближайших элементов несколько, верните итератор на наименьший из них.
*/

#include <iostream>
#include <set>
#include <iterator>

std::set<int>::const_iterator FindNearestElement(const std::set<int>& numbers, int border);

int main()
{
	std::set<int> numbers = { 1, 4, 6 };
	std::cout <<
		*FindNearestElement(numbers, 0) << " " <<
		*FindNearestElement(numbers, 3) << " " <<
		*FindNearestElement(numbers, 5) << " " <<
		*FindNearestElement(numbers, 6) << " " <<
		*FindNearestElement(numbers, 100) << std::endl;

	std::set<int> empty_set;

	std::cout << (FindNearestElement(empty_set, 8) == end(empty_set)) << std::endl;

	return 0;
}

std::set<int>::const_iterator FindNearestElement(const std::set<int>& numbers, int border)
{
	
	const auto first_not_less = numbers.lower_bound(border);
	//если border меньше Min, то возвращаем begin()
	if (first_not_less == numbers.begin())
	{
		return first_not_less;
	}

	const auto last_less = prev(first_not_less);
	//если border больше Max и указывает на end(), то возвращаем предыдущее
	if (first_not_less == numbers.end())
	{
		return last_less;
	}

	//сравнение к какому значению ближе border к last_less или first_not_less
	const bool is_left = (border - *first_not_less <= *last_less - border);
	return is_left ? last_less : first_not_less;
}