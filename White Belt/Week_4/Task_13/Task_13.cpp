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

Часть 5
Наконец, вам нужно реализовать возможность использовать объекты класса Rational
	в качестве элементов контейнера set и ключей в контейнере map.
*/

#include "pch.h"
#include <iostream>
#include <sstream>
#include <map>
#include <set>
#include <vector>

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
	return (((double)one.Numerator() / one.Denominator()) == ((double)two.Numerator() / two.Denominator()));
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

ostream& operator<<(ostream& stream, const Rational& obj)
{
	stream << obj.Numerator() << '/' << obj.Denominator();

	return stream;
}

bool operator< (const Rational& obj_one, const Rational& obj_two)
{
	return ((double)obj_one.Numerator() / obj_one.Denominator()) < ((double)obj_two.Numerator() / obj_two.Denominator());
}

int main() {
	{
		const set<Rational> rs = { {1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2} };
		if (rs.size() != 3) {
			cout << "Wrong amount of items in the set " << rs.size() << endl;
			return 1;
		}

		vector<Rational> v;
		for (auto x : rs) {
			v.push_back(x);
		}
		if (v != vector<Rational>{ {1, 25}, { 1, 2 }, { 3, 4 }}) {
			cout << "Rationals comparison works incorrectly" << endl;
			return 2;
		}
	}

	{
		map<Rational, int> count;
		++count[{1, 2}];
		++count[{1, 2}];

		++count[{2, 3}];

		if (count.size() != 2) {
			cout << "Wrong amount of items in the map" << endl;
			return 3;
		}
	}

	cout << "OK" << endl;
	return 0;
}