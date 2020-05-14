/*
 * В стандартном потоке даны три строки, разделённые пробелом.
 * Каждая строка состоит из строчных латинских букв и имеет длину не более 30 символов.
 * Выведите в стандартный вывод лексикографически минимальную из них.
 */
 
#include <iostream>
#include <algorithm>

int main()
{
	std::string word1, word2, word3;
	std::cin >> word1 >> word2 >> word3;

	std::cout << std::min({ word1, word2, word3 });
}