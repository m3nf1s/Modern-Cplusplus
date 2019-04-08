// Task_5.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

/*
Дополните класс из предыдущей задачи «Имена и фамилии — 1» методом GetFullNameWithHistory:
В отличие от метода GetFullName,
	метод GetFullNameWithHistory должен вернуть не только последние имя и фамилию к концу данного года,
	но ещё и все предыдущие имена и фамилии в обратном хронологическом порядке.
Если текущие факты говорят о том, что человек два раза подряд изменил фамилию или имя на одно и то же,
	второе изменение при формировании истории нужно игнорировать.
*/
#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>

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
		int year_list_fn = FindMaxYear(year, list_first_name);
		int year_list_ln = FindMaxYear(year, list_last_name);


		if (list_first_name.count(year_list_fn) == 1 && list_last_name.count(year_list_ln) == 1)
		{
			return list_first_name[year_list_fn] + " " + list_last_name[year_list_ln];
		}
		
		if (list_first_name.count(year_list_fn) == 1 && list_last_name.count(year_list_ln) != 1)
		{
			return list_first_name[year_list_fn] + " with with unknown last name";
		}
		
		if (list_first_name.count(year_list_fn) != 1 && list_last_name.count(year_list_ln) == 1)
		{
			return list_last_name[year_list_ln] + " with unknown first name";
		}

		return "Incognito";
	}
	std::string GetFullNameWithHistory(int year)
	{
		if (list_first_name.size() < 2 && list_last_name.size() < 2)
		{
			return GetFullName(year);
		}
		else
		{

			int year_list_fn = FindMaxYear(year, list_first_name);
			int year_list_ln = FindMaxYear(year, list_last_name);

			std::vector<std::string> history_fist_name;
			std::vector<std::string> history_last_name;

			VectorPush(year_list_fn, list_first_name, history_fist_name);
			VectorPush(year_list_ln, list_last_name, history_last_name);

			std::string message1 = "";
			std::string message2 = "";

			for (const std::string& s : history_fist_name)
			{
				message1 += s + ",";
			}

			for (const std::string& s : history_last_name)
			{
				message2 += s + ",";
			}

			return list_first_name[year_list_fn] + " (" + message1 + ") " + list_last_name[year_list_ln] + " (" + message2 + ")";
		}
	}
private:
	std::map<int, std::string> list_first_name;
	std::map<int, std::string> list_last_name;

	int FindMaxYear(const int year, const std::map<int, std::string>& list)
	{
		int max = INT32_MIN;
		for (const auto& item : list)
		{
			if (item.first <= year)
				max = item.first;
		}
		return max;
	}

	void VectorPush(int max, std::map<int,std::string> list, std::vector<std::string>& vec)
	{
		for (const auto& pair : list)
		{
			if (pair.first < max)
				vec.push_back(pair.second);
		}
	}
};

int main()
{
	Person person;

	person.ChangeFirstName(1965, "Polina");
	person.ChangeLastName(1967, "Sergeeva");
	for (int year : {1900, 1965, 1990}) {
		std::cout << person.GetFullNameWithHistory(year) << std::endl;
	}

	person.ChangeFirstName(1970, "Appolinaria");
	for (int year : {1969, 1970}) {
		std::cout << person.GetFullNameWithHistory(year) << std::endl;
	}

	person.ChangeLastName(1968, "Volkova");
	for (int year : {1969, 1970}) {
		std::cout << person.GetFullNameWithHistory(year) << std::endl;
	}

	person.ChangeFirstName(1990, "Polina");
	person.ChangeLastName(1990, "Volkova-Sergeeva");
	std::cout << person.GetFullNameWithHistory(1990) << std::endl;

	person.ChangeFirstName(1966, "Pauline");
	std::cout << person.GetFullNameWithHistory(1966) << std::endl;

	person.ChangeLastName(1960, "Sergeeva");
	for (int year : {1960, 1967}) {
		std::cout << person.GetFullNameWithHistory(year) << std::endl;
	}

	person.ChangeLastName(1961, "Ivanova");
	std::cout << person.GetFullNameWithHistory(1967) << std::endl;
}