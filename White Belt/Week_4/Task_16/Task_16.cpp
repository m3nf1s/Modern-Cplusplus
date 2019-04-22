/*
Итак, теперь у нас с вами есть полноценный тип для представления обыкновенных дробей:
класс Rational интегрирован в язык с помощью перегрузки операторов и не позволяет выполнять
некорректные операции за счёт выбрасывания исключений.
Давайте на основе класса Rational создадим простой калькулятор для обыкновенных дробей.

Вам надо написать программу, которая считывает из стандартного ввода одну строку в формате
ДРОБЬ_1 операция ДРОБЬ_2. ДРОБЬ_1 и ДРОБЬ_2 имеют формат X/Y, 
где X — целое, а Y — целое неотрицательное число. операция — это один из символов '+', '-', '*', '/'.

Если ДРОБЬ_1 или ДРОБЬ_2 является некорректной обыкновенной дробью,
ваша программа должна вывести в стандартный вывод сообщение "Invalid argument".
Если считанная операция — это деление на ноль, выведите в стандартный вывод сообщение "Division by zero".
В противном случае выведите результат операции.
*/

#include "pch.h"
#include <iostream>
#include <string>
#include <exception>
#include <cmath>

class Rational
{
public:
	Rational()
	{
		_numerator = 0;
		_denominator = 1;
	}
	Rational(const int numerator, const int denominator)
	{
		if (denominator == 0)
		{
			throw std::invalid_argument("Invalid argument");
		}

		const int GCD = FindGCD(numerator, denominator);

		if (numerator > 0 && denominator < 0 || numerator < 0 && denominator < 0)
		{
			_numerator = -numerator / GCD;
			_denominator = -denominator / GCD;
		}
		else
		{
			_numerator = numerator / GCD;
			_denominator = denominator / GCD;
		}
	}

	int GetNumerator() const
	{
		return _numerator;
	}

	int GetDenominator() const
	{
		return _denominator;
	}

private: 
	int _numerator;
	int _denominator;

	int FindGCD(int numerator, int denominator) const
	{
		numerator = abs(numerator);
		denominator = abs(denominator);

		while (numerator > 0 && denominator > 0)
		{
			if (numerator > denominator)
			{
				numerator %= denominator;
			}
			else
			{
				denominator %= numerator;
			}
		}

		return numerator + denominator;
	}
};

Rational operator+ (const Rational& lhs, const Rational& rhs)
{
	if (lhs.GetDenominator() == rhs.GetDenominator())
		return { lhs.GetNumerator() + rhs.GetNumerator(), lhs.GetDenominator() };

	return { lhs.GetNumerator() * rhs.GetDenominator() + rhs.GetNumerator() * lhs.GetDenominator(), lhs.GetDenominator() *rhs.GetDenominator() };
}

Rational operator- (const Rational& lhs, const Rational& rhs)
{
	if (lhs.GetDenominator() == rhs.GetDenominator())
		return { lhs.GetNumerator() - rhs.GetNumerator(), lhs.GetDenominator() };

	return { lhs.GetNumerator() * rhs.GetDenominator() - rhs.GetNumerator() * lhs.GetDenominator(), lhs.GetDenominator() * rhs.GetDenominator() };
}

Rational operator* (const Rational& lhs, const Rational& rhs)
{
	return { lhs.GetNumerator() * rhs.GetNumerator(), lhs.GetDenominator() * rhs.GetDenominator() };
}

Rational operator/ (const Rational& lhs, const Rational& rhs)
{
	const int numerator = lhs.GetNumerator() * rhs.GetDenominator();
	const int denominator = rhs.GetNumerator() * lhs.GetDenominator();

	if (denominator == 0)
		throw std::domain_error("Division by zero");

	return { numerator, denominator };
}

std::istream& operator>> (std::istream& stream, Rational& obj)
{
	if(stream.good())
	{
		int numerator = 0;
		int denominator = 0;
		stream >> numerator;
		if (stream.peek() != '/')
			throw std::invalid_argument("/");
		stream.ignore(1);
		stream >> denominator;

		obj = { numerator, denominator };
	}

	return stream;
}

std::ostream& operator<< (std::ostream& stream, Rational& obj)
{
	stream << obj.GetNumerator() << "/" << obj.GetDenominator();

	return stream;
}

int main()
{
	try
	{
		Rational r1, r2;
		char oper;

		std::cin >> r1 >> oper >> r2;

		if(oper == '+')
		{
			Rational result = r1 + r2;
			std::cout << result << std::endl;
		}
		else if(oper == '-')
		{
			Rational result = r1 - r2;
			std::cout << result << std::endl;
		}
		else if(oper == '*')
		{
			Rational result = r1 * r2;
			std::cout << result << std::endl;
		}
		else if(oper=='/')
		{
			Rational result = r1 / r2;
			std::cout << result << std::endl;
		}
	}
	catch (std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}
}