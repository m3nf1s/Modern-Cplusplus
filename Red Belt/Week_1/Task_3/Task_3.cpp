/*
	Давайте представим, что вы разрабатываете инновационный сервис поиска авиабилетов AviaScanner.

	В данный момент вы работаете над функцией сортировки результатов поиска.
	Пользователь вводит свой запрос и получает список подходящих билетов.
	Дальше он может задавать параметры сортировки этого списка.
	Например, сначала по цене, затем по времени вылета и, наконец, по аэропорту прилёта.

	Напишите макрос SORT_BY, который принимает в качестве параметра имя поля структуры AirlineTicket.
	Вызов sort(begin(tixs), end(tixs), SORT_BY(some_field)) должен приводить к сортировке вектора tixs по полю some_field.

	Вам дан файл airline_ticket.h, содержащий объявления структур Time, Date и AirlineTicket,
		а также заготовка решения в виде cpp-файла sort_by.cpp.

	Пришлите на проверку cpp-файл, который
	* подключает заголовочный файл airline_ticket.h
	* содержит макрос SORT_BY
	* содержит определения операторов, необходимых для использования классов Date и
		Time в алгоритме сортировки и макросе ASSERT_EQUAL (формат вывода в поток можете выбрать произвольный) 
*/

#include "airline_ticket.h"
#include "test_runner.h"

#include <algorithm>
#include <numeric>

using namespace std;

#define SORT_BY(field)						\
	[](const AirlineTicket& lhs, const AirlineTicket& rhs)	\
	{							\
		return lhs.field < rhs.field;			\
	}															


void TestSortBy()
{
	vector<AirlineTicket> tixs =
	{
	  {"VKO", "AER", "Utair",     {2018, 2, 28}, {17, 40}, {2018, 2, 28}, {20,  0}, 1200},
	  {"AER", "VKO", "Utair",     {2018, 3,  5}, {14, 15}, {2018, 3,  5}, {16, 30}, 1700},
	  {"AER", "SVO", "Aeroflot",  {2018, 3,  5}, {18, 30}, {2018, 3,  5}, {20, 30}, 2300},
	  {"PMI", "DME", "Iberia",    {2018, 2,  8}, {23, 00}, {2018, 2,  9}, { 3, 30}, 9000},
	  {"CDG", "SVO", "AirFrance", {2018, 3,  1}, {13, 00}, {2018, 3,  1}, {17, 30}, 8000},
	};

	sort(begin(tixs), end(tixs), SORT_BY(price));
	ASSERT_EQUAL(tixs.front().price, 1200);
	ASSERT_EQUAL(tixs.back().price, 9000);

	sort(begin(tixs), end(tixs), SORT_BY(from));
	ASSERT_EQUAL(tixs.front().from, "AER");
	ASSERT_EQUAL(tixs.back().from, "VKO");

	sort(begin(tixs), end(tixs), SORT_BY(arrival_date));
	ASSERT_EQUAL(tixs.front().arrival_date, (Date{ 2018, 2, 9 }));
	ASSERT_EQUAL(tixs.back().arrival_date, (Date{ 2018, 3, 5 }));
}

int main()
{
	TestRunner tr;
	RUN_TEST(tr, TestSortBy);
}
