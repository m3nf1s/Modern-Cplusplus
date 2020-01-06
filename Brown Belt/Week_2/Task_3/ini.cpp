#include "ini.h"

#include <string>
#include <exception>

namespace Ini
{
	Section& Document::AddSection(std::string name)
	{
		return sections[std::move(name)];
	}

	const Section& Document::GetSection(const std::string& name) const
	{
		return sections.at(name);
	}

	size_t Document::SectionCount() const
	{
		return sections.size();
	}

	std::string_view FindSectionName(std::string_view line)
	{
		line.remove_prefix(1);

		size_t pos = line.find(']');

		line.remove_suffix(line.size() - pos);

		return line;
	}

	std::pair<std::string_view, std::string_view> FindSection(std::string_view line)
	{
		size_t pos = line.find('=');

		std::string_view category = line.substr(0, pos);

		std::string_view amount = line.substr(pos + 1);

		return { category, amount };
	}

	Document Load(std::istream& input)
	{
		Document result;
		Section* section = nullptr;

		for (std::string line; std::getline(input, line); )
		{
			if (line[0] == '[')
			{
				std::string_view name = FindSectionName(line);
				section = &result.AddSection(std::string(name));
			}
			else if (!line.empty())
			{
				auto [category, amount] = FindSection(line);
				section->insert({ std::string(category), std::string(amount) });
			}
		}

		return result;
	}
}