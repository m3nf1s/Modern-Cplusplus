#pragma once

#include "responses.h"

class BusManager {
public:
	//ƒобавить автобус с остановками
	//bus - автобус
	//stops - вектор остановок
	void AddBus(const std::string& bus, const std::vector<std::string>& stops);

	//ѕолучить информацию об автобусах, которые проход€т через данную остановку
	//stop - остановка
	BusesForStopResponse GetBusesForStop(const std::string& stop) const;

	//ѕолучить информацию о всех остановках маршрута автобуса
	//bus - автобус
	StopsForBusResponse GetStopsForBus(const std::string& bus) const;

	//ѕолучить информацию о всех автобусах
	AllBusesResponse GetAllBuses() const;

	std::map<std::string, std::vector<std::string>> GetBusesList();

	std::map<std::string, std::vector<std::string>> GetStopsList();

private:
	//хранит дл€ каждого автобуса список остановок
	std::map<std::string, std::vector<std::string>> list_buses_stops;
	//хранит дл€ каждой остановки список автобусов, которые проезжают через нее
	std::map<std::string, std::vector<std::string>> list_stops_buses;
};