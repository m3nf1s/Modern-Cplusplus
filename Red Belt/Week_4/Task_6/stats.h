#pragma once

#include "http_request.h"

#include <string_view>
#include <map>
#include <array>
#include <set>

class Stats 
{
public:
	void AddMethod(std::string_view method);
	void AddUri(std::string_view uri);
	const std::map<std::string_view, int>& GetMethodStats() const;
	const std::map<std::string_view, int>& GetUriStats() const;
	Stats();

private:
	std::map<std::string_view, int> methods_;
	std::map<std::string_view, int> uri_;

	static const size_t METHODS_SIZE = 5;
	static const size_t URI_SIZE = 6;

	std::array<std::string, METHODS_SIZE> data_methods_ =
	{
		"DELETE", "GET", "POST", "PUT", "UNKNOWN"
	};

	std::array<std::string, URI_SIZE> data_uri_ =
	{
		"/", "/basket", "/help", "/order", "/product", "unknown"
	};
};

HttpRequest ParseRequest(std::string_view line);