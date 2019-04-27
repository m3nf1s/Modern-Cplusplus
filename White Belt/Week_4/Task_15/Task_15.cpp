/*
Вспомним класс Rational, который мы реализовали в задачах, посвящённых перегрузке операторов.
Там специально говорилось, что в тестах объекты класса Rational никогда не создаются
с нулевым знаменателем и никогда не выполняется деление на ноль.
Настало время избавиться от этого ограничения и научиться обрабатывать нулевой знаменательи деление на ноль.
В этой задаче вам предстоит это сделать.

Поменяйте реализацию конструктора класса Rational так, чтобы он выбрасывал исключение invalid_argument,
если знаменатель равен нулю. Кроме того, переделайте реализацию оператора деления для класса Rational так,
чтобы он выбрасывал исключение domain_error, если делитель равен нулю.

Напомним, что вам надо реализовать интерфейс
class Rational {
public:
  Rational();
  Rational(int numerator, int denominator);

  int Numerator() const;
  int Denominator() const;
};

и оператор деления для класса Rational
Rational operator / (const Rational& lhs, const Rational& rhs);
*/

#include <iostream>
#include <exception>

using namespace std;

class Rational 
{
public:
	Rational(int numerator, int denominator)
	{
		if (denominator == 0)
		{
			throw invalid_argument("invalid_argument");
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

Rational operator / (const Rational& lhs, const Rational& rhs)
{
	int new_numerator = lhs.Numerator() * rhs.Denominator();
	int new_denominator = rhs.Numerator() * lhs.Denominator();

	if (new_denominator == 0)
		throw domain_error("domain_error");


	return Rational(new_numerator, new_denominator);
}

int main() 
{
	try 
	{
		Rational r(1, 0);
		cout << "Doesn't throw in case of zero denominator" << endl;
		return 1;
	}
	catch (invalid_argument&) {
	}

	try {
		auto x = Rational(1, 2) / Rational(0, 1);
		cout << "Doesn't throw in case of division by zero" << endl;
		return 2;
	}
	catch (domain_error&) {
	}

	cout << "OK" << endl;
	return 0;
}