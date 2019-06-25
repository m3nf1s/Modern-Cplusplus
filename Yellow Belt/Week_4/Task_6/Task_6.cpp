﻿/*
В этой задаче вам необходимо вычислить различные демографические показатели для группы людей.
Человек представляется структурой Person:
	struct Person
	{
	  int age;  // возраст
	  Gender gender;  // пол
	  bool is_employed;  // имеет ли работу
	};

Тип Gender определён следующим образом:
	enum class Gender 
	{
	  FEMALE,
	  MALE
	};

Вам необходимо написать функцию PrintStats, получающую вектор людей,
	вычисляющую и выводящую медианный возраст для каждой из следующих групп людей:

	1) все люди;
	2) все женщины;
	3) все мужчины;
	4) все безработные женщины;
	5) все занятые женщины;
	6) все безработные мужчины;
	7) все занятые мужчины.

Все 7 чисел нужно вывести в строгом соответствии с форматом.

	void PrintStats(vector<Person> persons);
Принимая вектор по значению (а не по константной ссылке),
	вы получаете возможность модифицировать его копию произвольным образом и тем самым проще произвести вычисления.

Вычисление медианного возраста
Для вычисления медианного возраста группы людей вы должны использовать функцию ComputeMedianAge:
	template <typename InputIt>
	int ComputeMedianAge(InputIt range_begin, InputIt range_end);

Эту функцию не нужно реализовывать самостоятельно:
	мы реализовали её за вас и автоматически добавим к каждому вашему решению.

Функцию ComputeMedianAge можно вызвать и для пустого набора людей:
	её результат в этом случае и нужно считать медианным возрастом пустого набора людей.
*/

#include <iostream>
#include <vector>
#include "Person.h"

int main()
{
	std::vector<Person> persons = {
	{31, Gender::MALE, false},
	{40, Gender::FEMALE, true},
	{24, Gender::MALE, true},
	{20, Gender::FEMALE, true},
	{80, Gender::FEMALE, false},
	{78, Gender::MALE, false},
	{10, Gender::FEMALE, false},
	{55, Gender::MALE, true},
	};

	PrintStats(persons);
	return 0;
}