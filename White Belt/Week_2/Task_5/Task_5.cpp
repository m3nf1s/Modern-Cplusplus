/* Напишите функцию MoveStrings, которая принимает два вектора строк, source и destination, и дописывает все строки из первого вектора в конец второго.
 * После выполнения функции вектор source должен оказаться пустым.
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

void MoveStrings(vector<string>& source, vector<string>& destination)
{
	for (auto w : source)
		destination.push_back(w);

	source.clear();
}

int main()
{
	vector<string> first = { "qwe", "rty", "asd", "fgh" };
	vector<string> second = { "keyboard: " };
	MoveStrings(first, second);

	cout << "first - ";
	for (auto w : first)
		cout <<  w ;

	cout << endl;

	cout << "second - ";
	for (auto w : second)
		cout << w;
}