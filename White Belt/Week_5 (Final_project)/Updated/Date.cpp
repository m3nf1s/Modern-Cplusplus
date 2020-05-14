#include "Date.h"

#include <stdexcept>
#include <tuple>

Date::Date(const int year, const int month, const int day)
{
    year_ = year;

    if (month <= 0 || month > 12)
    {
        throw std::invalid_argument("Month value is invalid: " + std::to_string(month));
    }
    month_ = month;

    if (day <= 0 || day > 31)
    {
        throw std::invalid_argument("Day value is invalid: " + std::to_string(day));
    }
    day_ = day;

}

int Date::GetYear() const
{
    return year_;
}

int Date::GetMonth() const
{
    return month_;
}

int Date::GetDay() const
{
    return day_;
}

int ReadInt(std::stringstream& ss, bool& flag)
{
    int number{};
    flag = flag && (ss >> number);
    return number;
}

void CheckSymbol(std::stringstream& ss, bool& flag)
{
    flag = flag && (ss.peek() == '-');
    ss.ignore(1);
}

bool operator<(const Date& lhs, const Date& rhs)
{
    return std::tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) <
           std::tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}

std::istream& operator>>(std::istream& is, Date& date)
{
    std::string date_string;
    is >> date_string;
    std::stringstream ss(date_string);
    bool is_correct = true;

    const int year = ReadInt(ss, is_correct);
    CheckSymbol(ss, is_correct);

    const int month = ReadInt(ss, is_correct);
    CheckSymbol(ss, is_correct);

    const int day = ReadInt(ss, is_correct);

    if (!is_correct || !ss.eof())
    {
        throw std::invalid_argument("Wrong date format: " + date_string);
    }

    date = { year, month, day };

    return is;
}
