/*
	Условие
	Разработайте систему бронирования отелей, позволяющую бронировать номера клиентами и контролировать спрос владельцами отелей.
	Ваша программа должна обрабатывать следующие события:
	*	BOOK time hotel_name client_id room_count — забронировать клиентом client_id room_count номеров
			в отеле hotel_name в момент времени time.
		Время измеряется в секундах, отсчитываемых от некоторого момента.
	*	CLIENTS hotel_name — вывести количество различных клиентов, бронировавших номера в отеле hotel_name за последние сутки.
		Более формально интересующий диапазон времени описывается следующим образом:
			пусть current_time — время последнего события BOOK,
			тогда в данном запросе нужно учесть все события с current_time − 86400 < time ⩽ current_time,
			где 86400 — количество секунд в сутках.
		Обратите внимание, что последнее бронирование должно учитываться,
			а бронирование, случившееся ровно за сутки до него, учитываться не должно.
	*	ROOMS hotel_name — вывести количество номеров, забронированных за последние сутки в отеле hotel_name.

	Формат входных данных
	В первой строке вводится количество запросов Q — натуральное число, не превосходящее 10^5.
	В следующих Q строках в соответствии с описанным выше форматом вводятся запросы.
	Гарантируется, что:
	*	time — целое число в диапазоне от −10^18 до 10^18 и не убывает от события к событию.
	*	hotel_name — строка из латинских букв и цифр, имеющая длину не более 12 символов.
	*	client_id — натуральное число, не превосходящее 10^9.
	*	room_count — целое положительное число, не превосходящее 1000.

	Формат выходных данных
	Для каждого запроса CLIENTS и ROOMS выведите единственное целое число — ответ на запрос.
	Если указанный в запросе отель пока не имеет ни одного бронирования, выведите 0.

	Ограничения
	1 секунда на выполнение всех запросов.
	Все описанные в условии гарантии действительно справедливы для всех тестов, на которых будет запускаться ваша программа.
	Проверять корректность тестов не нужно.
*/

#include <iostream>
#include <map>
#include <queue>

class BookingManager
{
public:
	BookingManager() = default;

	void Book(const int64_t time, const std::string& hotel_name, const int client_id, const int room_count)
	{
		events.push({ time, hotel_name, client_id, room_count });

		client_system_[hotel_name][client_id] += room_count;
		room_system_[hotel_name] += room_count;

		UpdateEvents(time);
	}

	size_t Clients(const std::string& hotel_name)
	{
		return client_system_[hotel_name].size();
	}

	int Rooms(const std::string& hotel_name)
	{
		return room_system_[hotel_name];
	}
private:
	static constexpr int DAY_SECONDS_ = 86'400;

	std::map<std::string, std::map<int,int>> client_system_;
	std::map<std::string, int> room_system_;

	struct Event
	{
		int64_t time;
		std::string hotel_name;
		int client_id;
		int room_count;
	};
	std::queue<Event> events;

	void UpdateEvents(const int64_t current_time)
	{
		while (!events.empty() && events.front().time + DAY_SECONDS_ <= current_time)
		{
			auto ev = events.front();
			client_system_[ev.hotel_name][ev.client_id] -= ev.room_count;
			if (client_system_[ev.hotel_name][ev.client_id] == 0)
			{
				client_system_[ev.hotel_name].erase(ev.client_id);
			}
			
			room_system_[ev.hotel_name] -= ev.room_count;

			events.pop();
		}
	}
};

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	
	BookingManager bk;

	int query_count;
	std::cin >> query_count;

	for (int query_id = 0; query_id < query_count; ++ query_id)
	{
		std::string query_type;
		std::cin >> query_type;

		if (query_type == "BOOK")
		{
			int64_t time;
			std::string hotel_name;
			int client_id, room_count;
			std::cin >> time >> hotel_name >> client_id >> room_count;

			bk.Book(time, hotel_name, client_id, room_count);
		}
		else if (query_type == "CLIENTS")
		{
			std::string hotel_name;
			std::cin >> hotel_name;

			std::cout << bk.Clients(hotel_name) << '\n';
		}
		else if (query_type == "ROOMS")
		{
			std::string hotel_name;
			std::cin >> hotel_name;

			std::cout << bk.Rooms(hotel_name) << '\n';
		}
	}
	return 0;
}