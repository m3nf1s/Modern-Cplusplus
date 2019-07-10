#pragma once

#include "date.h"
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <tuple>
#include <set>

using namespace std;

class Database
{
public:

	//добавление события в БД
	void Add(const Date& date, const string& new_event);

	//вывод всех событий, которые хранятся в БД
	void Print(ostream& os);

	template<class Func>
	int RemoveIf(Func predicate)
	{
		
	}

	template<class Func>
	vector<string> FindIf(Func predicate)
	{
	
	}

	pair<Date, string> Last(const Date& date);
private:
	map<Date, vector<string>> base_;
	map<Date, set<string>> unique_base_;
};

