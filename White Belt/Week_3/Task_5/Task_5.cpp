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
		int max_year_fn = FindMaxYear(year, list_first_name);
		int max_year_ln = FindMaxYear(year, list_last_name);

		std::vector<std::string> history_fn = GetHistoryName(max_year_fn, list_first_name);
		std::vector<std::string> history_ln = GetHistoryName(max_year_ln, list_last_name);

		if (list_first_name.count(max_year_fn) == 1 && list_last_name.count(max_year_ln) == 1)
		{


			if (history_fn.empty() && history_ln.empty())
			{
				return list_first_name[max_year_fn] + " " + list_last_name[max_year_ln];
			}

			if (!history_fn.empty() && history_ln.empty())
			{
				std::string str = GetHistory(history_fn);

				return list_first_name[max_year_fn] + " (" + str + ") " + list_last_name[max_year_ln];
			}

			if(history_fn.empty() && !history_ln.empty())
			{
				std::string str = GetHistory(history_ln);

				return list_first_name[max_year_fn] + " " + list_last_name[max_year_ln] + " (" + str + ")";
			}

			if(!history_fn.empty() && !history_ln.empty())
			{
				std::string str_fn = GetHistory(history_fn);
				std::string str_ln = GetHistory(history_ln);

				return list_first_name[max_year_fn] + " (" + str_fn + ") " + list_last_name[max_year_ln] + " (" + str_ln + ")";
			}
		}

		if (list_first_name.count(max_year_fn) == 1 && list_last_name.count(max_year_ln) != 1)
		{
			if(!history_fn.empty())
			{
				std::string str = GetHistory(history_fn);

				return list_first_name[max_year_fn] + " ("+ str + ") "+ "with unknown last name";
			}
			return list_first_name[max_year_fn] + " with unknown last name";
		}

		if (list_first_name.count(max_year_fn) != 1 && list_last_name.count(max_year_ln) == 1)
		{
			if (!history_ln.empty())
			{
				std::string str = GetHistory(history_ln);

				return list_last_name[max_year_ln] + " (" + str + ") " + " with unknown first name";
			}
			return list_last_name[max_year_ln] + " with unknown first name";
		}

		return "Incognito";
	}
private:
	std::map<int, std::string> list_first_name;
	std::map<int, std::string> list_last_name;

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
		std::reverse(vec.begin(),vec.end());
	}

	std::vector<std::string> GetHistoryName(int max, std::map<int,std::string>& list) const
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
			if (vec[vec.size() - 1] == list[max])
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
	//Person person;

	//person.ChangeFirstName(1965, "Polina");
	//person.ChangeLastName(1967, "Sergeeva");
	//for (int year : {1900, 1965, 1990})
	//{
	//	std::cout << person.GetFullNameWithHistory(year) << std::endl;
	//}

	//person.ChangeFirstName(1970, "Appolinaria");
	//for (int year : {1969, 1970})
	//{
	//	std::cout << person.GetFullNameWithHistory(year) << std::endl;
	//}

	//person.ChangeLastName(1968, "Volkova");
	//for (int year : {1969, 1970})
	//{
	//	std::cout << person.GetFullNameWithHistory(year) << std::endl;
	//}

	//person.ChangeFirstName(1990, "Polina");
	//person.ChangeLastName(1990, "Volkova-Sergeeva");
	//std::cout << person.GetFullNameWithHistory(1990) << std::endl;

	//person.ChangeFirstName(1966, "Pauline");
	//std::cout << person.GetFullNameWithHistory(1966) << std::endl;

	//person.ChangeLastName(1960, "Sergeeva");
	//for (int year : {1960, 1967})
	//{
	//	std::cout << person.GetFullNameWithHistory(year) << std::endl;
	//}

	//person.ChangeLastName(1961, "Ivanova");
	//std::cout << person.GetFullNameWithHistory(1967) << std::endl;

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
	person.ChangeLastName(1990, "Volkova"); //-Sergeeva
	std::cout << person.GetFullNameWithHistory(1990) << std::endl;

	person.ChangeFirstName(1966, "Pauline");
	std::cout << person.GetFullNameWithHistory(1966) << std::endl;

	person.ChangeLastName(1960, "Sergeeva");
	for (int year : {1960, 1967}) {
		std::cout << person.GetFullNameWithHistory(year) << std::endl;
	}

	person.ChangeLastName(1961, "Ivanova");
	for (int year : {1960, 1967, 1990}) {
		std::cout << person.GetFullNameWithHistory(year) << std::endl;
	}

	person.ChangeFirstName(1901, "Polina");
	person.ChangeLastName(1901, "Sergeeva");
	for (int year : {1900, 1960, 1967, 1990, 1991}) {
		std::cout << person.GetFullNameWithHistory(year) << std::endl;
	}
}