/*
	В предыдущем видео мы показали, как пространства имён могут использоваться для структурирования кода
	и его разбиения на логические блоки.
	В этой задаче вам предстоит попрактиковаться в этом.
	
	Вам дана программа, которая умеет вычислять различные агрегации набора целых чисел:
	минимум, максимум, сумму, среднее и моду.
	Каждая агрегация в программе реализована в виде отдельного класса,
	который является потомком абстрактного базового класса StatsAggregator.
	
	Эти классы имеют имена:	
	*	SumStatsAggregator
	*	MinStatsAggregator
	*	MaxStatsAggregator
	*	AverageStatsAggregator
	*	ModeStatsAggregator

	Как видите, у всех этих классов общий суффикс.
	Его частое использование может загромождать код и затруднять его читаемость
	(особенно это касается файла с реализацией классов и файла с тестами).
	
	Выполните следующие преобразования кода:	
	*	удалите из имён потомков StatsAggregator общий суффикс (например, SumStatsAggregator надо переименовать в Sum)
	*	удалите из имён тестов общий суффикс (например, TestSumStatsAggregator надо переименовать в TestSum
		(см. юнит-тесты в файлах stats_aggregator.h и stats_aggregator_test.cpp ниже))
	*	поместите классы-потомки StatsAggregator,
		а также тесты для них в пространство имён StatsAggregators
	*	обновите файл main.cpp так, чтобы он корректно работал с новой структурой кода (в т.ч. вызывал юнит-тесты)
	*	базовый класс StatsAggregator оставьте в глобальном пространстве имён

	Как говорилось в видео, перемещение базового класса в пространство имён является делом вкуса.
	В этой задаче мы просим оставить его в глобальном пространстве имён, потому что это позволяет не трогать код,
	который работает с абстрактным интерфейсом, а не с его реализациями.
	Ради эксперимента, после сдачи задачи, вы можете поместить StatsAggregator в пространство имён StatsAggregators
	и посмотреть, какой ещё код придётся поменять и станет ли он от этого изменения проще.
*/
#include "test_runner.h"
#include "stats_aggregator.h"

#include <vector>
#include <string>
#include <map>
#include <memory>
#include <iostream>
#include <unordered_map>
#include <functional>

void TestAll();

std::unique_ptr<StatsAggregator> ReadAggregators(std::istream& input)
{
	using namespace StatsAggregators;

	const std::unordered_map<std::string, std::function<std::unique_ptr<StatsAggregator>()>> known_builders =
	{
		{"sum", [] { return std::make_unique<Sum>(); }},
		{"min", [] { return std::make_unique<Min>(); }},
		{"max", [] { return std::make_unique<Max>(); }},
		{"avg", [] { return std::make_unique<Average>(); }},
		{"mode", [] { return std::make_unique<Mode>(); }}
	};

	auto result = std::make_unique<Composite>();

	int aggr_count;
	input >> aggr_count;

	std::string line;
	for (int i = 0; i < aggr_count; ++i)
	{
		input >> line;
		result->Add(known_builders.at(line)());
	}

	return result;
}

int main()
{
	TestAll();

	auto stats_aggregator = ReadAggregators(std::cin);

	for (int value; std::cin >> value; )
	{
		stats_aggregator->Process(value);
	}
	stats_aggregator->PrintValue(std::cout);

	return 0;
}

void TestAll()
{
	TestRunner tr;
	RUN_TEST(tr, StatsAggregators::TestSum);
	RUN_TEST(tr, StatsAggregators::TestMin);
	RUN_TEST(tr, StatsAggregators::TestMax);
	RUN_TEST(tr, StatsAggregators::TestAverage);
	RUN_TEST(tr, StatsAggregators::TestMode);
	RUN_TEST(tr, StatsAggregators::TestComposite);
}