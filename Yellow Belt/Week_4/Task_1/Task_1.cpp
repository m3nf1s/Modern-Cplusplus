/*
Напишите функцию PrintVectorPart, принимающую вектор целых чисел numbers,
	выполняющую поиск первого отрицательного числа в нём и выводящую в стандартный вывод все числа,
	расположенные левее найденного, в обратном порядке.
Если вектор не содержит отрицательных чисел, выведите все числа в обратном порядке.
*/

#include <iostream>
#include <vector>
#include <algorithm>

void PrintVectorPart(const std::vector<int>& numbers)
{
	auto it = std::find_if(numbers.begin(), numbers.end(), [](int x)
		{
			return x < 0;
		});

	while (it != numbers.begin())
	{
		--it;
		std::cout << *it << ' ';
	}
}

int main()
{
	PrintVectorPart({ 6, 1, 8, -5, 4 });
	std::cout << std::endl;
	PrintVectorPart({ -6, 1, 8, -5, 4 });  // ничего не выведется
	std::cout << std::endl;
	PrintVectorPart({ 6, 1, 8, 5, 4 });
	std::cout << std::endl;
	return 0;
}