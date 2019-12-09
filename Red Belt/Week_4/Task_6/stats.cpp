#include "stats.h"

#include <algorithm>

void Stats::AddMethod(std::string_view method)
{
	auto it = std::find(data_methods_.begin(), data_methods_.end(), method);
	if (it != data_methods_.end())
	{
		++methods_[*it];
	}
	else
	{
		++methods_["UNKNOWN"];
	}
}

void Stats::AddUri(std::string_view uri)
{
	auto it = std::find(data_uri_.begin(), data_uri_.end(), uri);
	if (it != data_uri_.end())
	{
		++uri_[*it];
	}
	else
	{
		++uri_["unknown"];
	}
}

const std::map<std::string_view, int>& Stats::GetMethodStats() const
{
	return methods_;
}

const std::map<std::string_view, int>& Stats::GetUriStats() const
{
	return uri_;
}

Stats::Stats()
{
	for (const auto& method : data_methods_)
	{
		methods_[method] = 0;
	}

	for (const auto& uri : data_uri_)
	{
		uri_[uri] = 0;
	}
}

std::string_view ParseSV(std::string_view line)
{
	size_t index = line.find(' ');
	std::string_view result = line.substr(0, index);
	if (index != line.npos)
	{
		line.remove_prefix(index + 1);
	}

	return result;
}

HttpRequest ParseRequest(std::string_view line)
{
	//std::string_view method, uri, protocol;

	std::string_view method = ParseSV(line);
	std::string_view uri = ParseSV(line);
	std::string_view protocol = ParseSV(line);

	return { method, uri, protocol };
}