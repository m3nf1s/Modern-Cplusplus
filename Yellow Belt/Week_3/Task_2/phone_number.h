#pragma once

#include <string>

class PhoneNumber
{
public:
	/* Принимает строку в формате +XXX-YYY-ZZZZZZ
	   Часть от '+' до первого '-' - это код страны.
	   Часть между первым и вторым символами '-' - код города
	   Всё, что идёт после второго символа '-' - местный номер.
	   Код страны, код города и местный номер не должны быть пустыми.
	   Если строка не соответствует этому формату, нужно выбросить исключение invalid_argument. Проверять, что номер содержит только цифры, не нужно.

	   Примеры:
	   * +7-495-111-22-33
	   * +7-495-1112233
	   * +323-22-460002
	   * +1-2-coursera-cpp
	   * 1-2-333 - некорректный номер - не начинается на '+'
	   * +7-1233 - некорректный номер - есть только код страны и города
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