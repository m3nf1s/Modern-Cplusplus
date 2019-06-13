/*
В первом курсе «Белый пояс по С++» у нас была задача «Имена и фамилии — 1».
В ней надо было разработать класс Person, поддерживающий историю изменений человеком своих фамилии и имени.
В данной задаче вам надо разработать юнит-тесты на реализацию класса Person.
При разработке тестов учитывайте ограничения, которые накладывает на класс Person условие задачи «Имена и фамилии — 1».

Реализуйте класс для человека, поддерживающий историю изменений человеком своих фамилии и имени.
Считайте, что в каждый год может произойти не более одного изменения фамилии и не более одного изменения имени.
При этом с течением времени могут открываться всё новые факты из прошлого человека,
	поэтому года́ в последовательных вызовах методов ChangeLastName и ChangeFirstName не обязаны возрастать.

Гарантируется, что все имена и фамилии непусты.

Строка, возвращаемая методом GetFullName, должна содержать разделённые одним пробелом имя и фамилию человека
	по состоянию на конец данного года.

	* Если к данному году не случилось ни одного изменения фамилии и имени, верните строку "Incognito".
	* Если к данному году случилось изменение фамилии, но не было ни одного изменения имени, верните "last_name with unknown first name".
	* Если к данному году случилось изменение имени, но не было ни одного изменения фамилии, верните "first_name with unknown last name".
*/

#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <limits>

template <class T>
std::ostream& operator << (std::ostream& os, const std::vector<T>& s)
{
	os << "{";
	bool first = true;
	for (const auto& x : s) 
	{
		if (!first) 
		{
			os << ", ";
		}
		first = false;
		os << x;
	}
	return os << "}";
}

template <class T>
std::ostream& operator << (std::ostream& os, const std::set<T>& s) 
{
	os << "{";
	bool first = true;
	for (const auto& x : s) 
	{
		if (!first) 
		{
			os << ", ";
		}
		first = false;
		os << x;
	}
	return os << "}";
}

template <class K, class V>
std::ostream& operator << (std::ostream& os, const std::map<K, V>& m) 
{
	os << "{";
	bool first = true;
	for (const auto& kv : m) 
	{
		if (!first) 
		{
			os << ", ";
		}
		first = false;
		os << kv.first << ": " << kv.second;
	}
	return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const std::string& hint = {})
{
	if (t != u) 
	{
		std::ostringstream os;
		os << "Assertion failed: " << t << " != " << u;
		if (!hint.empty()) 
		{
			os << " hint: " << hint;
		}
		throw std::runtime_error(os.str());
	}
}

void Assert(bool b, const std::string& hint) 
{
	AssertEqual(b, true, hint);
}

class TestRunner 
{
public:
	template <class TestFunc>
	void RunTest(TestFunc func, const std::string& test_name) 
	{
		try 
		{
			func();
			std::cerr << test_name << " OK" << std::endl;
		}
		catch (std::exception& e) 
		{
			++fail_count;
			std::cerr << test_name << " fail: " << e.what() << std::endl;
		}
		catch (...) 
		{
			++fail_count;
			std::cerr << "Unknown exception caught" << std::endl;
		}
	}

	~TestRunner() 
	{
		if (fail_count > 0) 
		{
			std::cerr << fail_count << " unit tests failed. Terminate" << std::endl;
			exit(1);
		}
	}

private:
	int fail_count = 0;
};

class Person
{
public:
	// Вы можете вставлять сюда различные реализации класса,
	// чтобы проверить, что ваши тесты пропускают корректный код
	// и ловят некорректный
	void ChangeFirstName(int year, const std::string& first_name) 
	{
		_firstName[year] = first_name;
	}
	void ChangeLastName(int year, const std::string& last_name)
	{
		_lastName[year] = last_name;
	}
	std::string GetFullName(int year) 
	{
		int min_first_name = FindMinYear(year, _firstName);
		int min_last_name = FindMinYear(year, _lastName);
		
		return ReturnFullName(min_first_name, _firstName, min_last_name, _lastName);
	}
private:
	std::map<int, std::string> _firstName;
	std::map<int, std::string> _lastName;

	int FindMinYear(const int year, std::map<int, std::string>& list)
	{
		int min = std::numeric_limits<int>::min();

		for (const auto& [yr, name] : list)
		{
			if (yr <= year)
			{
				min = yr;
			}
		}

		return min;
	}

	std::string ReturnFullName(int fn_year, std::map<int, std::string> fn, int ln_year, std::map<int, std::string> ln)
	{
		if (fn.count(fn_year) == 1 && ln.count(ln_year) == 1)
		{
			return fn.at(fn_year) + " " + ln.at(ln_year);
		}
		
		if (fn.count(fn_year) == 1 && ln.count(ln_year) != 1)
		{
			return fn.at(fn_year) + " with unknown last name";
		}

		if (fn.count(fn_year) != 1 && ln.count(ln_year) == 1)
		{
			return ln.at(ln_year) + " with unknown first name";
		}

		return "Incognito";
	}
};

void TestIncognito()
{
	{
		Person person;
		AssertEqual(person.GetFullName(1800), "Incognito", "Incognito Test 1");
	}

	{
		Person person;
		person.ChangeFirstName(1700, "Ekaterina");
		AssertEqual(person.GetFullName(1600), "Incognito", "Incognito Test 2");
	}

	{
		Person person;
		person.ChangeLastName(1800, "Dronova");
		AssertEqual(person.GetFullName(1780), "Incognito", "Incognito Test 3");
	}
}

void TestUnknowLastName()
{
	{
		Person person;
		person.ChangeFirstName(1400, "Valentin");
		AssertEqual(person.GetFullName(1500), "Valentin with unknown last name", "UnknowLastName Test 1");
	}

	{
		Person person;
		person.ChangeFirstName(1450, "Valentin");
		person.ChangeFirstName(1500, "Egor");
		person.ChangeLastName(1480, "Ivanov");
		AssertEqual(person.GetFullName(1475), "Valentin with unknown last name", "UnknowLastName Test 2");
	}
}

void TestUnknowFirstName()
{
	{
		Person person;
		person.ChangeLastName(2000, "Petrov");
		AssertEqual(person.GetFullName(2001), "Petrov with unknown first name", "UnknowFirstName Test 1");
	}

	{
		Person person;
		person.ChangeLastName(2007, "Sidorov");
		person.ChangeLastName(2009, "Vakin");
		person.ChangeFirstName(2009, "Ivanov");
		AssertEqual(person.GetFullName(2007), "Sidorov with unknown first name", "UnknowFirstName Test 2");
	}
}

void TestGetFullName()
{
	{
		Person person;
		person.ChangeFirstName(2001, "Igor");
		person.ChangeLastName(2002, "Lyahov");
		AssertEqual(person.GetFullName(2002), "Igor Lyahov", "FuulName Test 1");
	}

	{
		Person person;
		person.ChangeFirstName(2001, "Igor");
		person.ChangeLastName(2002, "Lyahov");
		person.ChangeFirstName(2002, "Sergey");
		AssertEqual(person.GetFullName(2002), "Sergey Lyahov", "FuulName Test 1");
	}
}

int main() 
{
	TestRunner runner;
	runner.RunTest(TestIncognito, "Incognito");
	runner.RunTest(TestUnknowFirstName, "Unknow First Name");
	runner.RunTest(TestUnknowLastName, "Unknow Last Name");
	runner.RunTest(TestGetFullName, "Get Full Name");

	return 0;
}