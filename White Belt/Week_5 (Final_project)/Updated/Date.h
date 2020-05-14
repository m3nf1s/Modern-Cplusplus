#pragma once

#include <sstream>

class Date
{
public:
    Date() = default;
    Date(const int year, const int month, const int day);

    int GetYear()  const;
    int GetMonth() const;
    int GetDay()   const;
private:
    int year_ { 0 },
        month_{ 0 },
        day_  { 0 };
};

int           ReadInt(std::stringstream& ss, bool& flag);
void          CheckSymbol(std::stringstream& ss, bool& flag);
bool          operator<(const Date& lhs, const Date& rhs);
std::istream& operator>>(std::istream& is, Date& date);