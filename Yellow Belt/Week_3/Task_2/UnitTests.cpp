#include "UnitTests.h"
#include "UnitFramework.h"
#include "phone_number.h"

void TestCorrectNumber()
{
	{
		PhoneNumber pn("+7-495-111-22-33");
		AssertEqual(pn.GetInternationalNumber(), "+7-945-111-22-33", "+7-495-111-22-33 != +7-945-111-22-33");
	}

	{
		PhoneNumber pn("+7-495-1112233");
		AssertEqual(pn.GetInternationalNumber(), "+7-945-1112233", "+7-945-1112233 != +7-945-1112233");

	}

	{
		PhoneNumber pn("+323-22-460002");
		AssertEqual(pn.GetInternationalNumber(), "+323-22-460002", "+323-22-460002 != +323-22-460002");

	}

	{
		PhoneNumber pn("+1-2-coursera-cpp");
		AssertEqual(pn.GetInternationalNumber(), "+1-2-courseracpp", "+1-2-coursera-cpp != +1-2-courseracpp");

	}

	//{
	//	PhoneNumber pn("1-2-333");
	//	AssertEqual(pn.GetInternationalNumber(), "+7-945-1112233", "+7-495-111-22-33 != +7-945-1112233");

	//}

	//{
	//	PhoneNumber pn("+7-1233");
	//	AssertEqual(pn.GetInternationalNumber(), "+7-945-1112233", "+7-495-111-22-33 != +7-945-1112233");

	//}
}

void TestCountyCode()
{
	{
		PhoneNumber pn("+7-495-111-22-33");
		AssertEqual(pn.GetCountryCode(), "7", "Country Code : +7-495-111-22-33 != 7");
	}

	{
		PhoneNumber pn("+7-495-1112233");
		AssertEqual(pn.GetCountryCode(), "7", "Country Code : +7-945-1112233 != 7");
	}

	{
		PhoneNumber pn("+323-22-460002");
		AssertEqual(pn.GetCountryCode(), "323", "Country Code : +323-22-460002 != 323");
	}

	{
		PhoneNumber pn("+1-2-coursera-cpp");
		AssertEqual(pn.GetCountryCode(), "1", "Country Code : +1-2-coursera-cpp != 1");
	}
}

void TestCityCode()
{
	{
		PhoneNumber pn("+7-495-111-22-33");
		AssertEqual(pn.GetCityCode(), "495", "City Code: +7-495-111-22-33 != 495");
	}

	{
		PhoneNumber pn("+7-495-1112233");
		AssertEqual(pn.GetCityCode(), "495", "City Code: +7-945-1112233 != 495");
	}

	{
		PhoneNumber pn("+323-22-460002");
		AssertEqual(pn.GetCityCode(), "22", "City Code: +323-22-460002 != 22");
	}

	{
		PhoneNumber pn("+1-2-coursera-cpp");
		AssertEqual(pn.GetCityCode(), "2", "City Code: +1-2-coursera-cpp != 22");
	}
}

void TestLocalNumber()
{
	{
		PhoneNumber pn("+7-495-111-22-33");
		AssertEqual(pn.GetLocalNumber(), "111-22-33", "+7-495-111-22-33 != 111-22-33");
	}

	{
		PhoneNumber pn("+7-495-1112233");
		AssertEqual(pn.GetLocalNumber(), "1112233", "+7-945-1112233 != 1112233");

	}

	{
		PhoneNumber pn("+323-22-460002");
		AssertEqual(pn.GetLocalNumber(), "460002", "+323-22-460002 != 460002");

	}

	{
		PhoneNumber pn("+1-2-coursera-cpp");
		AssertEqual(pn.GetLocalNumber(), "courseracpp", "+1-2-coursera-cpp != courseracpp");

	}
}