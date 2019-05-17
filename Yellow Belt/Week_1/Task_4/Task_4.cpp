/*

*/

#include <iostream>
#include <limits>

int main()
{
	int min = std::numeric_limits<size_t>::min();
	std::cout << min;
}