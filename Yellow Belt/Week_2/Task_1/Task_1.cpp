/*
В курсе «Белый пояс по С++» у нас была задача «Автобусные остановки — 1».
В этой задаче вам будет дано её правильное решение, целиком содержащееся внутри функции main.
Вам надо будет выполнить декомпозицию этого решения на заранее заданные блоки так,
	чтобы получившаяся программа так же корректно решала задачу.

Реализуйте систему хранения автобусных маршрутов.
Вам нужно обрабатывать следующие запросы:
	1) NEW_BUS bus stop_count stop1 stop2 ... — добавить маршрут автобуса с названием bus и stop_count остановками
		с названиями stop1, stop2, ...
	2) BUSES_FOR_STOP stop — вывести названия всех маршрутов автобуса, проходящих через остановку stop.
	3) STOPS_FOR_BUS bus — вывести названия всех остановок маршрута bus со списком автобусов,
		на которые можно пересесть на каждой из остановок.
	4) ALL_BUSES — вывести список всех маршрутов с остановками.

	Формат ввода
В первой строке ввода содержится количество запросов Q, затем в Q строках следуют описания запросов.
Гарантируется, что все названия маршрутов и остановок состоят лишь из латинских букв, цифр и знаков подчёркивания.
Для каждого запроса NEW_BUS bus stop_count stop1 stop2 ... гарантируется,
	что маршрут bus отсутствует, количество остановок больше 0,
	а после числа stop_count следует именно такое количество названий остановок,
	причём все названия в каждом списке различны.

Формат вывода
Для каждого запроса, кроме NEW_BUS, выведите соответствующий ответ на него:
	1) На запрос BUSES_FOR_STOP stop выведите через пробел список автобусов,
		проезжающих через эту остановку, в том порядке, в котором они создавались командами NEW_BUS.
		Если остановка stop не существует, выведите No stop.
	2) На запрос STOPS_FOR_BUS bus выведите описания остановок маршрута bus в отдельных строках в том порядке,
		в котором они были заданы в соответствующей команде NEW_BUS.
		Описание каждой остановки stop должно иметь вид Stop stop: bus1 bus2 ..., где bus1 bus2 ... — список автобусов,
		проезжающих через остановку stop, в порядке, в котором они создавались командами NEW_BUS, за исключением исходного маршрута bus.
		Если через остановку stop не проезжает ни один автобус, кроме bus, вместо списка автобусов для неё выведите no interchange.
		Если маршрут bus не существует, выведите No bus.
	3) На запрос ALL_BUSES выведите описания всех автобусов в алфавитном порядке.
		Описание каждого маршрута bus должно иметь вид Bus bus: stop1 stop2 ...,
		где stop1 stop2 ... — список остановок автобуса bus в порядке, в котором они были заданы в соответствующей команде NEW_BUS.
		Если автобусы отсутствуют, выведите No buses.
*/
#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>
#include <sstream>

using namespace std;

//Тип запроса
enum class QueryType
{
	NewBus,
	BusesForStop,
	StopsForBus,
	AllBuses
};

//Запрос
struct Query
{
	QueryType type;
	string bus;
	string stop;
	vector<string> stops;
};

istream& operator >> (istream& is, Query& q)
{
	
	
	return is;
}

//Хранит информацию об автобусных остановках, которые проходят через определенную остановку
struct BusesForStopResponse
{
	std::vector<std::string> busesforstop;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r)
{
	bool first = true;
	for (const auto& val : r.busesforstop)
	{
		if (first)
		{
			os << val;
			first = false;
		}

		os << ' ' << val;
	}

	return os;
}

//Хранит информацию об автобусном маршруте и какие автобусы проходят через определенную остановку
struct StopsForBusResponse
{
	std::map<std::string, std::vector<std::string>> stopsforbus;

};

ostream& operator << (ostream& os, const StopsForBusResponse& r)
{
	os << "Stop ";
	for (const auto& [stop, buses] : r.stopsforbus)
	{
		if(first)
	}

	return os;
}

//Хранит всю информацию о всех автобусных маршрутах
struct AllBusesResponse
{
	std::map < std::string, std::vector<std::string>> allbuses;
};

ostream& operator << (ostream& os, const AllBusesResponse& r)
{


	return os;
}

//
class BusManager {
public:
	//Добавить автобус с остановками
	//bus - автобус
	//stops - вектор остановок
	void AddBus(const string& bus, const vector<string>& stops)
	{
		for (const std::string& stop : stops)
		{
			list_buses_stops[bus].push_back(stop);
			list_stops_buses[stop].push_back(bus);
		}
	}

	//Получить информацию об автобусах, которые проходят через данную остановку
	//stop - остановка
	BusesForStopResponse GetBusesForStop(const string& stop) const
	{
		BusesForStopResponse list;
		if(list_stops_buses.count(stop) == 1)
			list.busesforstop = list_stops_buses.at(stop);

		return list;
	}

	//Получить информацию о всех остановках маршрута автобуса
	//bus - автобус
	StopsForBusResponse GetStopsForBus(const string& bus) const
	{
		StopsForBusResponse list;
		if(list_buses_stops.count(bus) == 1)
			list.stopsforbus = list_buses_stops.at(bus);

		return list;
	}

	//Получить информацию о всех автобусах
	AllBusesResponse GetAllBuses() const
	{
		AllBusesResponse list;

		list.allbuses = list_buses_stops;
	}
private:
	//хранит для каждого автобуса список остановок
	std::map<std::string, std::vector<std::string>> list_buses_stops;
	//хранит для каждой остановки список автобусов, которые проезжают через нее
	std::map<std::string, std::vector<std::string>> list_stops_buses;
};

// Не меняя тела функции main, реализуйте функции и классы выше

int main() {
	int query_count;
	Query q;

	cin >> query_count;

	BusManager bm;
	for (int i = 0; i < query_count; ++i) {
		cin >> q;
		switch (q.type)
		{
			case QueryType::NewBus:
				bm.AddBus(q.bus, q.stops);
				break;
			case QueryType::BusesForStop:
				cout << bm.GetBusesForStop(q.stop) << endl;
				break;
			case QueryType::StopsForBus:
				cout << bm.GetStopsForBus(q.bus) << endl;
				break;
			case QueryType::AllBuses:
				cout << bm.GetAllBuses() << endl;
				break;
		}
	}

	return 0;
}