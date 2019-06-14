/*
Вам дан заголовочный файл phone_number.h, содержащий объявление класса PhoneNumber.
При этом в комментариях описано поведение, которое ожидается от реализации этого класса.


*/

#include <iostream>
#include "phone_number.h"
#include "UnitFramework.h"
#include "UnitTests.h"

int main()
{
	UnitFramework uf;
	uf.RunTest(TestCorrectNumber, "Correct number");
	uf.RunTest(TestCountyCode, "Contry Code");
	uf.RunTest(TestCityCode, "City Code");
	uf.RunTest(TestLocalNumber, "Local Numbers");
	
	
	//PhoneNumber pn("+7-495-2387858");
	//std::cout << pn.GetInternationalNumber() << ": " << pn.GetCountryCode() << " " << pn.GetCityCode() << " " << pn.GetLocalNumber() << std::endl;
}