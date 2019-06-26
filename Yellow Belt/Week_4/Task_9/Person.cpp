#include "Person.h"

void Person::ChangeFirstName(int year, const std::string& first_name)
{
	first_name_history_[year] = first_name;
}

void Person::ChangeLastName(int year, const std::string& last_name)
{
	last_name_history_[year] = last_name;
}

std::string Person::FindNameByYear(const std::map<int, std::string>& name_history, const int year)
{
	auto name_year = name_history.upper_bound(year);

	std::string name;
	if (name_year != name_history.begin())
	{
		name = std::prev(name_year)->second;
	}

	return name;
}

std::string Person::GetFullName(int year)
{
	const std::string first_name = FindNameByYear(first_name_history_, year);
	const std::string last_name = FindNameByYear(last_name_history_, year);

	if (first_name.empty() && last_name.empty())
	{
		return "Incognito";
	}

	if (!first_name.empty() && last_name.empty())
	{
		return first_name + " with unknown last name";
	}

	if (first_name.empty() && !last_name.empty())
	{
		return last_name + " with unknown first name";
	}

	return first_name + " " + last_name;
}