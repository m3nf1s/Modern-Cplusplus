// Task_9.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
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
			int NOD = FindNOD(numerator, denominator);

			if ((numerator > 0 && denominator < 0) || (numerator < 0 && denominator < 0))
			{
				numer = - (numerator / NOD);
				denom = - (denominator / NOD);
			}
			else
			{
				numer = numerator / NOD;
				denom = denominator / NOD;
			}
		}
	}

	int Numerator() const
	{
		return numer;
	}

	int Denominator() const
	{
		return denom;
	}

private:
	int numer;
	int denom;

	void Init()
	{
		numer = 0;
		denom = 1;
	}
	
	int FindNOD(int numerator, int denominator) const
	{
		numerator = std::abs(numerator);
		denominator = std::abs(denominator);

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

int main()
{
	{
		const Rational r(3, 10);
		if (r.Numerator() != 3 || r.Denominator() != 10)
		{
			cout << "Rational(3, 10) != 3/10" << endl;
			return 1;
		}
	}

	{
		const Rational r(8, 12);
		if (r.Numerator() != 2 || r.Denominator() != 3)
		{
			cout << "Rational(8, 12) != 2/3" << endl;
			return 2;
		}
	}

	{
		const Rational r(-4, 6);
		if (r.Numerator() != -2 || r.Denominator() != 3)
		{
			cout << "Rational(-4, 6) != -2/3" << endl;
			return 3;
		}
	}

	{
		const Rational r(4, -6);
		if (r.Numerator() != -2 || r.Denominator() != 3)
		{
			cout << "Rational(4, -6) != -2/3" << endl;
			return 3;
		}
	}

	{
		const Rational r(0, 15);
		if (r.Numerator() != 0 || r.Denominator() != 1)
		{
			cout << "Rational(0, 15) != 0/1" << endl;
			return 4;
		}
	}

	{
		const Rational defaultConstructed;
		if (defaultConstructed.Numerator() != 0 || defaultConstructed.Denominator() != 1)
		{
			cout << "Rational() != 0/1" << endl;
			return 5;
		}
	}

	cout << "OK" << endl;
	return 0;
}