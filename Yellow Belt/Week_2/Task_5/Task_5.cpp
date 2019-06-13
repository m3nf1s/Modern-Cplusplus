/*
В этой задаче вам нужно разработать набор юнит-тестов для функции bool IsPalindrom(const string& s);
Эта функция проверяет, является ли строка s палиндромом.
Палиндром — это слово или фраза, которые одинаково читаются слева направо и справа налево.
Примеры палиндромов: madam, level, wasitacaroracatisaw

Разработайте набор юнит-тестов, который будет принимать правильные реализации функции IsPalindrom и отвергать неправильные.
При этом учитывайте, что правильная реализация функции:
	1) считает пустую строку палиндромом;
	2) считает строку из одного символа палиндромом;
	3) осуществляет обычное сравнение символов на равенство, не игнорируя никакие символы, в том числе пробельные.

При разработке тестов подумайте, какие ошибки можно допустить при реализации функции IsPalindrom.
Примеры ошибок:
	1) игнорируется первый или последний символ;
	2) сравнение соответствующих символов завершается не в середине строки, а раньше;
	3) игнорируются пробелы
*/

#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

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

bool IsPalindrom(const std::string& str)
{
	for (size_t i = 0; i < str.size() / 2; i++)
	{
		if (str.at(i) != str.at(str.size() - i - 1))
		{
			return false;
		}
	}

	return true;
}

void TestPalindrom()
{
	Assert(IsPalindrom("wakaw"), "wakaw isn't palindrom");
	Assert(IsPalindrom(""), "empty string isn't palindrom");
	Assert(IsPalindrom("s"), "s isn't palindrom");
	Assert(!IsPalindrom("wakow"), "wakow is palindrom");
	Assert(!IsPalindrom("VakoK"), "VakoK is palindrom");
	Assert(!IsPalindrom("wa lin"), "wa lin is palindrom");
	Assert(!IsPalindrom("waklaw"), "waklaw is palindrom");
	Assert(!IsPalindrom("masdam"), "masdam is palindrom");
	Assert(IsPalindrom("wa k aw"), "wa k aw isn't palindrom");
	Assert(IsPalindrom("   "), "empty  isn't palindrom");
	Assert(!IsPalindrom(" K  "), " K   is palindrom");
	Assert(IsPalindrom(" S "), " S  isn't palindrom");
}

void Test()
{
	AssertEqual(IsPalindrom("madam"), 1);
	AssertEqual(IsPalindrom("lool"), 1);
	AssertEqual(IsPalindrom("o"), 1);
	AssertEqual(IsPalindrom(""), 1);
	AssertEqual(IsPalindrom(" "), 1);
	AssertEqual(IsPalindrom("  "), 1);
	AssertEqual(IsPalindrom("top pot"), 1);
	AssertEqual(IsPalindrom("o lol o"), 1);
	AssertEqual(IsPalindrom(" olo "), 1);
	AssertEqual(IsPalindrom("olol"), 0);
	AssertEqual(IsPalindrom("motor"), 0);
	AssertEqual(IsPalindrom("topo gun"), 0);
	AssertEqual(IsPalindrom("olol "), 0);
	AssertEqual(IsPalindrom(" lol"), 0);
	AssertEqual(IsPalindrom("olo" + '\n'), 0);
}

int main()
{
	TestRunner runner;
	runner.RunTest(TestPalindrom, "Is Palindrom");
	runner.RunTest(Test, "Test");
	return 0;
}