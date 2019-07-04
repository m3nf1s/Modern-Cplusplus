#pragma once

#include "date.h"
#include <string>
#include <map>
#include <vector>

using namespace std;

class Database
{
public:
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
	map<Date, vector<string>> base_;
};