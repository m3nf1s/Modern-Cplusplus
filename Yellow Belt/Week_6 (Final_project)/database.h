#pragma once

#include "date.h"

#include <iostream>
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
	void Print(ostream& os) const;

	//удаление из БД при условии
	template<class Func>
	int RemoveIf(Func predicate)
	{
		int count = 0;

		vector<Date> null_size_date; //массив дат, с нулевыми событиями

		for (auto it = base_.begin(); it != base_.end(); it++)
		{
			auto date = it->first;

			auto remove = stable_partition(it->second.begin(),
											it->second.end(),
											[predicate, date](const string& ev)
											{
												return !predicate(date, ev);
											});

			count += it->second.end() - remove; //подсчет количества удаляемых событий

			vector<string> buffer = { remove, it->second.end() }; //массив из событий, которые будем удалять в set<string>
			//удаляем события из set<string>
			for (const auto& e : buffer)
			{
				unique_base_.at(date).erase(e);
			}
			//удаляем события из vector<string>
			it->second.erase(remove, it->second.end());
			//проверяем на пустоту массив с событиями
			//если массив пустой, то добавляем в массив дату, чтобы удалить из map
			if (it->second.size() == 0)
			{
				null_size_date.push_back(it->first);
			}
		}
		//проводим удаление в БД пустых дат
		for (const auto& date : null_size_date)
		{
			base_.erase(date);
			unique_base_.erase(date);
		}

		return count;
	}
	//Поиск в БД дат-событий, которые удовлетворяет поиску
	template<class Func>
	vector<pair<Date, string>> FindIf(Func predicate) const
	{
		vector<pair<Date, string>> result;

		for (auto it = base_.begin(); it != base_.end(); ++it)
		{
			for (const string& ev : it->second)
			{
				if (predicate(it->first, ev))
				{
					result.push_back(make_pair(it->first, ev));
				}
			}
		}

		return result;
	}

	pair<Date, string> Last(const Date& date) const;

	
private:
	map<Date, vector<string>> base_; //Словарь для хранения дат-событий в порядко добавления
	map<Date, set<string>> unique_base_; //Словарь для быстрого поиска на уникальность событий, с последующим добавлением в base_
};

ostream& operator<< (ostream& os, const pair<Date, string>& pair);