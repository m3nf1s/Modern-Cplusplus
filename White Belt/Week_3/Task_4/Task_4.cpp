// Task_4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

/*
Реализуйте класс для человека, поддерживающий историю изменений человеком своих фамилии и имени.

Считайте, что в каждый год может произойти не более одного изменения фамилии и не более одного изменения имени.
При этом с течением времени могут открываться всё новые факты из прошлого человека,
	поэтому года́ в последовательных вызовах методов ChangeLastName и ChangeFirstName не обязаны возрастать.

Гарантируется, что все имена и фамилии непусты.

Строка, возвращаемая методом GetFullName,
должна содержать разделённые одним пробелом имя и фамилию человека по состоянию на конец данного года.

Если к данному году не случилось ни одного изменения фамилии и имени, верните строку "Incognito".
Если к данному году случилось изменение фамилии, но не было ни одного изменения имени,
	верните "last_name with unknown first name".
Если к данному году случилось изменение имени, но не было ни одного изменения фамилии,
	верните "first_name with unknown last name".
*/
#include <iostream>
#include <string>
#include <map>
#include <algorithm>

class Person
{
public:
	void ChangeFirstName(int year, const std::string& firts_name)
	{
		list_first_name[year] = firts_name;
	}
	void ChangeLastName(int year, const std::string& last_name)
	{
		list_last_name[year] = last_name;
	}
	std::string GetFullName(int year)
	{
		int year_list_fn = INT32_MIN;
		int year_list_ln = INT32_MIN;

		for (const auto& item : list_first_name)
		{
			if (item.first <= year)
				year_list_fn = item.first;
		}

		for (const auto& item : list_last_name)
		{
			if (item.first <= year)
				year_list_ln = item.first;
		}

		if (list_first_name.count(year_list_fn) == 1 && list_last_name.count(year_list_ln) == 1)
		{
			return list_first_name[year_list_fn] + " " + list_last_name[year_list_ln];
		}
			else if (list_first_name.count(year_list_fn) == 1 && list_last_name.count(year_list_ln) != 1)
			{
				return list_first_name[year_list_fn] + " with unknown last name";
			}
				else if (list_first_name.count(year_list_fn) != 1 && list_last_name.count(year_list_ln) == 1)
				{
					return list_last_name[year_list_ln] + " with unknown first name";
				}

		return "Incognito";
	}
private:
	std::map<int, std::string> list_first_name;
	std::map<int, std::string> list_last_name;
};

int main()
{
	Person person;

	person.ChangeFirstName(1965, "Polina");
	person.ChangeLastName(1967, "Sergeeva");
	for (int year : {1900, 1965, 1990}) {
		std::cout << person.GetFullName(year) << std::endl;
	}

	person.ChangeFirstName(1970, "Appolinaria");
	for (int year : {1969, 1970}) {
		std::cout << person.GetFullName(year) << std::endl;
	}

	person.ChangeLastName(1968, "Volkova");
	for (int year : {1969, 1970}) {
		std::cout << person.GetFullName(year) << std::endl;
	}
}