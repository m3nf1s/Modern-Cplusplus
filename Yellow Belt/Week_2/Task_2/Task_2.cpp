/*
Функция int GetDistinctRealRootCount(double a, double b, double c);
	возвращает количество уникальных действительных корней уравнения ax² + bx + c = 0.
Разработайте набор юнит-тестов для проверки корректности реализации этой функции.
Случай, когда все три коэффициента равны нулю, тестировать не надо.
*/

#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <cmath>

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

class TestRunner {
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

//Решение для квадратного уравнения
int SolveQuadradicEquation(double a, double b, double c)
{
	std::set<double> roots;

	double D = std::pow(b, 2) - 4 * a * c;
	//если дискриминант == 0 - 1 корень
	if (D == 0)
	{
		double result = (-b + std::sqrt(D)) / 2 * a;
		roots.insert(result);
	}
	//если дискриминант > 0 - 2 корня
	else if (D > 0)
	{
		double result = (-b + std::sqrt(D)) / 2 * a;
		roots.insert(result);
		result = (-b - std::sqrt(D)) / 2 * a;
		roots.insert(result);
	}
	//Если D < 0 вернет пустой set, либо с корнями
	return roots.size();
}

//Решение для линейного уравнения
int SolveLinearEquation(double b, double c)
{
	std::set<double> root;
	if (b != 0)
	{
		double result = -c / b;
		root.insert(result);
	}

	return root.size();
}

int GetDistinctRealRootCount(double a, double b, double c)
{
	if (a != 0)
	{
		return SolveQuadradicEquation(a, b, c);
	}
	else
	{
		return SolveLinearEquation(b, c);
	}
}

void TestNullRoots()
{
	AssertEqual(GetDistinctRealRootCount(0, 0, 1), 0);
	AssertEqual(GetDistinctRealRootCount(1, 2, 4), 0);
}

void TestOneRoot()
{
	AssertEqual(GetDistinctRealRootCount(0, 1, 2), 1);
	AssertEqual(GetDistinctRealRootCount(1, 4, 4), 1);
}

void TestTwoRoots()
{
	AssertEqual(GetDistinctRealRootCount(1, 5, 4), 2);
	AssertEqual(GetDistinctRealRootCount(5, 10, 4), 2);
}

int main() {
	TestRunner runner;
	runner.RunTest(TestNullRoots, "NullRoots");
	runner.RunTest(TestOneRoot, "OneRoot");
	runner.RunTest(TestTwoRoots, "TwoRoots");
	return 0;
}