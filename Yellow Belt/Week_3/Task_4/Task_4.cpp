/*
В задаче «Декомпозиция программы» мы разбили монолитный код на набор функций и классов.
Теперь мы сделаем ещё один шаг и разделим нашу программу на несколько файлов.
В этой задаче вам нужно создать проект, состоящий из следующих файлов:
	1.query.h, в него кладём:
		enum class QueryType
		struct Query
		объявление istream& operator >> (istream& is, Query& q)
	2. query.cpp, в него кладём
		определение istream& operator >> (istream& is, Query& q);
	3. responses.h:
		struct BusesForStopResponse
		ostream& operator << (ostream& os, const BusesForStopResponse& r)
		struct StopsForBusResponse
		ostream& operator << (ostream& os, const StopsForBusResponse& r)
		struct AllBusesResponse
		ostream& operator << (ostream& os, const AllBusesResponse& r)
	4. responses.cpp: определения всего, что объявлено в responses.h
	5. bus_manager.h: объявление класса BusManager
	6. bus_manager.cpp: определения методов класса BusManager
	7. main.cpp: функция main
*/

#include <iostream>
#include "query.h"
#include "bus_manager.h"

int main()
{
	int query_count;
	Query q;

	std::cin >> query_count;

	BusManager bm;
	for (int i = 0; i < query_count; ++i) {
		std::cin >> q;
		switch (q.type)
		{
		case QueryType::NewBus:
			bm.AddBus(q.bus, q.stops);
			break;
		case QueryType::BusesForStop:
			std::cout << bm.GetBusesForStop(q.stop) << std::endl;
			break;
		case QueryType::StopsForBus:
			std::cout << bm.GetStopsForBus(q.bus) << std::endl;
			break;
		case QueryType::AllBuses:
			std::cout << bm.GetAllBuses() << std::endl;
			break;
		}
	}

	return 0;
}