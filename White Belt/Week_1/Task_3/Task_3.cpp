/*
 * На вход вашей программе в стандартном вводе даны действительные коэффициенты A, B и C уравнения Ax² + Bx + C = 0.
 * Выведите все его различные действительные корни в любом порядке.
 * Гарантируется, что хотя бы один из коэффициентов не равен нулю.
 */

#include "pch.h"
#include <iostream>
#include <cmath>

using namespace std;

int main()
{
	double a, b, c;

	cin >> a >> b >> c;

	if (a != 0)
	{
		const double D = sqrt(pow(b, 2) - 4 * a * c);

		if (D > 0)
			cout << (-b + D) / (2 * a) << ' ' << (-b - D) / (2 * a) << endl;
		else
			if (D == 0)
				cout << (-b - D) / (2 * a) << endl;
	}
	else
	{
		if (b != 0)
			cout << -c / b << endl;
	}

	return 0;
}