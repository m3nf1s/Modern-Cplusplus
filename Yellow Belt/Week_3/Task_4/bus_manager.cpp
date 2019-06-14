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

//ѕолучить информацию об автобусах, которые проход€т через данную остановку
//stop - остановка
BusesForStopResponse BusManager::GetBusesForStop(const std::string& stop) const
{
	BusesForStopResponse list;
	if (list_stops_buses.count(stop) == 1)
		list.busesforstop = list_stops_buses.at(stop);

	return list;
}

//ѕолучить информацию о всех остановках маршрута автобуса
//bus - автобус
StopsForBusResponse BusManager::GetStopsForBus(const std::string& bus) const
{
	StopsForBusResponse list;
	//провер€ем наличие маршрута bus
	if (list_buses_stops.count(bus) == 1)
	{
		//получаем копию списка остановок в пор€дке создани€
		list.stops = list_buses_stops.at(bus);
		//перебираем каждую остановку, чтобы к словарю <остановка, маршруты>
		for (const auto& stop : list.stops)
		{
			//перебираем автобусные маршруты в словаре <остановка, маршруты> чтобы
			//получить список других автобусных маршрутов, которые проход€т через данную остановку
			for (const auto& b : list_stops_buses.at(stop))
			{
				//сравниваем маршрут с искомым, чтобы избежать добавлени€ самого себ€
				if (b != bus)
				{
					list.stops_buses[stop].push_back(b);
				}
			}
		}
	}

	return list;
}

//ѕолучить информацию о всех автобусах
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