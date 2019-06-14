#pragma once

#include <string>

class PhoneNumber
{
public:
	/* ��������� ������ � ������� +XXX-YYY-ZZZZZZ
	   ����� �� '+' �� ������� '-' - ��� ��� ������.
	   ����� ����� ������ � ������ ��������� '-' - ��� ������
	   ��, ��� ��� ����� ������� ������� '-' - ������� �����.
	   ��� ������, ��� ������ � ������� ����� �� ������ ���� �������.
	   ���� ������ �� ������������� ����� �������, ����� ��������� ���������� invalid_argument. ���������, ��� ����� �������� ������ �����, �� �����.

	   �������:
	   * +7-495-111-22-33
	   * +7-495-1112233
	   * +323-22-460002
	   * +1-2-coursera-cpp
	   * 1-2-333 - ������������ ����� - �� ���������� �� '+'
	   * +7-1233 - ������������ ����� - ���� ������ ��� ������ � ������
	*/
	explicit PhoneNumber(const std::string& international_number);

	std::string GetCountryCode() const;
	std::string GetCityCode() const;
	std::string GetLocalNumber() const;
	std::string GetInternationalNumber() const;

private:
	std::string country_code_;
	std::string city_code_;
	std::string local_number_;
};