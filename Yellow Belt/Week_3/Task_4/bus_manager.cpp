#include "bus_manager.h"

void BusManager::AddBus(const std::string& bus, const std::vector<std::string>& stops)
{
	if (!bus.empty() && !stops.empty())
	{
		for (const std::string& stop : stops)
		{
			list_buses_stops[bus].push_back(stop);
			list_stops_buses[stop].push_back(bus);
		}
	}
}

//�������� ���������� �� ���������, ������� �������� ����� ������ ���������
//stop - ���������
BusesForStopResponse BusManager::GetBusesForStop(const std::string& stop) const
{
	BusesForStopResponse list;
	if (list_stops_buses.count(stop) == 1)
		list.busesforstop = list_stops_buses.at(stop);

	return list;
}

//�������� ���������� � ���� ���������� �������� ��������
//bus - �������
StopsForBusResponse BusManager::GetStopsForBus(const std::string& bus) const
{
	StopsForBusResponse list;
	//��������� ������� �������� bus
	if (list_buses_stops.count(bus) == 1)
	{
		//�������� ����� ������ ��������� � ������� ��������
		list.stops = list_buses_stops.at(bus);
		//���������� ������ ���������, ����� � ������� <���������, ��������>
		for (const auto& stop : list.stops)
		{
			//���������� ���������� �������� � ������� <���������, ��������> �����
			//�������� ������ ������ ���������� ���������, ������� �������� ����� ������ ���������
			for (const auto& b : list_stops_buses.at(stop))
			{
				//���������� ������� � �������, ����� �������� ���������� ������ ����
				if (b != bus)
				{
					list.stops_buses[stop].push_back(b);
				}
			}
		}
	}

	return list;
}

//�������� ���������� � ���� ���������
AllBusesResponse BusManager::GetAllBuses() const
{
	return AllBusesResponse{ list_buses_stops };
}

std::map<std::string, std::vector<std::string>> BusManager::GetBusesList()
{
	return list_buses_stops;
}

std::map<std::string, std::vector<std::string>> BusManager::GetStopsList()
{
	return list_stops_buses;
}