#include "stats.h"

#include <cctype>

Stats::Stats()
{
	Initialization(known_methods_, methods_);
	methods_[unknown_method] = 0;
	Initialization(known_uri_, uri_);
	uri_[unknown_uri] = 0;
}

void Stats::AddMethod(std::string_view method)
{
	if (methods_.count(method))
	{
		++methods_[method];
	}
	else
	{
		++methods_[unknown_method];
	}
}

void Stats::AddUri(std::string_view uri)
{
	if (uri_.count(uri))
	{
		++uri_[uri];
	}
	else
	{
		++uri_[unknown_uri];
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

void RemoveSpaces(std::string_view& line)
{
	while (!line.empty() && std::isspace(line[0]))
	{
		line.remove_prefix(1);
	}
}

std::string_view ParseSV(std::string_view& line)
{
	RemoveSpaces(line);
	size_t index = line.find(' ');
	std::string_view result = line.substr(0, index);
	line.remove_prefix(index + 1);

	return result;
}

HttpRequest ParseRequest(std::string_view line)
{
	std::string_view method = ParseSV(line);
	std::string_view uri = ParseSV(line);
	std::string_view protocol = ParseSV(line);
	return { method, uri, protocol };
}