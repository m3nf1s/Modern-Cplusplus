/*
	Как известно, отсутствие синхронизации доступа нескольких потоков к одним и тем же данным
	может фатально сказаться на работе программы.
	Поэтому очень важно не забывать захватывать мьютекс при обращении к разделяемым данным.
	Но если у нас есть большой проект, в котором доступ к общим данным осуществляется
	из большого количества мест в коде, то не так уж и трудно забыть сделать это, внося очередные правки.
	
	Чтобы защититься от такой забывчивости, можно написать специальную обёртку над данными,
	которая будет предоставлять к ним доступ только под мьютексом.
	В этой задаче вам надо разработать такую обёртку — шаблон класса Synchronized.

	Типы Access1 и Access2 должны быть структурами, в которых есть поля T& ref_to_value и const T& ref_to_valueсоответственно.
	В обоих случаях поле ref_to_value должно ссылаться на поле value класса Synchronized<T>.
	Кроме того, объекты классов Access1 и Access2 должны вести себя аналогично классу lock_guard<mutex>:
	захватывать мьютекс в своём конструкторе и освобождать в деструкторе.

	Вам можно (и даже нужно) добавлять необходимые поля в классы Access1, Access2 и шаблон Synchronized.
	Более подробные примеры использования шаблона Synchronized смотрите в заготовке решения.
	
	Как видите, единственный способ получить доступ к полю value класса Synchronized<T>
	— это обратиться к полю ref_to_value классов Access1 и Access2, которые гарантируют,
	что этот доступ осуществляется под мьютексом. 
	Таким образом, если разделяемые данные обернуть в шаблон Synchronized, 
	вы никогда не забудете захватить мьютекс при обращении к ним.
	
	Примечание
	Проверяющий код никак не закладывается на имена типов, возвращаемых методами GetAccess,
	поэтому вы можете назвать их не Access1 и Access2, а как-то более осмысленно.
*/
#include "test_runner.h"

#include <numeric>
#include <vector>
#include <string>
#include <future>
#include <mutex>
#include <queue>
using namespace std;

template <typename T>
class Synchronized
{
private:
	template <typename U>
	struct Access
	{
		std::lock_guard<std::mutex> guard;
		U& ref_to_value;
	};

public:
	explicit Synchronized(T initial = T())
		: value(std::move(initial))
	{
	}

	Access<T> GetAccess()
	{
		return { std::lock_guard(m), value };
	}

	Access<const T> GetAccess() const
	{
		return { std::lock_guard(m), value };
	}

private:
	T value;
	mutable std::mutex m;
};

void TestConcurrentUpdate()
{
	Synchronized<string> common_string;

	const size_t add_count = 50000;
	auto updater = [&common_string, add_count]
	{
		for (size_t i = 0; i < add_count; ++i)
		{
			auto access = common_string.GetAccess();
			access.ref_to_value += 'a';
		}
	};

	auto f1 = async(updater);
	auto f2 = async(updater);

	f1.get();
	f2.get();

	ASSERT_EQUAL(common_string.GetAccess().ref_to_value.size(), 2 * add_count);
}

vector<int> Consume(Synchronized<deque<int>>& common_queue)
{
	vector<int> got;

	for (;;)
	{
		deque<int> q;

		{
			// Мы специально заключили эти две строчки в операторные скобки, чтобы
			// уменьшить размер критической секции. Поток-потребитель захватывает
			// мьютекс, перемещает всё содержимое общей очереди в свою
			// локальную переменную и отпускает мьютекс. После этого он обрабатывает
			// объекты в очереди за пределами критической секции, позволяя
			// потоку-производителю параллельно помещать в очередь новые объекты.
			//
			// Размер критической секции существенно влияет на быстродействие
			// многопоточных программ.
			auto access = common_queue.GetAccess();
			q = move(access.ref_to_value);
		}

		for (int item : q)
		{
			if (item > 0)
			{
				got.push_back(item);
			}
			else
			{
				return got;
			}
		}
	}
}

void Log(const Synchronized<deque<int>>& common_queue, ostream& out)
{
	for (int i = 0; i < 100; ++i)
	{
		out << "Queue size is " << common_queue.GetAccess().ref_to_value.size() << '\n';
	}
}

void TestProducerConsumer()
{
	Synchronized<deque<int>> common_queue;
	ostringstream log;

	auto consumer = async(Consume, ref(common_queue));
	auto logger = async(Log, cref(common_queue), ref(log));

	const size_t item_count = 100000;
	for (size_t i = 1; i <= item_count; ++i)
	{
		common_queue.GetAccess().ref_to_value.push_back(i);
	}
	common_queue.GetAccess().ref_to_value.push_back(-1);

	vector<int> expected(item_count);
	iota(begin(expected), end(expected), 1);
	ASSERT_EQUAL(consumer.get(), expected);

	logger.get();
	const string logs = log.str();
	ASSERT(!logs.empty());
}

int main()
{
	TestRunner tr;
	RUN_TEST(tr, TestConcurrentUpdate);
	RUN_TEST(tr, TestProducerConsumer);
}
