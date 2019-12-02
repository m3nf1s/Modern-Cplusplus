/*
	Продолжим работу над сервисом поиска авиабилетов AviaScanner.
	Наш сервис хранит базу данных билетов в виде vector<AirlineTicket>,
		где AirlineTicket — такая же структура, как и в предыдущей задаче.
	Периодически наш сервис обходит сайты авиакомпаний, собирает свежую информацию о доступных билетах и обновляет записи в своей базе данных.
	Делается это с помощью функции void UpdateTicket(AirlineTicket& ticket, const map<string, string>& updates).
	Параметр updates содержит пары (имя поля; новое значение).
	При этом он содержит только те поля, которые поменялись.

	Напишите макрос UPDATE_FIELD.
	Вам дан файл airline_ticket.h, содержащий объявления структур Time, Date и AirlineTicket,
		а также заготовка решения в виде cpp-файла update_field.cpp.
	Пришлите на проверку cpp-файл, который
	* подключает заголовочный файл airline_ticket.h
	* содержит макрос UPDATE_FIELD
	* содержит определения операторов, необходимых для считывания классов Date и Time из потока istream
		и их использования в макросе ASSERT_EQUAL (формат ввода смотрите в юнит-тестах в файле update_field.cpp)
*/

#include "airline_ticket.h"
#include "test_runner.h"

using namespace std;

#define UPDATE_FIELD(ticket, field, values)		\
{							\
	auto it = values.find(#field);			\
	if (it != values.end())				\
	{						\
		std::istringstream is (it->second);	\
		is >> ticket.field;			\
	}						\
}

void TestUpdate()
{
	AirlineTicket t;
	t.price = 0;

	const map<string, string> updates1 =
	{
	  {"departure_date", "2018-2-28"},
	  {"departure_time", "17:40"},
	};
	UPDATE_FIELD(t, departure_date, updates1);
	UPDATE_FIELD(t, departure_time, updates1);
	UPDATE_FIELD(t, price, updates1);

	ASSERT_EQUAL(t.departure_date, (Date{ 2018, 2, 28 }));
	ASSERT_EQUAL(t.departure_time, (Time{ 17, 40 }));
	ASSERT_EQUAL(t.price, 0);

	const map<string, string> updates2 =
	{
	  {"price", "12550"},
	  {"arrival_time", "20:33"},
	};
	UPDATE_FIELD(t, departure_date, updates2);
	UPDATE_FIELD(t, departure_time, updates2);
	UPDATE_FIELD(t, arrival_time, updates2);
	UPDATE_FIELD(t, price, updates2);

	// updates2 не содержит ключей "departure_date" и "departure_time", поэтому
	// значения этих полей не должны измениться
	ASSERT_EQUAL(t.departure_date, (Date{ 2018, 2, 28 }));
	ASSERT_EQUAL(t.departure_time, (Time{ 17, 40 }));
	ASSERT_EQUAL(t.price, 12550);
	ASSERT_EQUAL(t.arrival_time, (Time{ 20, 33 }));
}

int main()
{
	TestRunner tr;
	RUN_TEST(tr, TestUpdate);
}