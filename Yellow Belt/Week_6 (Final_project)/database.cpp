#include <algorithm>
#include <iomanip>

#include "database.h"

//��������� ������� � ��
void Database::Add(const Date& date, const string& new_event)
{ 	
	if (unique_base_[date].count(new_event) == 0)
	{
		base_[date].push_back(new_event);
		unique_base_[date].insert(new_event);
	}
}
//������� ��� �� � ������� ����-�������
void Database::Print(ostream& os) const
{
	for (const auto& [date, events] : base_)
	{
		for (const auto& event : events)
		{			
				os << date << ' ' << event << endl;
		}		
	}
}
//������� ��������� ����������� ������� � ��������� ����
//��� ��������� ������� �� ���� ��
pair<Date, string> Database::Last(const Date& date) const
{
	if (base_.count(date))
	{
		if (base_.at(date).empty())
		{
			throw invalid_argument("");
		}

		return make_pair(date, base_.at(date).back());
	}

	auto it = base_.upper_bound(date);
	if (it == base_.begin())
	{
		throw invalid_argument("");
	}

	--it;

	if (it->second.empty())
	{
		throw invalid_argument("");
	}

	return make_pair(it->first, it->second.back());
}

ostream& operator<< (ostream& os, const pair<Date, string>& pair)
{
	return os << pair.first << ' ' << pair.second;
}