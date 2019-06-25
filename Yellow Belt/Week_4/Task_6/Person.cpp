#include <vector>
#include <iostream>
#include "Person.h"
#include "ComputeMedianAge.h"

void PrintStats(std::vector<Person> persons)
{
	auto female_end = std::partition(std::begin(persons), std::end(persons),
		[](const Person& person)
		{
			return person.gender == Gender::FEMALE;
		});

	auto female_empl = std::partition(std::begin(persons), female_end,
		[](const Person& person)
		{
			return person.is_employed == true;
		});

	auto male_empl = std::partition(female_end, std::end(persons),
		[](const Person& person)
		{
			return person.is_employed == true;
		});

	std::cout << "Median age = " << ComputeMedianAge(std::begin(persons), std::end(persons)) << std::endl;
	std::cout << "Median age for females = " << ComputeMedianAge(std::begin(persons), female_end) << std::endl;
	std::cout << "Median age for males = " << ComputeMedianAge(female_end, std::end(persons)) << std::endl;

	std::cout << "Median age for employed females = " << ComputeMedianAge(std::begin(persons), female_empl) << std::endl;
	std::cout << "Median age for unemployed females = " << ComputeMedianAge(female_empl, female_end) << std::endl;
	std::cout << "Median age for employed males = " << ComputeMedianAge(female_end, male_empl) << std::endl;
	std::cout << "Median age for unemployed males = " << ComputeMedianAge(male_empl, std::end(persons)) << std::endl;
}