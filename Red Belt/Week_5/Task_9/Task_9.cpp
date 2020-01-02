/*
    Крупная IT-компания Янгл проводит исследование упоминаемости своего бренда в блогах и социальных сетях.
    Аналитики компании уже выгрузили интересующие их публикации и сформировали набор ключевых слов.
    Их интересует, сколько раз каждое ключевое слово входит в набор публикаций.

    Помогите им это сделать — напишите функцию Stats ExploreKeyWords(const set<string>& key_words, istream& input).
    Её параметры:
    *   key_words — множество ключевых слов
    *   input — входной поток, содержащий исследуемые публикации в блогах и соц. сетях, одна строка — одна публикация.

    Функция ExploreKeyWords должна возвращать структуру Stats, в которой хранится,
    сколько раз каждое слово из key_words суммарно встретилось в потоке input.

    При подсчёте вхождения ключевых слов в текст нужно учитывать только вхождения в виде отдельных слов.
    Слова друг от друга отделяются одним или несколькими пробелами.
    В качестве примера допустим, что key_words = {"yangle", "rocks", "sucks", "all"}
    и у нас есть публикация из соц. сети Switter: "Goondex really sucks, but yangle rocks ! Use yangle".
    Слово «yangle» входит в неё 2 раза, «rocks» — один раз, а слова «all» и «sucks» — ни разу.
    Слово «sucks» не входит ни разу, потому что в данном примере оно является префиксом слова «sucks,»
    (по условию, слова друг от друга отделяются только пробелами).
    Несмотря на то, что слово «all» является частью слова «really»,
    его вхождение тоже нельзя засчитывать, так как это не отдельное слово.

    Чтобы уложиться в Time Limit, подумайте, можно ли эту задачу распараллелить.
*/

#include "test_runner.h"
#include "profile.h"

#include <vector>
#include <map>
#include <string>
#include <set>
#include <sstream>
#include <string_view>
#include <future>
#include <cmath>

template <typename Iterator>
class IteratorRange
{
public:
    IteratorRange(Iterator begin, Iterator end)
        : first(begin)
        , last(end)
        , size_(distance(first, last))
    {
    }

    Iterator begin() const
    {
        return first;
    }

    Iterator end() const
    {
        return last;
    }

    size_t size() const
    {
        return size_;
    }

private:
    Iterator first, last;
    size_t size_;
};

template <typename Iterator>
class Paginator
{
private:
    std::vector<IteratorRange<Iterator>> pages;

public:
    Paginator(Iterator begin, Iterator end, size_t page_size)
    {
        for (size_t left = std::distance(begin, end); left > 0; )
        {
            size_t current_page_size = std::min(page_size, left);
            Iterator current_page_end = std::next(begin, current_page_size);
            pages.push_back({ begin, current_page_end });

            left -= current_page_size;
            begin = current_page_end;
        }
    }

    auto begin() const
    {
        return pages.begin();
    }

    auto end() const
    {
        return pages.end();
    }

    size_t size() const
    {
        return pages.size();
    }
};

template <typename C>
auto Paginate(C& c, size_t page_size)
{
    return Paginator(begin(c), end(c), page_size);
}

struct Stats
{
    std::map<std::string, int> word_frequences;

    void operator += (const Stats& other)
    {
        for (const auto& [word, count] : other.word_frequences)
        {
            word_frequences[word] += count;
        }
    }
};

Stats ExploreLine(const std::set<std::string>& key_words, const std::string& line)
{
    Stats result;
    std::string_view sv = line;

    while(true)
    {
        size_t space = sv.find(' ');
        std::string word(sv.substr(0, space));

        if (key_words.count(word))
        {
            ++result.word_frequences[word];
        }

        if (space == sv.npos)
        {
            break;
        }
        sv.remove_prefix(space + 1);
    }

    return result;
}

Stats ExploreKeyWordsSingleThread(const std::set<std::string>& key_words, std::istream& input)
{
    Stats result;
    for (std::string line; std::getline(input, line); )
    {
        result += ExploreLine(key_words, line);
    }
    return result;
}

template <typename Container>
Stats TemplateExploreKeyWords(const std::set<std::string>& key_words, Container& input)
{
    Stats result;
    for(const auto& line : input)
    {
        result += ExploreLine(key_words, line);
    }
    return result;
}

Stats ExploreKeyWords(const std::set<std::string>& key_words, std::istream& input)
{
    std::vector<std::string> lines;

    for (std::string line; std::getline(input, line); )
    {
        lines.push_back(line);
    }

    double threads_count = 4.0;
    size_t page_size = std::min<size_t>(lines.size(), std::ceil(lines.size() / threads_count));

    std::vector<std::future<Stats>> futures;

    for (const auto& page : Paginate(lines, page_size))
    {
        futures.push_back(std::async([&key_words, page]
            {
                return TemplateExploreKeyWords(key_words, page);
            }));
    }

    Stats result;

    for (auto& f : futures)
    {
        result += f.get();
    }
    return result;    
}

void TestBasic()
{
    const std::set<std::string> key_words = { "yangle", "rocks", "sucks", "all" };

    std::stringstream ss;
    ss << "this new yangle service really rocks\n";
    ss << "It sucks when yangle isn't available\n";
    ss << "10 reasons why yangle is the best IT company\n";
    ss << "yangle rocks others suck\n";
    ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

    const auto stats = ExploreKeyWords(key_words, ss);
    const std::map<std::string, int> expected =
    {
        {"yangle", 6},
        {"rocks", 2},
        {"sucks", 1}
    };
    ASSERT_EQUAL(stats.word_frequences, expected);
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestBasic);
}