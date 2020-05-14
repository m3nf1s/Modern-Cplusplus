/* На вход дано целое положительное число N.
 * Выведите его в двоичной системе счисления без ведущих нулей.
 */

#include <iostream>
#include <vector>

int main()
{
	int number;
	std::cin >> number;
	size_t bits { 0 };

	for(int temp = number; temp != 0; temp /= 2)
	{
		++bits;
	}

	std::vector<int> binary_number(bits);

	for(size_t i = 0; i < binary_number.size(); ++i, number /= 2)
	{
		binary_number[i] = number % 2;
	}
	
	for(auto it = binary_number.crbegin(); it != binary_number.crend(); ++it)
	{
		std::cout << *it;
	}
}