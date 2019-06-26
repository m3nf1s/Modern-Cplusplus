#pragma once

#include <string>
#include <map>

class Person
{
public:
	void ChangeFirstName(int year, const std::string& first_name);
	void ChangeLastName(int year, const std::string& last_name);
	std::string GetFullName(int year);
private:
	std::map<int, std::string> first_name_history_;
	std::map<int, std::string> last_name_history_;
	std::string FindNameByYear(const std::map<int, std::string>& name_history, const int year);
};