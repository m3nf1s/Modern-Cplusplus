/*
Введение
В курсе «Белый пояс по С++» финальным заданием была разработка базы данных, которая работала с парами (дата, событие).
В этой задаче вам нужно развить эту базу данных, научив её выбирать и удалять события,
	удовлетворяющие заданному условию, а также разделив её код на несколько файлов.

Более подробно, ваша программа должна уметь обрабатывать набор команд:
	1) Add date event — добавить в базу данных пару (date, event);
	2) Print — вывести всё содержимое базы данных;
	3) Find condition — вывести все записи, содержащиеся в базе данных, которые удовлетворяют условию condition;
	4) Del condition — удалить из базы все записи, которые удовлетворяют условию condition;
	5) Last date — вывести запись с последним событием, случившимся не позже данной даты.

Условия в командах Find и Del накладывают определённые ограничения на даты и события, например:
	1) Find date < 2017-11-06 — найти все события, которые случились раньше 6 ноября 2017 года;
	2) Del event != "holiday" — удалить из базы все события, кроме «holiday»;
	3) Find date >= 2017-01-01 AND date < 2017-07-01 AND event == "sport event" —
		найти всё события «sport event», случившиеся в первой половине 2017 года;
	4) Del date < 2017-01-01 AND (event == "holiday" OR event == "sport event") —
		удалить из базы все события «holiday» и «sport event», случившиеся до 2017 года.

В командах обоих типов условия могут быть пустыми: под такое условие попадают все события.

Структура программы
Ниже вам даны заготовки для файлов

	1) condition_parser.h/cpp — в видеолекции «Задача разбора арифметического выражения.
	Описание решения» мы продемонстрировали построение абстрактного синтаксического дерева для арифметических выражений.
	Реализация этого алгоритма для разбора условий в командах Find и Del содержится в функции ParseCondition,
		объявленной и полностью реализованной в файлах condition_parser.h/cpp;
	2) token.h/cpp — содержат готовый токенизатор, который используется в функции ParseCondition;
	3) main.cpp — содержит готовую функцию main.

Вам нужно проанализировать выданный код и разработать недостающие классы и функции:
	1) класс Database, который представляет собой базу данных, — вы должны сами создать его публичный интерфейс,
		основываясь на том, как он используется в функции main;
	2) классы Node, EmptyNode, DateComparisonNode, EventComparisonNode и LogicalOperationNode —
		сформировать их иерархию и публичный интерфейс вам поможет анализ функций main и ParseCondition;
	3) класс Date, а также функцию ParseDate и оператор вывода в поток для класса Date.

На проверку вы должны прислать архив, состоящий из файлов:
	1) date.h/cpp — эти файлы должны содержать объявления и определения класса Date,
		функции ParseDate и оператора вывода в поток для класса Date;
	2) database.h/cpp — эти файлы должны содержать объявление и определение класса Database;
	3) node.h/cpp — эти файлы должны содержать объявления и определения класса Node,
		а также всех его потомков (см. выше), которые представляют собой узлы абстрактного синтаксического дерева,
		формируемого функцией ParseCondition;
	4) condition_parser.h/cpp;
	5) token.h/cpp;
	6) main.cpp;
	7) другие .h- и .cpp-файлы, которые вы посчитаете нужным создать в своём решении.

Формат ввода и вывода
	В стандартном вводе содержатся команды для работы с базой данных, по одной команде в строке.
	Ваша программа должна считать их и вывести результаты обработки в стандартный вывод.
	Правила обработки команд приведены ниже.

Команда Add
Встретив команду Add date event, ваша программа должна добавить пару (date, event) в базу данных
	и затем показывать её при поиске (команда Find) или печати (команда Print).
Одинаковые события, произошедшие в один и тот же день, сохранять не нужно:
	добавление в базу уже существующей пары (date, event) должно игнорироваться.
В одну и ту же дату может произойти много разных событий, БД должна суметь их все сохранить.

Гарантируется, что поле date в команде Add имеет формат «Год-Месяц-День», где Год — это целое число от 0 до 9999,
	Месяц — это номер месяца от 1 до 12 включительно, День — это номер дня от 1 до 31 включительно.
После даты обязательно следует пробел, отделяющий её от события. Примеры корректных дат: 2017-11-07, 0-2-31.

Вся остальная часть строки в команде Add задаёт событие.
Оно может содержать пробелы, поэтому для его считывания удобно воспользоваться функцией getline.
При этом гарантируется, что название события не может содержать символ кавычки (").
Таким образом, этот символ может встретиться лишь в условии в командах Find и Del, являясь ограничителем названия события.

Пример
Для команды Add 2017-11-07 big sport event программа должна добавить в базу данных пару (2017-11-07, big sport event).

Команда Del
Встретив команду Del condition, ваша программа должна удалить из базы данных все события, удовлетворяющие условию condition,
	и вывести в стандартный вывод количество удалённых записей N в формате «Removed N entries».
Если условие пусто, результатом выполнения команды должна стать очистка всей базы данных.

Команда Print
Встретив команду Print, ваша программа должна вывести все пары (дата, событие), которые в данный момент содержатся в базе данных.
Пары надо выводить по одной в строке. Они должны быть отсортированы по дате по возрастанию.
События в рамках одной даты необходимо выводить в порядке добавления (за исключением уже удалённых и попыток добавления повторов).

Даты надо выводить в формате ГГГГ-ММ-ДД, где Г, М, Д — это цифры чисел года, месяца и дня соответственно.
Если какое-то число имеет меньше разрядов, чем нужно, его надо дополнить нулями, например: 0001-01-01 — первое января первого года.

Команда Find
Встретив команду Find condition, ваша программа должна вывести все пары (дата, событие),
	которые в данный момент содержатся в базе данных и удовлетворяют условию condition.
Формат вывода аналогичен команде Print. Поиск с пустым условием эквивалентен команде Print.
В конце команда должна вывести строку Found N entries, где N— количество найденных пар.

Команда Last
По команде Last date нужно вывести последнее из событий, случившихся к дате date. Более формально:
	1) среди всех имеющихся дат событий нужно найти наибольшую, не превосходящую date;
	2) из всех событий с такой датой нужно выбрать последнее добавленное и вывести в формате, аналогичном формату команды Print;
	3) если date меньше всех имеющихся дат, необходимо вывести «No entries».
*/
#include "database.h"
#include "date.h"
#include "condition_parser.h"
#include "node.h"
#include "test_runner.h"

#include <iostream>
#include <stdexcept>
#include <sstream>

using namespace std;

//парсит дату (год-месяц-день)
//и возвращается готовый класс Date
Date ParseDate(istream& is)
{
	int year, month, day;
	is >> year;
	is.ignore(1);
	is >> month;
	is.ignore(1);
	is >> day;

	return Date{ year,month,day };
}

//парсит новое событие
string ParseEvent(istream& is)
{
	string new_event;
	getline(is, new_event);

	return new_event;
}

void TestAll();

int main()
{
	//запускаем тесты
	TestAll();
	//создаем Базу данных
	Database db;
	//считывает строку в line
	for (string line; getline(cin, line); )
	{
		//помещаем line в поток ss
		istringstream is(line);
		//вводим команду
		string command;
		is >> command;
		//если команда ADD
		if (command == "Add")
		{
			//парсим дату
			const auto date = ParseDate(is);
			//парсим события
			const auto event = ParseEvent(is);
			//помещаем в базу данных
			db.Add(date, event);
		}
		//если команда Print
		else if (command == "Print")
		{
			//печатаем базу использую поток cout
			db.Print(cout);
		}
		//если удалить
		else if (command == "Del")
		{
			//пример: Del event != "holiday"
			//Del date < 2017-01-01 AND (event == "holiday" OR event == "sport event")
			auto condition = ParseCondition(is);
			//
			auto predicate = [condition](const Date& date, const string& event)
			{
				return condition->Evaluate(date, event);
			};
			int count = db.RemoveIf(predicate);
			cout << "Removed " << count << " entries" << endl;
		}
		else if (command == "Find")
		{
			auto condition = ParseCondition(is);
			auto predicate = [condition](const Date& date, const string& event)
			{
				return condition->Evaluate(date, event);
			};

			const auto entries = db.FindIf(predicate);
			for (const auto& entry : entries)
			{
				cout << entry << endl;
			}
			cout << "Found " << entries.size() << " entries" << endl;
		}
		else if (command == "Last")
		{
			try
			{
				cout << db.Last(ParseDate(is)) << endl;
			}
			catch (invalid_argument&)
			{
				cout << "No entries" << endl;
			}
		}
		else if (command.empty())
		{
			continue;
		}
		else
		{
			throw logic_error("Unknown command: " + command);
		}
	}

	return 0;
}

void TestParseEvent() {
	{
		istringstream is("event");
		AssertEqual(ParseEvent(is), "event", "Parse event without leading spaces");
	}
	{
		istringstream is("   sport event ");
		AssertEqual(ParseEvent(is), "sport event ", "Parse event with leading spaces");
	}
	{
		istringstream is("  first event  \n  second event");
		vector<string> events;
		events.push_back(ParseEvent(is));
		events.push_back(ParseEvent(is));
		AssertEqual(events, vector<string>{"first event  ", "second event"}, "Parse multiple events");
	}
}

void TestAll() {
	TestRunner tr;
	tr.RunTest(TestParseEvent, "TestParseEvent");
	tr.RunTest(TestParseCondition, "TestParseCondition");
}