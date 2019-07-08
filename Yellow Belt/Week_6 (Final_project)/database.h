#pragma once

#include "date.h"
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <tuple>

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
		auto it = find_if(base_.begin(), base_.end(), predicate);
	}

	template <class Func>
	string Last(Func function)
	{
		
	}
private:
	map<Date, vector<string>> base_;
};

bool operator< (const Date& lhs, const Date& rhs)
{
	auto lhs_key = tie(lhs.year_, lhs.month_, lhs.day_);
	auto rhs_key = tie(rhs.year_, rhs.month_, rhs.day_);

	return lhs_key < rhs_key;
}