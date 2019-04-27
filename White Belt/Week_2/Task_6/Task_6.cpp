/*
 * Реализуйте функцию void Reverse(vector<int>& v), которая переставляет элементы вектора в обратном порядке.
 */
 
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void ReverseV1 (vector<int>& v)
{
	for (int i = 0; i < v.size() / 2 ; i++)
	{
		int buff = v[i];
		v[i] = v[v.size() - i - 1];
		v[v.size() - i - 1] = buff;
	}
}

void ReverseV2 (vector<int>& v)
{
	vector<int> buff;
	for (int i = v.size() - 1; i >= 0; i--)
		buff.push_back(v[i]);
	v.clear();
	v = buff;
}

int main()
{
	vector<int> test = { 1, 2, 3, 4, 5, 6, 7, 8, 9};
	ReverseV1 (test);

	for (auto n : test)
		cout << n << " ";

	cout << endl;

	ReverseV2(test);

	for (auto n : test)
		cout << n << " ";
}