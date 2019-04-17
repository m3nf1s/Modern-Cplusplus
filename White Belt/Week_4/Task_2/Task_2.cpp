#include "pch.h"
#include <iostream>
#include <vector>

/*
Реализуйте рассказанный на лекции класс Function, позволяющий создавать,
вычислять и инвертировать функцию, состоящую из следующих элементарных операций:

* прибавить вещественное число x;
* вычесть вещественное число x.
При этом необходимо объявить константными все методы, которые по сути такими являются.
*/

struct Image
{
	double quality; 
	double freshness; 
	double rating;
};

struct Params
{
	double a;
	double b;
	double c;
};

class FunctionPart
{
public:
	FunctionPart(char new_operation, double new_value)
	{
		operation = new_operation;
		value = new_value;
	}

	double Apply(double source_value) const
	{
		if (operation == '+')
			return source_value + value;
		else
			return source_value - value;
	}

	void Invert()
	{
		if (operation == '+')
			operation = '-';
		else
			operation = '+';
	}
private:
	char operation;
	double value;
};

class Function
{
public:
	void AddPart(char operation, double value)
	{
		parts.push_back({ operation, value });
	}

	double Apply(double value) const
	{
		for (const FunctionPart& part : parts)
		{
			value = part.Apply(value);
		}
		return value;
	}

	void Invert()
	{
		for (FunctionPart& part : parts)
		{
			part.Invert();
		}
		std::reverse(parts.begin(), parts.end());
	}
private:
	std::vector<FunctionPart> parts; 
};

Function ComputerWeightFunction(const Params& params, const Image& image)
{
	Function function;
	function.AddPart('-', image.freshness * params.a + params.b);
	function.AddPart('+', image.rating * params.c);
	return function;
}

double ComputeImageWeight(const Params& params, const Image& image)
{
	Function function = ComputerWeightFunction(params, image);
	return function.Apply(image.quality);
}

double ComputeQualityByWeight(const Params& params, const Image& image, double weight)
{
	Function function = ComputerWeightFunction(params, image);
	function.Invert();
	return function.Apply(weight);
}

int main()
{
	Image image = { 10, 2, 6 };
	Params params = { 4, 2, 6 };
	std::cout << ComputeImageWeight(params, image) << std::endl;
	std::cout << ComputeQualityByWeight(params, image, 46) << std::endl;
	return 0;
}