#pragma once

#include <chrono>
#include <iostream>
#include <string>

class LogDuration
{
public:
	explicit LogDuration(const std::string& message = {})
		: _message(message + ": ")
		, _start(std::chrono::steady_clock::now())
	{
	}

	~LogDuration()
	{
		auto finish = std::chrono::steady_clock::now();
		auto duration = finish - _start;
		std::cerr << _message
			<< std::chrono::duration_cast<std::chrono::milliseconds>(duration).count()
			<< " ms" << std::endl;
	}
private:
	std::string _message;
	std::chrono::steady_clock::time_point _start;
};

#define UNIQ_ID_IMPL(lineno) _a_local_var_##lineno
#define UNIQ_ID(lineno) UNIQ_ID_IMPL(lineno)

#define LOG_DURATION(message)					\
	LogDuration UNIQ_ID(__LINE__) {message};