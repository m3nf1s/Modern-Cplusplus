#pragma once

#include "date.h"
#include <string>
#include <map>
#include <set>

using namespace std;

class Database
{
	//���������� ������� � ��
	void Add(const Date& date, const string& new_event);
	//����� ���� �������, ������� �������� � ��
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