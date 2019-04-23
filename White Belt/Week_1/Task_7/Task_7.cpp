/* Дана строка.
 * Найдите в этой строке второе вхождение буквы f и выведите индекс этого вхождения.
 * Если буква f в данной строке встречается только один раз, выведите число -1, а если не встречается ни разу, выведите число -2.
 * Индексы нумеруются с нуля.
 */

#include "pch.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
	string word;
	cin >> word;
	int itr = 0;
	int buff;
	for (int i = 0; i < word.size(); i++)
	{
		if (word[i] == 'f')
		{
			itr++;
			if (itr == 2)
			{
				buff = i;
				break;
			}
		}
	}

	if (itr == 2)
		cout << buff << endl;
	else
		if (itr == 1)
			cout << -1 << endl;
		else
			cout << -2 << endl;
		
	return 0;
}