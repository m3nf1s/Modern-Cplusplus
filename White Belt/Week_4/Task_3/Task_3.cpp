#include "pch.h"
#include <iostream>
#include <vector>

/*
Добавьте в класс Function из задачи «Обратимая функция» обработку умножения ('*') и деления ('/').
Гарантируется отсутствие элементарных операций умножения и деления на 0.
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
		else if (operation == '-')
			return source_value - value;
		else if (operation == '*')
			return source_value * value;
		else
			return source_value / value;
	}
	void Invert()
	{
		if (operation == '+')
			operation = '-';
		else if (operation == '-')
			operation = '+';
		else if (operation == '*')
			operation = '/';
		else
			operation = '*';
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

Function MakeWeightFunction(const Params& params, const Image& image)
{
	Function function;
	function.AddPart('*', params.a);
	function.AddPart('-', image.freshness * params.b);
	function.AddPart('+', image.rating *params.c);
	return function;
}

double ComputeImageWeight(const Params& params, const Image& image)
{
	Function function = MakeWeightFunction(params, image);
	return function.Apply(image.quality);
}

double ComputeQualityByWeight(const Params& params, const Image& image, double weight)
{
	Function function = MakeWeightFunction(params, image);
	function.Invert();
	return function.Apply(weight);
}

int main()
{
	Image image = { 10, 2, 6 };
	Params params = { 4, 2, 6 };
	std::cout << ComputeImageWeight(params, image) << std::endl;
	std::cout << ComputeQualityByWeight(params, image, 52) << std::endl;
	return 0;
}