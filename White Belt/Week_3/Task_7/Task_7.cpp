// Task_7.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

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
	Person(const std::string& first_name, const std::string& last_name, const int year)
	{
		birth_year = year;
		list_fn[year] = first_name;
		list_ln[year] = last_name;
	}
	/// <summary>
	/// Изменение имени
	/// </summary>
	/// <param name="year">Год изменения</param>
	/// <param name="first_name">Имя</param>
	void ChangeFirstName(int year, const std::string& first_name)
	{
		if (year > birth_year)
			list_fn[year] = first_name;
	}
	/// <summary>
	/// Изменение фамилии
	/// </summary>
	/// <param name="year">Год изменения</param>
	/// <param name="last_name">Фамилия</param>
	void ChangeLastName(int year, const std::string& last_name)
	{
		if (year > birth_year)
			list_ln[year] = last_name;
	}
	/// <summary>
	/// Получение имени и фамилии на определенный год
	/// </summary>
	/// <param name="year">Год</param>
	/// <returns>Имя и фамилия на указанный год</returns>
	std::string GetFullName(int year)
	{
		int actual_year_fn = FindActualYear(year, list_fn);
		int actual_year_ln = FindActualYear(year, list_ln);

		if (year >= birth_year)
		{
			if (list_fn.count(actual_year_fn) == 0 && list_ln.count(actual_year_ln) == 0)
			{
				return "Incognito";
			}

			if (list_fn.count(actual_year_fn) == 1 && list_ln.count(actual_year_ln) == 0)
			{
				return list_fn[actual_year_fn] + " with unknow last name";
			}

			if (list_fn.count(actual_year_fn) == 0 && list_ln.count(actual_year_ln) == 1)
			{
				return list_ln[actual_year_ln] + "with unknow first name";
			}

			if (list_fn.count(actual_year_fn) == 1 && list_ln.count(actual_year_ln) == 1)
			{
				return list_fn[actual_year_fn] + " " + list_ln[actual_year_ln];
			}
		}

		return "No person";
	}
	/// <summary>
	/// Получения имени и фамилии с историей изменения на определенный год
	/// </summary>
	/// <param name="year">Год</param>
	/// <returns>Имя и фамилия с историей</returns>
	std::string GetFullNameWithHistory(int year)
	{
		int actual_year_fn = FindActualYear(year, list_fn);
		int actual_year_ln = FindActualYear(year, list_ln);

		std::string history_fn = GetHistory(actual_year_fn, list_fn);
		std::string history_ln = GetHistory(actual_year_ln, list_ln);

		if (history_fn.empty() && history_ln.empty())
		{
			return GetFullName(year);
		}

		return list_fn[actual_year_fn] + " " + history_fn + " " + list_ln[actual_year_ln] + " " + history_ln;
	}
private:	
	std::map<int, std::string> list_fn; //список год изменения - имя
	std::map<int, std::string> list_ln; // список год изменения - фамилия
	int birth_year; // год рождения

	/// <summary>
	/// Нахождения последнего года изменения имени/фамилии к искомому году
	/// </summary>
	/// <param name="year">Искомый год</param>
	/// <param name="m">Список с именами/фамилиями</param>
	/// <returns>Актуальный год</returns>
	int FindActualYear(int year, std::map<int, std::string> m)
	{
		int y = INT32_MIN;
		for (const auto& pair : m)
		{
			if (pair.first <= year)
			{
				y = pair.first;
			}
		}

		return y;
	}

	/// <summary>
	/// Получение истории
	/// </summary>
	/// <param name="actual_year">До какого года будем искать</param>
	/// <param name="m">Список, в котором будем вести поиск</param>
	/// <returns>Строка с историей</returns>
	std::string GetHistory(int actual_year, std::map<int, std::string>& m)
	{
		std::string buff = "";
		std::vector<std::string> vec;
		for (const auto& pair : m)
		{
			if (pair.second != buff && pair.first < actual_year)
			{
				vec.push_back(pair.second);
				buff = pair.second;
			}
			else
				break;
		}

		if (!vec.empty())
			if (vec[vec.size() - 1] == m[actual_year])
				vec.pop_back();

		Reverse(vec);

		std::string result;

		if (!vec.empty())
		{
			result = "(";

			for (int i = 0; i < vec.size(); ++i)
			{
				if (i == 0)
					result += vec[0];
				else
					result += ", " + vec[i];
			}
			result += ")";
		}

		return result;
	}

	/// <summary>
	/// Реверсировать вектор
	/// </summary>
	/// <param name="vec">Вектор, в котором будем менять порядок</param>
	void Reverse(std::vector<std::string>& vec) const
	{
		std::reverse(vec.begin(), vec.end());
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