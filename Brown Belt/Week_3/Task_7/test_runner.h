#pragma once

#include <sstream>
#include <stdexcept>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <unordered_map>

template <class T>
std::ostream& operator<< (std::ostream& os, const std::vector<T>& v)
{
	os << "{";
	bool first = true;
	for (const auto& x : v)
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
std::ostream& operator<< (std::ostream& os, const std::set<T>& s)
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
std::ostream& operator<< (std::ostream& os, const std::map<K, V>& m)
{
	os << "{";
	bool first = true;
	for (const auto& [key, value] : m)
	{
		if (!first)
		{
			os << ", ";
		}
		first = false;
		os << key << ": " << value;
	}
	return os << "}";
}

template<class K, class V>
std::ostream& operator<< (std::ostream& os, const std::unordered_map<K, V>& um)
{
	os << "{";
	bool first = true;
	for (const auto& [key, value] : um)
	{
		if (!first)
		{
			os << ", ";
		}
		first = false;
		os << key << ": " << value;
	}
	return os << "}";
}

template <class T, class U>
void AssertEqual(const T& t, const U& u, const std::string& hint = {})
{
 	if (!(t == u))
	{
		std::ostringstream os;
		os << "Assertion failed: " << t << " != " << u;
		if (!hint.empty())
		{
			os << "hint: " << hint;
		}
		throw std::runtime_error(os.str());
	}
}

inline void Assert(bool b, const std::string& hint)
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
		catch (std::exception & e)
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

#define ASSERT_EQUAL(x, y)					\
{								\
	std::ostringstream test_runner_os;			\
	test_runner_os << (#x) << " != " << (#y) << ", "	\
	   << __FILE__ << ":" << __LINE__;			\
	AssertEqual(x, y, test_runner_os.str());		\
}

#define ASSERT(x)						\
{								\
	std::ostringstream test_runner_os;			\
	test_runner_os << (#x) << " is false, "			\
	   << __FILE__ << ":" << __LINE__;			\
	Assert(x, test_runner_os.str());			\
}

#define RUN_TEST(tr, func)					\
	tr.RunTest(func, #func)