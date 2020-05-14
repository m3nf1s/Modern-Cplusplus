/* Напишите функцию MoveStrings, которая принимает два вектора строк, source и destination, и дописывает все строки из первого вектора в конец второго.
 * После выполнения функции вектор source должен оказаться пустым.
 */

#include <iostream>
#include <vector>

void MoveStrings(std::vector<std::string>& source, std::vector<std::string>& destination)
{
	destination.reserve(destination.size() + source.size());
	std::move(source.begin(), source.end(), std::back_inserter(destination));
	source.clear();
}

int main()
{
	std::vector<std::string> first = { "qwe", "rty", "asd", "fgh" };
	std::vector<std::string> second = { "keyboard: " };
	MoveStrings(first, second);

	std::cout << "first - ";
	for (const auto& word : first)
	{
		std::cout <<  word ;
	}

	std::cout << std::endl;

	std::cout << "second - ";
	for (const auto& word : second)
	{
		std::cout << word;
	}
}