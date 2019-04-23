/* На вход дано целое положительное число N.
 * Выведите его в двоичной системе счисления без ведущих нулей.
 */

#include "pch.h"
#include <iostream>
#include <vector>

using namespace std;

int main()
{
	vector<int> vec;
	int number;
	string a;

	cin >> number;

	while (number != 0)
	{
		vec.push_back(number % 2);
		number /= 2;
	}

	for (int i = vec.size() - 1; i >= 0; i--)
	{
		cout << vec[i];
	}

	return 0;
}