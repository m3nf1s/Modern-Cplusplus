/*
Класс Rational представляет собой рациональное число и имеет следующий интерфейс
Список требований, предъявляемых к реализации интерфейса класса Rational:
	1) Конструктор по умолчанию должен создавать дробь с числителем 0 и знаменателем 1.
	2) При конструировании объекта класса Rational с параметрами p и q должно выполняться сокращение дроби p/q.
	3) Если дробь p/q отрицательная, то объект Rational(p, q) должен иметь отрицательный числитель и положительный знаменатель.
	4) Если дробь p/q положительная, то объект Rational(p, q) должен иметь положительные числитель и знаменатель (обратите внимание на случай Rational(-2, -3)).
	5) Если числитель дроби равен нулю, то знаменатель должен быть равен 1.
Разработайте набор юнит-тестов, которые будут проверять корректность реализации класса Rational.
Тестировать случай, когда знаменатель равен нулю, не надо.
*/
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <limits>
#include <numeric>

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

class Rational
{
public:
	Rational()
	{
		_numerator = 0;
		_denominator = 1;
	}

	Rational(int numerator, int denominator)
	{
		if (numerator == 0 || denominator == 0)
		{
			Init();
		}
		else
		{
			int GCD = std::gcd(numerator, denominator);
			numerator /= GCD;
			denominator /= GCD;

			if (numerator > 0 && denominator < 0 || numerator < 0 && denominator < 0)
			{
				_numerator = -numerator;
				_denominator = -denominator;

			}
			else
			{
				_numerator = numerator;
				_denominator = denominator;
			}
		}
	}

	int Numerator() const
	{
		return _numerator;
	}

	int Denominator() const
	{
		return _denominator;
	}
private:
	int _numerator;
	int _denominator;

	void Init()
	{
		_numerator = 0;
		_denominator = 1;
	}
};

std::ostream& operator<<(std::ostream& os, const Rational& r)
{
	return os << r.Numerator() << "/" << r.Denominator();
}

bool operator!= (const Rational& lhs, const Rational rhs)
{
	return lhs.Numerator() != rhs.Numerator() || lhs.Denominator() != rhs.Denominator();
}

void TestRationals()
{
	//Deafaul конструктор
	{
		Rational r1;
		Rational r2(0, 1);
		AssertEqual(r1, r2, "def != 0/1");
	}

	{
		Rational r1;
		Rational r2(0, 100);
		AssertEqual(r1, r2, "def != 0/1 (0/100)");
	}

	{
		Rational r1;
		Rational r2(0, -100);
		AssertEqual(r1, r2, "def != 0/1 (0/100)");
	}
	// 0/1 проверка дроби
	{
		Rational r1(0, 1);
		Rational r2(0, -1);
		AssertEqual(r1, r2, "0/1 != 0/1 (0/-1)");
	}

	{
		Rational r1(0, 1);
		Rational r2(0, 25);
		AssertEqual(r1, r2, "0/1 != 0/1 (0/25)");
	}

	// Сокращение с разными знаками
	{
		Rational r1 (2, 3);
		Rational r2(8, 12);
		AssertEqual(r1, r2, "2/3 != 8/12");
	}

	{
		Rational r1(12, -8);
		Rational r2(-3, 2);
		AssertEqual(r1, r2, "12/-8 != -3/2");
	}

	{
		Rational r1(-12, 8);
		Rational r2(-3, 2);
		AssertEqual(r1, r2, "-12/8 != -3/2");
	}

	{
		Rational r1(-12, -8);
		Rational r2(3, 2);
		AssertEqual(r1, r2, "-12/-8 != 3/2");
	}

	//Единичные
	{
		Rational r1(3, 3);
		Rational r2(1, 1);
		AssertEqual(r1, r2, "3/3 != 1/1");
	}
}

int main() {
	TestRunner runner;
	runner.RunTest(TestRationals, "TestRationals");
	return 0;
}