// Task_4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

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
				return list_first_name[year_list_fn] + " with with unknown last name";
			}
				else if (list_first_name.count(year_list_fn) != 1 && list_last_name.count(year_list_ln) == 1)
				{
					return list_last_name[year] + " with unknown first name";
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