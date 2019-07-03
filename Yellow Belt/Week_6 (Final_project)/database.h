#pragma once

#include "date.h"
#include <string>
#include <map>
#include <set>

using namespace std;

class Database
{
	//добавление события в БД
	void Add(const Date& date, const string& new_event);
	//вывод всех событий, которые хранятся в БД
	void Print(ostream& os);
	//
	template<class Func>
	void RemoveIf(Func predicate)
	{

	}
	void FindIf(/*?*/);
	void Last(/*?*/);
private:
	map<Date, set<string>> base_;
};