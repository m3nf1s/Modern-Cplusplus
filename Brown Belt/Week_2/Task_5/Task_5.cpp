/*
	� ���������� ����� �� ��������, ��� ������������ ��� ����� �������������� ��� ���������������� ����
	� ��� ��������� �� ���������� �����.
	� ���� ������ ��� ��������� ���������������� � ����.
	
	��� ���� ���������, ������� ����� ��������� ��������� ��������� ������ ����� �����:
	�������, ��������, �����, ������� � ����.
	������ ��������� � ��������� ����������� � ���� ���������� ������,
	������� �������� �������� ������������ �������� ������ StatsAggregator.
	
	��� ������ ����� �����:	
	*	SumStatsAggregator
	*	MinStatsAggregator
	*	MaxStatsAggregator
	*	AverageStatsAggregator
	*	ModeStatsAggregator

	��� ������, � ���� ���� ������� ����� �������.
	��� ������ ������������� ����� ������������ ��� � ���������� ��� ����������
	(�������� ��� �������� ����� � ����������� ������� � ����� � �������).
	
	��������� ��������� �������������� ����:	
	*	������� �� ��� �������� StatsAggregator ����� ������� (��������, SumStatsAggregator ���� ������������� � Sum)
	*	������� �� ��� ������ ����� ������� (��������, TestSumStatsAggregator ���� ������������� � TestSum
		(��. ����-����� � ������ stats_aggregator.h � stats_aggregator_test.cpp ����))
	*	��������� ������-������� StatsAggregator,
		� ����� ����� ��� ��� � ������������ ��� StatsAggregators
	*	�������� ���� main.cpp ���, ����� �� ��������� ������� � ����� ���������� ���� (� �.�. ������� ����-�����)
	*	������� ����� StatsAggregator �������� � ���������� ������������ ���

	��� ���������� � �����, ����������� �������� ������ � ������������ ��� �������� ����� �����.
	� ���� ������ �� ������ �������� ��� � ���������� ������������ ���, ������ ��� ��� ��������� �� ������� ���,
	������� �������� � ����������� �����������, � �� � ��� ������������.
	���� ������������, ����� ����� ������, �� ������ ��������� StatsAggregator � ������������ ��� StatsAggregators
	� ����������, ����� ��� ��� ������� �������� � ������ �� �� �� ����� ��������� �����.
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