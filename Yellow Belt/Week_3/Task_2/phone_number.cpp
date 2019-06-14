#include "phone_number.h"
#include <iostream>
#include <sstream>
#include <stdexcept>

PhoneNumber::PhoneNumber(const std::string& international_number)
{
	std::stringstream ss(international_number);
	
	char sigh = ss.get();

	getline(ss, country_code_, '-');

	getline(ss, city_code_, '-');

	getline(ss, local_number_);

	if (sigh != '+' || country_code_.empty() || city_code_.empty() || local_number_.empty())
	{
		throw std::invalid_argument("Wrong phone number: " + international_number);
	}
}

std::string PhoneNumber::GetCountryCode() const
{
	return country_code_;
}

std::string PhoneNumber::GetCityCode() const
{
	return city_code_;
}
std::string PhoneNumber::GetLocalNumber() const
{
	return local_number_;
}
std::string PhoneNumber::GetInternationalNumber() const
{
	return "+" + GetCountryCode() + "-" + GetCityCode() + "-" + GetLocalNumber();
}