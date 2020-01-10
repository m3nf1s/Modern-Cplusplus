/*
	Вы устроились на новую работу и подключились к давно существующему проекту.
	Проект состоит в исследовании различных показателей по результатам переписи населения.
	Как это часто бывает, проект начинался как простая система, которая решала одну задачу,
	но со временем в неё стали добавлять новые функции.
	Делалось это как обычно — в аврале и в последний момент.
	
	Первой задачей, с которой начинался проект, было моделирование изменения возраста совершеннолетия.
	Экспериментаторы вводили различный возраст совершеннолетия и изучали,
	сколько в таком случае в обществе будет совершеннолетних людей.
	От этого рассчитывались годовые бюджеты, планы по сбору налога на доходы физических лиц и т.д.
	
	Первая версия программы принимала на вход список всех людей, которые живут в государстве,
	полученный с помощью переписи населения.
	Затем ей на вход подавался поток команд вида "AGE N".
	Для каждой такой строки программа выводила в стандартный вывод
	сообщение "There are X adult people for maturity age N".
	Программа отлично работала и справлялась со списком в несколько миллионов людей.
	
	Но потом начальство срочно захотело больше функций.
	Появилась новая команда — «WEALTHY M»,
	в ответ на которую программа должна была выводить суммарный доход M богатейших людей общества
	в виде "Top-M people have total income X".
	
	Когда тестирование новой функциональности ещё не было окончено,
	руководство потребовало немедленно поддержать команду «POPULAR_NAME M/W»,
	в ответ на которую программа сообщала самое популярное женское или мужское имя
	в виде "Most popular name among people of gender M is Ivan".
	
	Предыдущая команда быстро реализовала эту функциональность за 2 часа до дедлайна,
	убедилась, что на простейших тестах она корректно работает и поставила программу заказчику.
	Естественно, программа у заказчика не заработала, и он попросил её исправить,
	прислав подробнейшее описание найденных ошибок со всеми деталями.
	Выглядело оно так: «Ваша программа вообще не работает! Срочно исправьте, а то засужу».
	
	Прежнюю команду, естественно, тут же уволили и наняли вас =)
	Итак, вам дана программа и единственный тест, на котором её тестировали.
	Вам надо сделать всё хорошо.
	
	Формат ввода
	На вход программе поступает число N — количество людей.
	Далее идут N строк в формате Имя Возраст Доход Пол.
	Далее идут сами команды, по одной в строке.
	
	Виды команд:	
	*	AGE N — в ответ на неё в отдельной строке программа должна вывести сообщение 
		"There are X adult people for maturity age N", где X — количество людей, возраст которых не меньше N
	*	WEALTHY M — в ответ на неё в отдельной строке программа должна вывести сообщение 
		"Top-M people have total income X", где X — суммарный доход первых M богатейших людей.
	*	POPULAR_NAME M — в ответ на неё в отдельной строке программа должна вывести сообщение 
		"Most popular name among people of gender M is S", где S — мужское имя, которое встречается больше всего раз.
		Если таких имён несколько, программа должна вывести лексикографически минимальное.
		Если таких имён нет, должно быть выведено "No people of gender M".
	*	POPULAR_NAME W — в ответ на неё в отдельной строке программа должна вывести сообщение 
		"Most popular name among people of gender W is S", где S — женское имя, которое встречается больше всего раз.
		Если таких имён несколько, программа должна вывести лексикографически минимальное.
		Если таких имён нет, должно быть выведено "No people of gender W".
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <optional>

template <typename Iterator>
class IteratorRange
{
public:
	IteratorRange(Iterator begin, Iterator end)
		: first(begin)
		, last(end)
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

private:
	Iterator first, last;
};

template <typename Collection>
auto Head(Collection& v, size_t top)
{
	return IteratorRange{ v.begin(), next(v.begin(), std::min(top, v.size())) };
}

struct Person
{
	std::string name;
	int age, income;
	bool is_male;
};


std::vector<Person> ReadPeople(std::istream& input)
{
	int count;
	input >> count;

	std::vector<Person> result(count);
	for (Person& p : result)
	{
		char gender;
		input >> p.name >> p.age >> p.income >> gender;
		p.is_male = gender == 'M';
	}

	return result;
}

struct Stats
{
	std::optional<std::string> popular_name_male;
	std::optional<std::string> popular_name_female;
	std::vector<int> wealth;
	std::vector<Person> sorted_by_age;
};

template <typename Iter>
std::optional<std::string> FindPopularName(IteratorRange<Iter> range)
{
	if (range.begin() == range.end())
	{
		return std::nullopt;
	}

	std::sort(range.begin(), range.end(), [](const Person& lhs, const Person& rhs)
		{
			return lhs.name < rhs.name;
		});

	int count = 1;
	const std::string* popular_name = &range.begin()->name;

	for (auto it = range.begin(); it != range.end(); )
	{
		auto current_name_it = std::find_if_not(it, range.end(), [it](const Person& person)
			{
				return it->name == person.name;
			});

		const int current_name_count = std::distance(it, current_name_it);

		if (current_name_count > count || (current_name_count == count && it->name < *popular_name))
		{
			popular_name = &it->name;
			count = current_name_count;
		}

		it = current_name_it;
	}

	return *popular_name;
}

Stats BuildStats(std::vector<Person> people)
{
	Stats result;
	// MOST POPULAR NAME
	auto male_end = std::partition(people.begin(), people.end(), [](const Person& person)
		{
			return person.is_male;
		});

	IteratorRange male(people.begin(), male_end);
	IteratorRange female(male_end, people.end());

	result.popular_name_male = FindPopularName(male);
	result.popular_name_female = FindPopularName(female);

	//WEALTH

	std::sort(people.begin(), people.end(), [](const Person& lhs, const Person rhs)
		{
			return lhs.income > rhs.income;
		});

	auto& wealth = result.wealth;
	wealth.resize(people.size());

	if (!people.empty())
	{
		wealth[0] = people[0].income;

		for (size_t i = 1; i < people.size(); ++i)
		{
			wealth[i] = wealth[i - 1] + people[i].income;
		}
	}

	// AGE

	std::sort(people.begin(), people.end(), [](const Person& lhs, const Person& rhs)
		{
			return lhs.age < rhs.age;
		});

	result.sorted_by_age = std::move(people);

	return result;
}

void PrintAge(const Stats& stats, int adult_age)
{
	auto adult_begin = std::lower_bound(
		stats.sorted_by_age.begin(), stats.sorted_by_age.end(), adult_age, [](const Person& lhs, int age)
		{
			return lhs.age < age;
		}
	);

	std::cout << "There are " << std::distance(adult_begin, stats.sorted_by_age.end())
		<< " adult people for maturity age " << adult_age << '\n';
}

void PrintWealth(const Stats& stats, int count)
{
	std::cout << "Top-" << count << " people have total income " << stats.wealth[count - 1] << '\n';
}

void PrintPopularName(const Stats& stats, char gender)
{
	const auto& most_popular_name = gender == 'M' ? stats.popular_name_male : stats.popular_name_female;
	if (most_popular_name) 
	{
		std::cout << "Most popular name among people of gender " << gender << " is " << *most_popular_name << '\n';
	}
	else 
	{
		std::cout << "No people of gender " << gender << '\n';
	}
}

int main()
{
	const Stats stats = BuildStats(ReadPeople(std::cin));

	for (std::string command; std::cin >> command; )
	{
		if (command == "AGE")
		{
			int adult_age;
			std::cin >> adult_age;

			PrintAge(stats, adult_age);
		}
		else if (command == "WEALTHY")
		{
			int count;
			std::cin >> count;

			PrintWealth(stats, count);
		}
		else if (command == "POPULAR_NAME")
		{
			char gender;
			std::cin >> gender;

			PrintPopularName(stats, gender);
		}
	}
}
