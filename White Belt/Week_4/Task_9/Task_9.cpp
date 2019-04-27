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

Часть 1

В первой части вам надо реализовать класс Rational, который представляет собой рациональное число вида p/q,
где p целое, а q натуральное. Он должен иметь следующий интерфейс:

	class Rational {
	public:
	  Rational();
	  Rational(int numerator, int denominator);

	  int Numerator() const;
	  int Denominator() const;
	};

Класс Rational должен гарантировать, что p/q — это несократимая дробь. 
Список требований, предъявляемых к реализации интерфейса класса Rational:

- Конструктор по умолчанию должен создавать дробь с числителем 0 и знаменателем 1.
- При конструировании объека класса Rational с параметрами p и q должно выполняться сокращение дроби p/q
	(здесь вам может пригодиться решение задачи «Наибольший общий делитель»).
- Если дробь p/q отрицательная, то объект Rational(p, q) должен иметь отрицательный числитель и положительный знаменатель.
- Если дробь p/q положительная, то объект Rational(p, q) должен иметь положительные числитель и знаменатель
	(обратите внимание на случай Rational(-2, -3)).
- Если числитель дроби равен нулю, то знаменатель должен быть равен 1.
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