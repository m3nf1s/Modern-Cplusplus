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
 
#include <iostream>
#include <map>
#include <vector>

int main()
{
    size_t command_count {};
    std::cin >> command_count;
    std::map<std::string, std::vector<std::string>> stop_to_buses, bus_to_stops;
    
    for(size_t i = 0; i < command_count; ++i)
    {
        std::string command;
        std::cin >> command;

        if(command == "NEW_BUS")
        {
            std::string bus;
            size_t stops_count {};
            std::cin >> bus >> stops_count;

            std::vector<std::string>& stops = bus_to_stops[bus];
            stops.resize(stops_count);
            
            for(auto& stop : stops)
            {
                std::cin >> stop;
                stop_to_buses[stop].push_back(bus);
            }
        }
        else if(command == "BUSES_FOR_STOP")
        {
            std::string stop;
            std::cin >> stop;

            if(stop_to_buses.count(stop))
            {
                bool is_first = true;
                for(const auto& bus : stop_to_buses[stop])
                {
                    if(is_first)
                    {
                        std::cout << bus;
                        is_first = false;
                    }
                    else
                    {
                        std::cout << ' ' << bus;
                    }
                }
                std::cout << std::endl;
            }
            else
            {
                std::cout << "No stop" << std::endl;
            }
        }
        else if(command == "STOPS_FOR_BUS")
        {
            std::string bus;
            std::cin >> bus;

            if(bus_to_stops.count(bus))
            {
                for(const auto& stop : bus_to_stops[bus])
                {
                    std::cout << "Stop " << stop << ':';
                    if(stop_to_buses[stop].size() != 1)
                    {                        
                        for(const auto& bus_ : stop_to_buses[stop])
                        {
                            if(bus_ != bus)
                            {
                                std::cout << ' ' << bus_;
                            }
                        }
                        std::cout << std::endl;
                    }
                    else
                    {
                        std::cout << " no interchange" << std::endl;
                    }
                }
            }
            else
            {
                std::cout << "No bus" << std::endl;
            }
        }
        else if(command == "ALL_BUSES")
        {
            if(!bus_to_stops.empty())
            {
                for(const auto& [bus, stops] : bus_to_stops)
                {
                    std::cout << "Bus " << bus << ':';
                    for(const auto& stop : stops)
                    {
                        std::cout << ' ' << stop;
                    }
                    std::cout << std::endl;
                }
            }
            else
            {
                std::cout << "No buses" << std::endl;
            }
        }
    }
}
