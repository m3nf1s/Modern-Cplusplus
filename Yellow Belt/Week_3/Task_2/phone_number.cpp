#include "phone_number.h"

explicit PhoneNumber::PhoneNumber(const std::string& international_number)
{
	
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