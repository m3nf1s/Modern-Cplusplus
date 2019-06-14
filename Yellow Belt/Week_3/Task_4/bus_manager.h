#pragma once

#include "responses.h"

class BusManager {
public:
	//�������� ������� � �����������
	//bus - �������
	//stops - ������ ���������
	void AddBus(const std::string& bus, const std::vector<std::string>& stops);

	//�������� ���������� �� ���������, ������� �������� ����� ������ ���������
	//stop - ���������
	BusesForStopResponse GetBusesForStop(const std::string& stop) const;

	//�������� ���������� � ���� ���������� �������� ��������
	//bus - �������
	StopsForBusResponse GetStopsForBus(const std::string& bus) const;

	//�������� ���������� � ���� ���������
	AllBusesResponse GetAllBuses() const;

	std::map<std::string, std::vector<std::string>> GetBusesList();

	std::map<std::string, std::vector<std::string>> GetStopsList();

private:
	//������ ��� ������� �������� ������ ���������
	std::map<std::string, std::vector<std::string>> list_buses_stops;
	//������ ��� ������ ��������� ������ ���������, ������� ��������� ����� ���
	std::map<std::string, std::vector<std::string>> list_stops_buses;
};