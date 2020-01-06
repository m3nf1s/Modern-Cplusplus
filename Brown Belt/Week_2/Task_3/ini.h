#pragma once

#include <istream>
#include <unordered_map>
#include <string_view>

namespace Ini
{
    using Section = std::unordered_map<std::string, std::string>;

    class Document 
    {
    public:
        Document() = default;
        Section& AddSection(std::string name);
        const Section& GetSection(const std::string& name) const;
        size_t SectionCount() const;

    private:
        std::unordered_map<std::string, Section> sections;
    };

    std::string_view FindSectionName(std::string_view line);
    std::pair<std::string_view, std::string_view> FindSection(std::string_view line);

    Document Load(std::istream& input);
}