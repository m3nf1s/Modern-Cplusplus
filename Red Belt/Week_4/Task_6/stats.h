#pragma once

#include "http_request.h"

#include <string_view>
#include <map>
#include <array>

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

	static const size_t KNOWN_METHODS_SIZE = 4;
	inline static const std::array<std::string, KNOWN_METHODS_SIZE> known_methods_ =
	{
		"GET", "POST", "PUT", "DELETE"
	};
	inline static const std::string unknown_method = "UNKNOWN";

	static const size_t KNOWN_URI_SIZE = 5;
	inline static const std::array<std::string, KNOWN_URI_SIZE> known_uri_ =
	{
		"/", "/order", "/product", "/basket", "/help", 
	};
	inline static const std::string unknown_uri = "unknown";

	template <typename Container, typename Init_Container>
	void Initialization(const Container& c, Init_Container& init)
	{
		for (const auto& x : c)
		{
			init[x] = 0;
		}
	}
};

HttpRequest ParseRequest(std::string_view line);