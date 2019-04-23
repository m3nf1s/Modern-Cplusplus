#include "pch.h"
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <iomanip>
#include <sstream>
#include <exception>

class Date {
public:
	Date(const int new_year, const int new_month, const int new_day)
	{
		if (new_month > 12 || new_month <= 0)
			throw std::invalid_argument("Month value is invalid: " + std::to_string(new_month));

		if (new_day > 31 || new_day <= 0)
			throw std::invalid_argument("Day value is invalid: " + std::to_string(new_day));

		_year = new_year;
		_month = new_month;
		_day = new_day;
	}

	Date()
	{
		_year = 0;
		_month = 0;
		_day = 0;
	}

	int GetYear() const
	{
		return _year;
	}

	int GetMonth() const
	{
		return _month;
	}

	int GetDay() const
	{
		return _day;
	}

private:
	int _year;
	int _month;
	int _day;
};

bool operator<(const Date& lhs, const Date& rhs)
{
	if (lhs.GetYear() == rhs.GetYear() && lhs.GetMonth() == rhs.GetMonth())
		return lhs.GetDay() < rhs.GetDay();

	if (lhs.GetYear() == rhs.GetYear())
		return lhs.GetMonth() < rhs.GetMonth();

	return lhs.GetYear() < rhs.GetYear();
}

void CheckSymbol(std::stringstream& stream, const std::string& date)
{
	if (stream.peek() != '-')
		throw std::invalid_argument("Wrong date format: " + date);
	stream.ignore(1);
}

std::istream& operator>> (std::istream& stream, Date& obj)
{
	int year = 0, month = 0, day = 0;
	std::string date;
	stream >> date;
	bool flag = true;
	std::stringstream str(date);

	flag = flag && (str >> year);
	CheckSymbol(str, date);
	flag = flag && (str >> month);
	CheckSymbol(str, date);
	flag = flag && (str >> day);

	std::string garbage;
	str >> garbage;
	if(!flag || !garbage.empty())
		throw std::invalid_argument("Wrong date format: " + date);

	obj = { year,month,day};

	return stream;
}

class Database
{
public:
	void AddEvent(const Date& date, const std::string& event)
	{
		if (!event.empty())
		{
			_calendar[date].insert(event);
		}
	}

	bool DeleteEvent(const Date& date, const std::string& event)
	{
		if(_calendar.count(date) == 1)
		{
			if(_calendar[date].count(event))
			{
				std::cout << "Deleted successfully" << std::endl;
				return _calendar[date].erase(event);
			}
		}

		std::cout << "Event not found" << std::endl;
		return false;
	}

	int  DeleteDate(const Date& date)
	{
		int event_count = 0;
		if(_calendar.count(date) == 1)
		{
			event_count = _calendar[date].size();
			_calendar.erase(date);
		}

		return event_count;
	}

	void Find(const Date& date) const
	{
		if(_calendar.count(date) == 1)
		{
			for (const auto& v : _calendar.at(date))
			{
				std::cout << v << std::endl;
			}
		}
	}

	void Print() const
	{
		for (const auto& pair : _calendar)
		{
			for (const auto& e : pair.second)
			{
				std::cout << std::setw(4) << std::setfill('0') << pair.first.GetYear() << '-'
					<< std::setw(2) << std::setfill('0') << pair.first.GetMonth() << '-'
					<< std::setw(2) << std::setfill('0') << pair.first.GetDay() << ' '  << e << std::endl;
			}
		}
	}

private:	
	std::map<Date, std::set<std::string>> _calendar;
};

int main()
{
	Database db;

	std::string command;
	while (std::getline(std::cin, command))
	{
		try
		{
			std::stringstream str(command);

			std::string cmd;
			str >> cmd;

			if (cmd == "Add")
			{
				Date dt;
				std::string new_event;
				str >> dt >> new_event;

				//if(new_event.empty())
				//{
				//	std::string date = std::to_string(dt.GetYear()) + '-' + std::to_string(dt.GetMonth()) + '-' + std::to_string(dt.GetDay());
				//	throw std::invalid_argument("Wrong date format: " + date);
				//}
					

				db.AddEvent(dt, new_event);
			}
			else if (cmd == "Del")
			{
				Date dt;
				std::string current_event;

				str >> dt >> current_event;

				if (current_event.empty())
				{
					std::cout << "Deleted " << db.DeleteDate(dt) << " events" << std::endl;
				}
				else
				{
					db.DeleteEvent(dt, current_event);
				}
			}
			else if (cmd == "Find")
			{
				Date dt;
				str >> dt;

				db.Find(dt);
			}
			else if (cmd == "Print")
			{
				db.Print();
			}
			else if(!cmd.empty())
			{
				throw std::invalid_argument("Unknown command: " + cmd);
			}
		}
		catch (const std::exception& error)
		{
			std::cout << error.what() << std::endl;
			return 0;
		}
	}

	return 0;
}