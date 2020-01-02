/*
    Мы уже не раз видели, что отсутствие синхронизации доступа нескольких потоков
    к одним и тем же данным может фатально сказаться на работе программы.
    Поэтому очень важно не забывать захватывать мьютекс при обращении к разделяемым данным.
    Но если у нас есть большой проект, в котором доступ к общим данным осуществляется из большого количества мест в коде,
    то не так уж и трудно забыть сделать это, внося очередные правки.
    
    Чтобы защититься от такой забывчивости, можно написать специальную обёртку над данными,
    которая будет предоставлять к ним доступ только под мьютексом.
    В этой задаче вам надо разработать такую обёртку — шаблон класса Synchronized.

    Тип Access должен быть структурой, в которой есть поле T& ref_to_value,
    ссылающееся на поле value класса Synchronized<T>.
    Кроме того объект класса Access должен вести себя аналогично классу lock_guard<mutex>:
    захватывать мьютекс в своём конструкторе и освобождать в деструкторе.

    Вам можно (и даже нужно) добавлять необходимые поля в класс Access и шаблон Synchronized.
    Более подробные примеры использования шаблона Synchronized смотрите в заготовке решения.
    
    Как видите, единственный способ получить доступ к полю value класса
    Synchronized<T> — это обратиться к полю ref_to_value класса Access,
    который гарантирует, что этот доступ осуществляется под мьютексом.
    Таким образом, если разделяемые данные обернуть в шаблон Synchronized,
    вы никогда не забудете захватить мьютекс при обращении к ним.
*/

#include "test_runner.h"

#include <numeric>
#include <vector>
#include <string>
#include <future>
#include <mutex>
#include <queue>
#include <thread>

// Реализуйте шаблон Synchronized<T>.
// Метод GetAccess должен возвращать структуру, в которой есть поле T& value.
template <typename T>
class Synchronized 
{
public:
    explicit Synchronized(T initial = T())
        : value(std::move(initial))
    {
    }

    struct Access 
    {
        std::lock_guard<std::mutex> guard;
        T& ref_to_value;
    };

    Access GetAccess()
    {
        return { std::lock_guard(mutex), value};
    }
private:
    std::mutex mutex;
    T value;
};

void TestConcurrentUpdate() 
{
    Synchronized<std::string> common_string;

    const size_t add_count = 50000;
    auto updater = [&common_string, add_count]
    {
        for (size_t i = 0; i < add_count; ++i)
        {
            auto access = common_string.GetAccess();
            access.ref_to_value += 'a';
        }
    };

    auto f1 = std::async(updater);
    auto f2 = std::async(updater);

    f1.get();
    f2.get();

    ASSERT_EQUAL(common_string.GetAccess().ref_to_value.size(), 2 * add_count);
}

std::vector<int> Consume(Synchronized<std::deque<int>>& common_queue)
{
    std::vector<int> got;

    for (;;) 
    {
        std::deque<int> q;

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

void TestProducerConsumer()
{
    Synchronized<std::deque<int>> common_queue;

    auto consumer = async(Consume, std::ref(common_queue));

    const size_t item_count = 100000;
    for (size_t i = 1; i <= item_count; ++i) 
    {
        common_queue.GetAccess().ref_to_value.push_back(i);
    }
    common_queue.GetAccess().ref_to_value.push_back(-1);

    std::vector<int> expected(item_count);
    std::iota(std::begin(expected), std::end(expected), 1);
    ASSERT_EQUAL(consumer.get(), expected);
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestConcurrentUpdate);
    RUN_TEST(tr, TestProducerConsumer);
}
