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
#include <sstream>

class Rational
{
public:
	Rational(const int numerator, const int denominator)
	{
		if (denominator == 0)
		{
			throw std::invalid_argument("Invalid argument");
		}
		else
		{
			int GCD = FindGCD(numerator, denominator);

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

	int FindGCD(int numerator, int denominator)
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

Rational operator + (const Rational& one, const Rational& two)
{
	if (one.GetDenominator() == two.GetDenominator())
	{
		return Rational(one.GetNumerator() + two.GetNumerator(), one.GetDenominator());
	}

	return Rational(one.GetNumerator() * two.GetDenominator() + two.GetNumerator() * one.GetDenominator(), one.GetDenominator() * two.GetDenominator());
}

Rational operator - (const Rational& one, const Rational& two)
{
	if (one.GetDenominator() == two.GetDenominator())
	{
		return Rational(one.GetNumerator() - two.GetNumerator(), one.GetDenominator());
	}

	return Rational(one.GetNumerator() * two.GetDenominator() - two.GetNumerator() * one.GetDenominator(), one.GetDenominator() * two.GetDenominator());
}

Rational operator * (const Rational& one, const Rational& two)
{
	return Rational(one.GetNumerator() * two.GetNumerator(), one.GetDenominator() * two.GetDenominator());
}

Rational operator / (const Rational& lhs, const Rational& rhs)
{
	int new_numerator = lhs.GetNumerator() * rhs.GetDenominator();
	int new_denominator = rhs.GetNumerator() * lhs.GetDenominator();

	if (new_denominator == 0)
		throw std::domain_error("domain_error");


	return Rational(new_numerator, new_denominator);
}

std::istream& operator >>(std::istream& stream, Rational& obj)
{
	if (stream)
	{
		int numerator = 0;
		int denominator = 0;
		stream >> numerator;
		stream.ignore(1);
		stream >> denominator;

		obj = { numerator, denominator };
	}

	return stream;
}

std::ostream& operator <<(std::ostream& stream, const Rational& obj)
{
	stream << obj.GetNumerator() << '/' << obj.GetDenominator();

	return stream;
}

int main()
{
	{
		Rational r1(1, 2), r2(1, 3);
		std::cout << r1 + r2 << std::endl;
	}

	{
		try
		{
			Rational r1(1, 2), r2(5, 0);
			std::cout << r1 + r2 << std::endl;
		}
		catch (const std::invalid_argument& ex)
		{
			ex.what();
		}
	}

	{
		try
		{
			Rational r1(4, 5), r2(0, 8);
			std::cout << r1 / r2 << std::endl;
		}
		catch (const std::domain_error& ex)
		{
			ex.what();
		}
	}
}
