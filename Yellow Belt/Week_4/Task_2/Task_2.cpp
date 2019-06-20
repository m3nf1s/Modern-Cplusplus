/*
Напишите шаблонную функцию FindGreaterElements,
	принимающую множество elements объектов типа T и ещё один объект border типа T и возвращающую вектор из всех элементов множества,
	бо́льших border, в возрастающем порядке.
*/

#include <iostream>
#include "FindGreaterElements.h"

int main() {
	for (int x : FindGreaterElements(std::set<int>{1, 5, 7, 8}, 5)) {
		std::cout << x << " ";
	}
	std::cout << std::endl;

	for (int x : FindGreaterElements(std::set<int>{1, 5, 7, 8}, 0)) {
		std::cout << x << " ";
	}
	std::cout << std::endl;

	std::string to_find = "Python";
	std::cout << FindGreaterElements(std::set<std::string>{"C", "C++"}, to_find).size() << std::endl;
	return 0;
}