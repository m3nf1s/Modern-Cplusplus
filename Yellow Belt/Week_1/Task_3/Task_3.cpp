/*
Вычислите суммарную массу имеющих форму прямоугольного параллелепипеда бетонных блоков одинаковой плотности, но разного размера.

Указание
Считайте, что размеры блоков измеряются в сантиметрах, плотность — в граммах на кубический сантиметр,
а итоговая масса — в граммах. Таким образом, массу блока можно вычислять как простое произведение плотности на объём.

Формат ввода
В первой строке вводятся два целых положительных числа: количество блоков N и плотность каждого блока R.
Каждая из следующих N строк содержит три целых положительных числа W, H, D — размеры очередного блока.

Гарантируется, что:

количество блоков N не превосходит 10^5;
плотность блоков R не превосходит 100;
размеры блоков W, H, D не превосходят 10^4.
*/

#include <iostream>
#include <vector>
#include <cstdint>

class Block
{
public:
	Block(const uint64_t new_width, const uint64_t new_height, const uint64_t new_length)
	{
		_width = new_width;
		_height = new_height;
		_length = new_length;
	}

	uint64_t Squad()
	{
		return _width * _height* _length;
	}
private:
	uint64_t _width;
	uint64_t _height;
	uint64_t _length;
};

int main()
{
	uint64_t count{};
	uint64_t density{};
	std::cin >> count >> density;

	std::vector<Block> blocks;

	for (size_t i = 0; i < count; i++)
	{
		uint64_t new_width{}, new_height{}, new_length{};
		std::cin >> new_width >> new_height >> new_length;

		blocks.push_back({ new_width, new_height, new_length });
	}

	uint64_t mass{ 0 };

	for (Block& bl : blocks)
	{
		mass += bl.Squad() * density;
	}

	std::cout << mass << std::endl;
}