/*
Функция возвращает количество уникальных действительных корней уравнения ax² + bx + c = 0.
Разработайте набор юнит-тестов для проверки корректности реализации этой функции.
Случай, когда все три коэффициента равны нулю, тестировать не надо.

Начать работу вы можете с шаблона, который содержит наш фреймворк юнит-тест и заготовку функции GetDistinctRealRootCount.
*/

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <stdexcept>
#include <sstream>
#include <string>

template<class Value>
std::ostream& operator<< (std::ostream& os, const std::vector<Value>& vec)
{
	os << '{';
	bool first = true;

	for (const auto& value : vec)
	{
		if (!first)
		{
			os << ', ';
		}
		first = false;
		os << value;
	}

	return os << '}';
}

template<class Value>
std::ostream& operator<< (std::ostream&, const std::set<Value>& s)
{
	os << "{";
	bool first = true;

	for (const auto& valie : s)
	{
		if (!first)
		{
			os << ", ";
		}

		first = false;
		os << value;
	}

	return os << "}";
}

template<class Key, class Value>
std::ostream& operator<< (std::ostream& os, std::map<Key, Value> m)
{
	os << "{";
	bool first = true;
	for (const auto& [key, value] : m)
	{
		if(!first)
		{
			os << ", ";
		}
		first = false;
		os << key << " " << value;
	}
	return os << "}";
}

template<class Rhs, class Lhs>
void AssertEqual(const Rhs& rhs, const Lhs& lhs, const std::string& hint = {})
{
	if (rhs != lhs)
	{
		std::ostringstream os;
		os << "Assert failed: " << rhs << " != " << lhs;
		if (!hint.empty())
		{
			os << " hint: " << hint;
		}
		throw std::runtime_error(os.str());
	}
}

void Assert(bool b, const std::string hint)
{
	AssertEqual(b, true, hint);
}

class TestRunner
{
public:
	template<class TestFunc>
	void RunTest(TestFunc func, const std::string& test_name)
	{
		try
		{
			func();
			std::cerr << test_name << ": OK" << std::endl;
		}
		catch (const std::exception& e)
		{
			++_fail_count;
			std::cerr << test_name << " fail: " << e.what() << std::endl;
		}
		//catch (...)
		//{
		//	++fail_count;
		//	cerr << "Unknown exception caught" << endl;
		//}
	}

	~TestRunner()
	{
		if (_fail_count > 0)
		{
			std::cerr << _fail_count << " unit tests failed. Terminate" << std::endl;
			exit(1);
		}
	}

private:
	int _fail_count = 0;
};

int GetDistinctRealRootCount(double a, double b, double c)
{
	// Вы можете вставлять сюда различные реализации функции,
	// чтобы проверить, что ваши тесты пропускают корректный код
	// и ловят некорректный
}

int main()
{
	TestRunner runner;
	// добавьте сюда свои тесты
	return 0;
}