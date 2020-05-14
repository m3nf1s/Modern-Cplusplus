#include "Database.h"

#include <iostream>
#include <iomanip>

void Database::AddEvent(const Date& date, const std::string& event)
{
    if (!event.empty())
    {
        db_[date].insert(event);
    }
}

bool Database::DeleteEvent(const Date& date, const std::string& event)
{
    if (db_[date].count(event))
    {
        db_[date].erase(event);

        return true;
    }

    return false;
}

int Database::DeleteDate(const Date& date)
{
    const int count_event = db_[date].size();
    db_.erase(date);

    return count_event;
}

std::set<std::string> Database::Find(const Date& date) const
{
    if (db_.count(date))
    {
        return db_.at(date);
    }
    return std::set<std::string>();
}

void Database::Print() const
{
    for (const auto& [date, events] : db_)
    {
        bool is_first = true;
        for (const auto& event : events)
        {
            std::cout << std::setw(4) << std::setfill('0') << date.GetYear() << '-'
                      << std::setw(2) << std::setfill('0') << date.GetMonth() << '-'
                      << std::setw(2) << std::setfill('0') << date.GetDay() << ' '
                      << event << std::endl;
        }
    }
}
