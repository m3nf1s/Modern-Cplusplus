#include "query.h"
#include <map>

std::istream& operator >> (std::istream& is, Query& q)
{
	std::string cmd;
	is >> cmd;

	std::map<std::string, QueryType> commands =
	{
		{"NEW_BUS", QueryType::NewBus},
		{"BUSES_FOR_STOP",QueryType::BusesForStop},
		{"STOPS_FOR_BUS", QueryType::StopsForBus},
		{"ALL_BUSES", QueryType::AllBuses}
	};

	q.type = commands.at(cmd);

	switch (q.type)
	{
	case QueryType::NewBus:
		is >> q.bus;
		is.ignore(1);
		size_t stop_count;
		is >> stop_count;
		q.stops.clear();
		for (size_t i = 0; i < stop_count; i++)
		{
			std::string stop;
			is >> stop;
			q.stops.push_back(stop);
		}
		break;
	case QueryType::BusesForStop:
		is >> q.stop;
		break;
	case QueryType::StopsForBus:
		is >> q.bus;
		break;
	case QueryType::AllBuses:
		;
		break;
	}

	return is;
}