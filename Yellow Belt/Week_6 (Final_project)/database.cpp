#include "database.h"
#include <algorithm>
#include <iomanip>

void Database::Add(const Date& date, const string& new_event)
{
	if (!new_event.empty())
	{
		auto events_begin = base_[date].begin();
		auto events_end = base_[date].end();

		auto it = find(events_begin, events_end, new_event);
		if (it == base_[date].end())
		{
			base_[date].push_back(new_event);
		}
	}
}

void Database::Print(ostream& os)
{
	for (const auto& [date, events] : base_)
	{
		for (const auto& event : events)
		{
			os << setw(4) << setfill('0') << date.year_ <<
				setw(2) << setfill('0') << date.month_ <<
				setw(2) << setfill('0') << date.day_ <<
				' ' << event << endl;
		}
	}
}
