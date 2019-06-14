#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <map>

//������ ���������� �� ���������� ����������, ������� �������� ����� ������������ ���������
struct BusesForStopResponse
{
	std::vector<std::string> busesforstop;
};

std::ostream& operator<< (std::ostream& os, const BusesForStopResponse& r);

//������ ���������� �� ���������� �������� � ����� �������� �������� ����� ������������ ���������
// stops - ��������� � ��������� �������
// stops_buses - ��������� � �������� ���������
struct StopsForBusResponse
{
	std::vector<std::string> stops;
	std::map<std::string, std::vector<std::string>> stops_buses;
};

std::ostream& operator<< (std::ostream& os, const StopsForBusResponse& r);

//������ ��� ���������� � ���� ���������� ���������
struct AllBusesResponse
{
	std::map<std::string, std::vector<std::string>> allbuses;
};

std::ostream& operator<< (std::ostream& os, const AllBusesResponse& r);