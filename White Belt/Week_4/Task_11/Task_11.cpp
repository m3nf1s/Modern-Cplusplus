﻿/*
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

Часть 3

Аналогично предыдущей части, реализуйте операторы * и /.
*/

#include <iostream>

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

int main() {
	{
		Rational a(2, 3);
		Rational b(4, 3);
		Rational c = a * b;
		bool equal = c == Rational(8, 9);
		if (!equal) {
			cout << "2/3 * 4/3 != 8/9" << endl;
			return 1;
		}
	}

	{
		Rational a(5, 4);
		Rational b(15, 8);
		Rational c = a / b;
		bool equal = c == Rational(2, 3);
		if (!equal) {
			cout << "5/4 / 15/8 != 2/3" << endl;
			return 2;
		}
	}

	cout << "OK" << endl;
	return 0;
}