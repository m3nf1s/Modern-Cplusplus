/*
    Часто от хранилища данных требуется быстрый поиск по любому полю.
    Для этого конструируются вспомогательные структуры данных, ускоряющие поиск,
    они называются вторичными индексами (secondary index).
    Реализуйте такое хранилище для данных типа Record.
   
    Требования:    
    *   Операция Put должна возвращать true, если вставка удалась, и false,
        если вставка не удалась, потому что в базе данных уже есть запись с таким же id.
        В последнем случае состояние базы данных не должно меняться.
    *   Операция GetById должна возвращать nullptr, если в базе данных нет записи с указанным id.
    *   Операция Erase должна возвращать true, если удалось удалить элемент с заданным id, и false,
        если элемент с заданным id не был найден.
        В последнем случае состояние базы данных не должно меняться.
    *   Подразумевается, что callback должен возвращать true,
        если требуется продолжить обход найденных записей, и false в противном случае.
        Например, это позволит вывести первые 10 записей или найти первую запись, удовлетворяющую дополнительному критерию.
    *   Время выполнения всех операций должно иметь в среднем сублинейную (например, константную или логарифмическую)
        зависимость от общего числа записей в базе данных.
    *   Все границы интервалов - включительные, [low, high] — это наиболее универсальный интервальный запрос,
        подумайте, как с помощью него выразить условия вида x < high, x > low, x = x_0.
    *   При решении этой задачи вы можете считать, что bad_alloc кидаться не будет.
*/

#include "test_runner.h"

#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <tuple>
#include <vector>
#include <memory>

struct Record
{
    std::string id;
    std::string title;
    std::string user;
    int timestamp;
    int karma;
};

// Реализуйте этот класс
class Database 
{
public:
    bool Put(const Record& record)
    {
        Data position {std::make_shared<Record>(record), {}, {}, {} };
        const auto [it, isSuccess] = data.emplace( record.id, std::move(position) );
        if (!isSuccess)
        {
            return false;
        }

        it->second.user_iterator = users.emplace( record.user, it->second.record );
        it->second.timestamp_iterator = timestamps.emplace( record.timestamp, it->second.record);
        it->second.karma_iterator = karma.emplace( record.karma, it->second.record);

        return true;
    }

    const Record* GetById(const std::string& id) const
    {
        auto pos_it = data.find(id);
        if (pos_it == data.end())
        {
            return nullptr;
        }
        
        return pos_it->second.record.get();
    }

    bool Erase(const std::string& id)
    {
        auto pos_it = data.find(id);

        if (pos_it == data.end())
        {
            return false;
        }

        users.erase(pos_it->second.user_iterator);
        timestamps.erase(pos_it->second.timestamp_iterator);
        karma.erase(pos_it->second.karma_iterator);

        data.erase(id);

        return true;
    }

    template <typename Callback>
    void RangeByTimestamp(int low, int high, Callback callback) const
    {
        auto it_begin = timestamps.lower_bound(low);
        auto it_end = timestamps.upper_bound(high);

        for (auto& it = it_begin; it != it_end; ++it)
        {
            if (!callback(*it->second))
            {
                break;
            }
        }
    }

    template <typename Callback>
    void RangeByKarma(int low, int high, Callback callback) const
    {
        
        auto it_begin = karma.lower_bound(low);
        auto it_end = karma.upper_bound(high);

        for (auto& it = it_begin; it != it_end; ++it)
        {
            if (!callback(*it->second))
            {
                break;
            }
        }
    }

    template <typename Callback>
    void AllByUser(const std::string& user, Callback callback) const
    {
        auto [begin, end] = users.equal_range(user);

        for (auto& it = begin; begin != end; ++it)
        {
            if (!callback(*it->second))
            {
                break;
            }
        }
    }

private:
    using Id = std::string;
    using User = std::string;
    using Timestamp = int;
    using Karma = int;


    struct Data
    {
        const std::shared_ptr<Record> record;
        std::multimap<User, std::shared_ptr<Record>>::iterator user_iterator;
        std::multimap<Timestamp, std::shared_ptr<Record>>::iterator timestamp_iterator;
        std::multimap<Karma, std::shared_ptr<Record>>::iterator karma_iterator;
    };

    std::unordered_map<Id, Data> data;

    std::multimap<User, std::shared_ptr<Record>> users;
    std::multimap<Timestamp, std::shared_ptr<Record>> timestamps;
    std::multimap<Karma, std::shared_ptr<Record>> karma;
};


void TestRangeBoundaries() 
{
    const int good_karma = 1000;
    const int bad_karma = -10;

    Database db;
    db.Put({ "id1", "Hello there", "master", 1536107260, good_karma });
    db.Put({ "id2", "O>>-<", "general2", 1536107260, bad_karma });

    int count = 0;
    db.RangeByKarma(bad_karma, good_karma, [&count](const Record&) 
        {
            ++count;
            return true;
        });

    ASSERT_EQUAL(2, count);
}

void TestSameUser() 
{
    Database db;
    db.Put({ "id1", "Don't sell", "master", 1536107260, 1000 });
    db.Put({ "id2", "Rethink life", "master", 1536107260, 2000 });

    int count = 0;
    db.AllByUser("master", [&count](const Record&)
        {
            ++count;
            return true;
        });

    ASSERT_EQUAL(2, count);
}

void TestReplacement()
{
    const std::string final_body = "Feeling sad";

    Database db;
    db.Put({ "id", "Have a hand", "not-master", 1536107260, 10 });
    db.Erase("id");
    db.Put({ "id", final_body, "not-master", 1536107260, -10 });

    auto record = db.GetById("id");
    ASSERT(record != nullptr);
    ASSERT_EQUAL(final_body, record->title);
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestRangeBoundaries);
    RUN_TEST(tr, TestSameUser);
    RUN_TEST(tr, TestReplacement);
    return 0;
}
