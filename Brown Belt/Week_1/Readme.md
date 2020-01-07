
# Эффективное использование ассоциативных контейнеров

## [Задание по программированию: Хеш-таблица](https://github.com/m3nf1s/Modern-Cplusplus/tree/master/Brown%20Belt/Week_1/Task_1)

Теперь, когда вы знаете, как unordered-контейнеры устроены внутри, вам предлагается самостоятельно реализовать упрощённую версию хеш-таблицы. Реализуйте шаблон HashSet:

```cpp
template <typename Type, typename Hasher>
class HashSet {
public:
  using BucketList = forward_list<Type>;

public:
  explicit HashSet(
      size_t num_buckets,
      const Hasher& hasher = {}
  );

  void Add(const Type& value);
  bool Has(const Type& value) const ;
  void Erase(const Type& value);
  const BucketList& GetBucket(const Type& value) const;
};
```

Требования:

* В любой момент времени в вашей хеш-таблице должно быть ровно num_buckets корзин. Рехеширование выполнять не нужно.
* Метод Add не должен менять содержимое таблицы, если элемент, равный данному, уже есть в таблице.
* Метод Has должен возвращать true тогда и только тогда, когда элемент, равный данному, есть в таблице.
* Метод Erase должен стирать элемент, равный данному, из таблицы, если он там есть, в противном случае он не должен менять содержимое таблицы.
* Метод GetBucket должен возвращать ссылку на бакет, который содержал бы данный элемент, вне зависимости от того, есть он в таблице или нет.

## [Задание по программированию: set::iterator++](https://github.com/m3nf1s/Modern-Cplusplus/tree/master/Brown%20Belt/Week_1/Task_2)

На лекциях вам было рассказано о внутреннем устройстве контейнеров map и set. Обычно map и set реализованы как двоичные деревья поиска.

Также вы узнали о том, как производится обход дерева с помощью итераторов.

В данной задаче мы будем работать не с контейнером set, но с аналогичным двоичным деревом поиска, состоящим из следующих вершин:
```cpp
struct Node {
  int value;
  Node* left;
  Node* right;
  Node* parent;
};
```

Где:
* value - значение, хранящееся в вершине;
* left и right - указатели на дочерние вершины (оба равны nullptr для листьев дерева);
* parent - указатель на родительскую вершину (равен nullptr для корня дерева).

Допустим, что для обхода дерева мы используем не специальный итератор, а просто указатель на вершину Node*.

Вам требуется реализовать функцию
```cpp
Node* Next(Node* node);
```
, возвращающую указатель на следующую по возрастанию значения вершину.

Функция должна вернуть nullptr в случае, если текущая вершина -- последняя в дереве.

## [Тренировочное задание по программированию: Интеграция структуры Point в unordered_set](https://github.com/m3nf1s/Modern-Cplusplus/tree/master/Brown%20Belt/Week_1/Task_3)

Мы хотим научиться встраивать структуру Point3D в контейнер unordered_set<Point3D, Hasher>. Для этого вам нужно реализовать структуру Hasher и оператор сравнения:
```cpp
using CoordType = int;

struct Point3D {
  CoordType x;
  CoordType y;
  CoordType z;

  bool operator==(const Point3D& other) const {
    // реализуйте оператор
  }
};

struct Hasher {
  // реализуйте структуру
};
```

В своей реализации используйте стандартную хеш-функцию std::hash<CoordType> для хеширования координат и комбинируйте полученные хеши с помощью полинома, как показано в лекции.

Требования:
* хеш-функция должна зависеть от всех координат точки
* хеш-функция должна равномерно рассеивать точки в трёхмерном пространстве; это её свойство проверяется тестом TestDistribution в заготовке решения.

## [Задание по программированию: Интеграция структуры Person в unordered_set](https://github.com/m3nf1s/Modern-Cplusplus/tree/master/Brown%20Belt/Week_1/Task_4)

Мы хотим научиться встраивать структуру Person в контейнер unordered_set<Person, PersonHasher>. Для этого вам нужно реализовать структуры PersonHasher, AddressHasher, и операторы сравнения:
```cpp
struct Address {
  string city, street;
  int building;

  bool operator==(const Address& other) const {
    // реализуйте оператор
  }
};

struct Person {
  string name;
  int height;
  double weight;
  Address address;

  bool operator==(const Person& other) const {
    // реализуйте оператор
  }
};

struct AddressHasher {
  // реализуйте структуру
};

struct PersonHasher {
  // реализуйте структуру
};
```

Для этого используйте стандартные хеш-функции std::hash и комбинируйте хеши полей с помощью полинома, как показано в лекции.

Требования:
* хеш-функции должны зависеть от всех полей структур
* хеш-функция должна равномерно рассеивать объекты типа Person; это её свойство проверяется тестом TestDistribution в заготовке решения.

## [Задание по программированию: Вторичный индекс в базе данных](https://github.com/m3nf1s/Modern-Cplusplus/tree/master/Brown%20Belt/Week_1/Task_5)

Часто от хранилища данных требуется быстрый поиск по любому полю. Для этого конструируются вспомогательные структуры данных, ускоряющие поиск, они называются вторичными индексами (secondary index). Реализуйте такое хранилище для данных типа Record ниже:
```cpp
struct Record {
  string id;
  string title;
  string user;
  int timestamp;
  int karma;
};

class Database {
public:
  bool Put(const Record& record);
  const Record* GetById(const string& id) const;
  bool Erase(const string& id);

  template <typename Callback>
  void RangeByTimestamp(int low, int high, Callback callback) const;

  template <typename Callback>
  void RangeByKarma(int low, int high, Callback callback) const;

  template <typename Callback>
  void AllByUser(const string& user, Callback callback) const;
};
```

Требования:
* Операция Put должна возвращать true, если вставка удалась, и false, если вставка не удалась, потому что в базе данных уже есть запись с таким же id. В последнем случае состояние базы данных не должно меняться.
* Операция GetById должна возвращать nullptr, если в базе данных нет записи с указанным id.
* Операция Erase должна возвращать true, если удалось удалить элемент с заданным id, и false, если элемент с заданным id не был найден. В последнем случае состояние базы данных не должно меняться.
* Подразумевается, что callback должен возвращать true, если требуется продолжить обход найденных записей, и false в противном случае. Например, это позволит вывести первые 10 записей или найти первую запись, удовлетворяющую дополнительному критерию.
* Время выполнения всех операций должно иметь в среднем сублинейную (например, константную или логарифмическую) зависимость от общего числа записей в базе данных.
* Все границы интервалов - включительные, [low, high] — это наиболее универсальный интервальный запрос, подумайте, как с помощью него выразить условия вида x < high, x > low, x = x_0.
* При решении этой задачи вы можете считать, что bad_alloc кидаться не будет.
