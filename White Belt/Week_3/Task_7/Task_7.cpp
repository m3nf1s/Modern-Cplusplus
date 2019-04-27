/*
Дополните класс Person из задачи «Имена и фамилии — 2» конструктором,
	позволяющим задать имя и фамилию человека при рождении, а также сам год рождения.
Класс не должен иметь конструктора по умолчанию.

При получении на вход года, который меньше года рождения:
* методы GetFullName и GetFullNameWithHistory должны отдавать "No person";
* методы ChangeFirstName и ChangeLastName должны игнорировать запрос.

Кроме того, необходимо объявить константными все методы, которые по сути ими являются.
*/

#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>

class Person
{
public:
	Person(const std::string& first_name, const std::string& last_name, const int new_year)
	{
		birth_year = new_year;
		list_first_name[new_year] = first_name;
		list_last_name[new_year] = last_name;
	}

	void ChangeFirstName(int year, const std::string& firts_name)
	{
		if(year >= birth_year)
			list_first_name[year] = firts_name;
	}

	void ChangeLastName(int year, const std::string& last_name)
	{
		if (year >= birth_year)
			list_last_name[year] = last_name;
	}

	std::string GetFullName(int year) const 
	{
		if (year >= birth_year)
		{
			int year_list_fn = FindMaxYear(year, list_first_name);
			int year_list_ln = FindMaxYear(year, list_last_name);


			if (list_first_name.count(year_list_fn) == 1 && list_last_name.count(year_list_ln) == 1)
			{
				return list_first_name.at(year_list_fn) + " " + list_last_name.at(year_list_ln);
			}

			if (list_first_name.count(year_list_fn) == 1 && list_last_name.count(year_list_ln) != 1)
			{
				return list_first_name.at(year_list_fn) + " with unknown last name";
			}

			if (list_first_name.count(year_list_fn) != 1 && list_last_name.count(year_list_ln) == 1)
			{
				return list_last_name.at(year_list_ln) + " with unknown first name";
			}
		}

		return "No person";
	}

	std::string GetFullNameWithHistory(int year) const
	{
		if (year >= birth_year)
		{
			int max_year_fn = FindMaxYear(year, list_first_name);
			int max_year_ln = FindMaxYear(year, list_last_name);

			std::vector<std::string> history_fn = GetHistoryName(max_year_fn, list_first_name);
			std::vector<std::string> history_ln = GetHistoryName(max_year_ln, list_last_name);

			if (list_first_name.count(max_year_fn) == 1 && list_last_name.count(max_year_ln) == 1)
			{


				if (history_fn.empty() && history_ln.empty())
				{
					return list_first_name.at(max_year_fn) + " " + list_last_name.at(max_year_ln);
				}

				if (!history_fn.empty() && history_ln.empty())
				{
					std::string str = GetHistory(history_fn);

					return list_first_name.at(max_year_fn) + " (" + str + ") " + list_last_name.at(max_year_ln);
				}

				if (history_fn.empty() && !history_ln.empty())
				{
					std::string str = GetHistory(history_ln);

					return list_first_name.at(max_year_fn) + " " + list_last_name.at(max_year_ln) + " (" + str + ")";
				}

				if (!history_fn.empty() && !history_ln.empty())
				{
					std::string str_fn = GetHistory(history_fn);
					std::string str_ln = GetHistory(history_ln);

					return list_first_name.at(max_year_fn) + " (" + str_fn + ") " + list_last_name.at(max_year_ln) + " (" + str_ln + ")";
				}
			}

			if (list_first_name.count(max_year_fn) == 1 && list_last_name.count(max_year_ln) != 1)
			{
				if (!history_fn.empty())
				{
					std::string str = GetHistory(history_fn);

					return list_first_name.at(max_year_fn) + " (" + str + ") " + "with unknown last name";
				}
				return list_first_name.at(max_year_fn) + " with unknown last name";
			}

			if (list_first_name.count(max_year_fn) != 1 && list_last_name.count(max_year_ln) == 1)
			{
				if (!history_ln.empty())
				{
					std::string str = GetHistory(history_ln);

					return list_last_name.at(max_year_ln) + " (" + str + ") " + " with unknown first name";
				}
				return list_last_name.at(max_year_ln) + " with unknown first name";
			}
		}

		return "No person";
	}
private:
	std::map<int, std::string> list_first_name;
	std::map<int, std::string> list_last_name;
	int birth_year;

	int FindMaxYear(const int year, const std::map<int, std::string>& list) const
	{
		int max = INT32_MIN;
		for (const auto& item : list)
		{
			if (item.first <= year)
				max = item.first;
			else
				break;
		}
		return max;
	}

	void ReverseVector(std::vector<std::string>& vec) const
	{
		std::reverse(vec.begin(), vec.end());
	}

	std::vector<std::string> GetHistoryName(const int max, const std::map<int, std::string>& list) const
	{
		std::vector<std::string> vec;
		std::string buff;
		for (const auto& pair : list)
		{
			if (pair.first < max && pair.second != buff)
			{
				vec.push_back(pair.second);
				buff = pair.second;
			}
		}

		if (!vec.empty())
			if (vec[vec.size() - 1] == list.at(max))
				vec.pop_back();

		ReverseVector(vec);

		return vec;
	}

	std::string GetHistory(const std::vector<std::string>& vec) const
	{
		std::string str;
		for (int i = 0; i < vec.size(); ++i)
		{
			if (i == 0)
				str += vec[i];
			else
				str += ", " + vec[i];
		}

		return str;
	}
};

int main()
{
	Person person("Polina", "Sergeeva", 1960);
	//for (int year : {1959, 1960}) {
	//	std::cout << person.GetFullNameWithHistory(year) << std::endl;
	//}

	//person.ChangeFirstName(1965, "Appolinaria");
	//person.ChangeLastName(1967, "Ivanova");
	//for (int year : {1965, 1967}) {
	//	std::cout << person.GetFullNameWithHistory(year) << std::endl;
	//}

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

	return 0;
}