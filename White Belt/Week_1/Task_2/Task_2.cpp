/*
 * В стандартном потоке даны три строки, разделённые пробелом.
 * Каждая строка состоит из строчных латинских букв и имеет длину не более 30 символов.
 * Выведите в стандартный вывод лексикографически минимальную из них.
 */
 
#include <iostream>
#include <string>

using namespace std;

int main()
{
	string a, b, c;
	cin >> a >> b >> c;

	if (a < b)
	{
		if (a < c)
			cout << a << endl;
		else
			cout << c << endl;
	}
	else
	{
		if (b < c)
			cout << b << endl;
		else
			cout << c << endl;
	}

	return 0;
}