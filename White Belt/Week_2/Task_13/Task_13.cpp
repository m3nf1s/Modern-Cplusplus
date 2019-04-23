// Task_13.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

/*
 * Реализуйте систему хранения автобусных маршрутов. Вам нужно обрабатывать следующие запросы:
 * 
 * NEW_BUS bus stop_count stop1 stop2 ... — добавить маршрут автобуса с названием bus и stop_count остановками с названиями stop1, stop2, ...
 * BUSES_FOR_STOP stop — вывести названия всех маршрутов автобуса, проходящих через остановку stop.
 * STOPS_FOR_BUS bus — вывести названия всех остановок маршрута bus со списком автобусов, на которые можно пересесть на каждой из остановок.
 * ALL_BUSES — вывести список всех маршрутов с остановками.
 * 
 * Формат ввода 
 * В первой строке ввода содержится количество запросов Q, затем в Q строках следуют описания запросов.
 * 
 * Гарантируется, что все названия маршрутов и остановок состоят лишь из латинских букв, цифр и знаков подчёркивания.
 * 
 * Для каждого запроса NEW_BUS bus stop_count stop1 stop2 ... гарантируется, что маршрут bus отсутствует, количество остановок больше 0,
 * а после числа stop_count следует именно такое количество названий остановок, причём все названия в каждом списке различны.
 * 
 * Формат вывода
 * 
 * Для каждого запроса, кроме NEW_BUS, выведите соответствующий ответ на него:
 * 
 * На запрос BUSES_FOR_STOP stop выведите через пробел список автобусов, проезжающих через эту остановку, в том порядке, в котором они создавались командами NEW_BUS.
 * Если остановка stop не существует, выведите No stop.
 * 
 * На запрос STOPS_FOR_BUS bus выведите описания остановок маршрута bus в отдельных строках в том порядке, в котором они были заданы в соответствующей команде NEW_BUS.
 * Описание каждой остановки stop должно иметь вид Stop stop: bus1 bus2 ..., где bus1 bus2 ... — список автобусов, проезжающих через остановку stop,
 * в порядке, в котором они создавались командами NEW_BUS, за исключением исходного маршрута bus.
 * Если через остановку stop не проезжает ни один автобус, кроме bus, вместо списка автобусов для неё выведите no interchange.
 * Если маршрут bus не существует, выведите No bus.
 * 
 * На запрос ALL_BUSES выведите описания всех автобусов в алфавитном порядке.
 * Описание каждого маршрута bus должно иметь вид Bus bus: stop1 stop2 ..., где stop1 stop2 ... — список остановок автобуса bus в порядке, в котором они были заданы в соответствующей команде NEW_BUS.
 * Если автобусы отсутствуют, выведите No buses.
 */
#include "pch.h"
#include <iostream>
#include <vector>
#include <map>
#include <string>

/// <summary>
/// Вывод vector на экран
/// </summary>
/// <param name="massive">Vector</param>
void PrintVector(const std::vector<std::string>& massive)
{
	for (const auto& value : massive)
	{
		std::cout << value << " ";
	}
	std::cout << std::endl;
}

int main()
{
	std::map <std::string, std::vector<std::string>> list_bus_stops, list_stop_buses;
	
	int command_count;
	std::cin >> command_count;

	for (int i = 0; i < command_count; i++)
	{
		std::string command;
		std::cin >> command;

		if(command == "NEW_BUS")
		{
			std::string bus;
			int stop_count;

			std::cin >> bus >> stop_count;
			for (int j = 0; j < stop_count; j++)
			{
				std::string stop;
				std::cin >> stop;
				list_bus_stops[bus].push_back(stop);

				list_stop_buses[stop].push_back(bus);
			}

			continue;
		}

		if (command == "BUSES_FOR_STOP")
		{
			std::string stop;
			std::vector<std::string> buses;

			std::cin >> stop;

			if (list_stop_buses.count(stop))
				buses = list_stop_buses[stop];

			if(!buses.empty())
			{
				PrintVector(buses);
			}
			else
			{
				std::cout << "No stop" << std::endl;
			}

			continue;
		}

		if (command == "STOPS_FOR_BUS")
		{
			std::string bus;
			std::cin >> bus;

			if(list_bus_stops.count(bus) != 0)
			{
				//список остановок
				std::vector<std::string> stops = list_bus_stops[bus];
				//перебираем список остановок
				for (const auto& stop : stops)
				{
					std::cout << "Stop " << stop << ": ";
					//перебираем словарь <остановка, номера автобусов>
					for (const auto& value : list_stop_buses)
					{
						//если остановка совпадает с остановкой из списка
						if(value.first == stop)
						{
							//перебираем список номеров автобусов
							for (const auto& vector_bus : value.second)
							{
								//если текущий номер автобуса не совпадает с номером автобуса из списка, то выводим его на экран
								if (vector_bus != bus)
									std::cout << vector_bus << " ";
								//иначе если текущий номер автобуса совпадает с номером автобуса из списка и список номеров автобусов содержит только данный номер, то выводим на экран сообщение
								else if (vector_bus == bus && value.second.size() == 1)
									std::cout << "no interchange";
							}
						}
					}
					std::cout << std::endl;
				}
			}
			else
			{
				std::cout << "No bus" << std::endl;
			}

			continue;
		}

		if(command == "ALL_BUSES")
		{
			if(!list_bus_stops.empty())
			{
				for (const auto& item : list_bus_stops)
				{
					std::cout << "Bus " << item.first << ": ";
					PrintVector(item.second);
				}
			}
			else
			{
				std::cout << "No buses" << std::endl;
			}
		}
	}
}