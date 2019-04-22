/*
В этой задаче вам надо разработать класс для представления рациональных чисел и внедрить его в систему типов языка С++ так,
чтобы им можно было пользоваться естественным образом Задание состоит из нескольких частей.
К каждой части приложен файл с заготовкой программы, который имеет следующую структуру

Вам нужно, не меняя тело функции main, реализовать то, что предложено в комментариях, так,
чтобы ваша программа выводила на экран сообщение OK.
Функция main содержит ряд юнит-тестов, которые проверяют правильность вашей реализации.
Если эти тесты находят ошибку в вашей реализации, то вместо OK программа выведет подсказку о том, что именно работает неправильно.

Когда ваша программа начнёт выводить OK, можете отправлять свой файл на проверку.
Ваша реализация будет тестироваться на другом, более полном наборе тестов.
То есть, если ваша программа выводит OK, то это не даёт гарантии, что ваша реализация будет принята тестирующей системой.
В случае неудачной посылки тестирующая система также выдаст вам подсказку о том, какая именно часть реализации работает неправильно.

Внимательно изучите набор юнит-тестов для каждой заготовки решения.
Тесты описывают требования, предъявляемые к вашей реализации, которые могут быть не указаны в условии задач

На проверку можно отправлять весь файл с вашей реализацией: функцию main удалять из него не нужно.

Часть 4
В этой части вам нужно реализовать операторы ввода и вывода для класса Rational.
*/

#include "pch.h"
#include <iostream>
#include <sstream>

using namespace std;

class Rational
{
public:
	Rational()
	{
		Init();
	}

	Rational(const int numerator, const int denominator)
	{
		if (numerator == 0)
		{
			Init();
		}
		else
		{
			int GCD = FindGCD(numerator, denominator);

			if ((numerator > 0 && denominator < 0) || (numerator < 0 && denominator < 0))
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

	int Numerator() const
	{
		return _numerator;
	}

	int Denominator() const
	{
		return _denominator;
	}

private:
	int _numerator;
	int _denominator;

	void Init()
	{
		_numerator = 0;
		_denominator = 1;
	}

	int FindGCD(int numerator, int denominator)
	{
		numerator = abs(numerator);
		denominator = abs(denominator);
		while (numerator > 0 && denominator > 0)
		{
			if (numerator > denominator)
				numerator %= denominator;
			else
				denominator %= numerator;
		}

		return numerator + denominator;
	}
};

bool operator== (const Rational& one, const Rational& two)
{
	return ((double)one.Numerator() / one.Denominator()) == ((double)two.Numerator() / two.Denominator());
}

Rational operator+ (const Rational& one, const Rational& two)
{
	if (one.Denominator() == two.Denominator())
	{
		return Rational(one.Numerator() + two.Numerator(), one.Denominator());
	}

	return Rational(one.Numerator() * two.Denominator() + two.Numerator() * one.Denominator(), one.Denominator() * two.Denominator());
}

Rational operator- (const Rational& one, const Rational& two)
{
	if (one.Denominator() == two.Denominator())
	{
		return Rational(one.Numerator() - two.Numerator(), one.Denominator());
	}

	return Rational(one.Numerator() * two.Denominator() - two.Numerator() * one.Denominator(), one.Denominator() * two.Denominator());
}

Rational operator* (const Rational& one, const Rational& two)
{
	return Rational(one.Numerator() * two.Numerator(), one.Denominator() * two.Denominator());
}

Rational operator/ (const Rational& one, const Rational& two)
{
	return Rational(one.Numerator() * two.Denominator(), two.Numerator() * one.Denominator());
}

istream& operator>>(istream& stream, Rational& obj)
{
	if (stream.good())
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

ostream& operator<<(ostream& stream, const Rational& obj)
{
	stream << obj.Numerator() << '/' << obj.Denominator();

	return stream;
}

int main() {
	{
		ostringstream output;
		output << Rational(-6, 8);
		if (output.str() != "-3/4") {
			cout << "Rational(-6, 8) should be written as \"-3/4\"" << endl;
			return 1;
		}
	}

	{
		istringstream input("5/7");
		Rational r;
		input >> r;
		bool equal = r == Rational(5, 7);
		if (!equal) {
			cout << "5/7 is incorrectly read as " << r << endl;
			return 2;
		}
	}

	{
		istringstream input("5/7 5/4");
		Rational r1, r2;
		input >> r1 >> r2;
		bool correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
		if (!correct) {
			cout << "Multiple values are read incorrectly: " << r1 << " " << r2 << endl;
			return 3;
		}

		input >> r1;
		input >> r2;
		correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
		if (!correct) {
			cout << "Read from empty stream shouldn't change arguments: " << r1 << " " << r2 << endl;
			return 4;
		}
	}

	cout << "OK" << endl;
	return 0;
}