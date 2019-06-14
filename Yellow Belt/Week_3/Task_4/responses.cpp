#include "responses.h"

std::ostream& operator<< (std::ostream& os, const BusesForStopResponse& r)
{
	if (r.busesforstop.empty())
	{
		os << "No stop";
	}
	else
	{
		bool first = true;
		for (const auto& val : r.busesforstop)
		{
			if (first)
			{
				os << val;
				first = false;
			}
			else
			{
				os << ' ' << val;
			}
		}
	}
	return os;
}

std::ostream& operator<< (std::ostream& os, const StopsForBusResponse& r)
{
	//���������, ����� ������ ��������� �� ��� ������
	if (!r.stops.empty())
	{
		//���������� ������ ���������
		for (size_t i = 0; i < r.stops.size(); i++)
		{
			os << "Stop " << r.stops.at(i) << ": ";
			//������� ����������, ���� ������ �������� �� �������� ����� ��� ���������
			if (r.stops_buses.count(r.stops.at(i)) == 0)
			{
				os << "no interchange" << std::endl;
			}
			else
			{
				bool first = true;
				for (const auto& bus : r.stops_buses.at(r.stops.at(i)))
				{
					if (first)
					{
						os << bus;
						first = false;
					}
					else
					{
						os << " " << bus;
					}
				}
				if (i != r.stops.size() - 1)
				{
					os << std::endl;
				}
			}
		}
	}
	else
	{
		os << "No bus";
	}

	return os;
}

std::ostream& operator<< (std::ostream& os, const AllBusesResponse& r)
{
	if (!r.allbuses.empty())
	{
		size_t i{ 0 };
		for (const auto& [bus, stops] : r.allbuses)
		{
			os << "Bus " << bus << ": ";
			bool first = true;
			for (const auto& stop : stops)
			{
				if (first)
				{
					os << stop;
					first = false;
				}
				else
				{
					os << " " << stop;
				}
			}

			if (i != r.allbuses.size() - 1)
			{
				os << std::endl;
			}
			++i;
		}
	}
	else
	{
		os << "No buses";
	}

	return os;
}