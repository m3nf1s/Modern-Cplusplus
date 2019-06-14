#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <map>

//Хранит информацию об автобусных остановках, которые проходят через определенную остановку
struct BusesForStopResponse
{
	std::vector<std::string> busesforstop;
};

std::ostream& operator<< (std::ostream& os, const BusesForStopResponse& r);

//Хранит информацию об автобусном маршруте и какие автобусы проходят через определенную остановку
// stops - остановки в созданном порядке
// stops_buses - остановки с номерами автобусов
struct StopsForBusResponse
{
	std::vector<std::string> stops;
	std::map<std::string, std::vector<std::string>> stops_buses;
};

std::ostream& operator<< (std::ostream& os, const StopsForBusResponse& r);

//Хранит всю информацию о всех автобусных маршрутах
struct AllBusesResponse
{
	std::map<std::string, std::vector<std::string>> allbuses;
};

std::ostream& operator<< (std::ostream& os, const AllBusesResponse& r);