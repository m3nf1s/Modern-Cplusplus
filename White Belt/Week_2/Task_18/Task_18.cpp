// Task_18.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <set>
#include <string>
#include <map>

int main()
{
	std::map<std::set<std::string>, int> list_bus_stops;
	int command_count, number_route = 0;

	std::cin >> command_count;

	for (int i = 0; i < command_count; ++i)
	{
		int stops_count;
		std::set<std::string> stops;

		std::cin >> stops_count;

		for (int j = 0; j < stops_count; ++j)
		{
			std::string stop_name;
			std::cin >> stop_name;

			stops.insert(stop_name);
		}

		if(list_bus_stops.count(stops) == 1)
		{
			std::cout << "Already exists for " << list_bus_stops[stops] << std::endl;
		}
		else
		{
			list_bus_stops[stops] = ++number_route;
			std::cout << "New bus " << number_route << std::endl;
		}

		stops.clear();
	}
}

