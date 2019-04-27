/*
 * Реализуйте функцию vector<int> Reversed(const vector<int>& v), возвращающую копию вектора v, в которой числа переставлены в обратном порядке.
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> Reversed(const vector<int>& v)
{
	vector<int> buff;
	for (int i = v.size() - 1; i >= 0; i--)
		buff.push_back(v[i]);
	return buff;
}

int main()
{
	vector<int> test = { 1, 5, 3, 4, 2 };
	vector<int> simple = Reversed(test);

	for (auto n : simple)
		cout << n << " ";
}