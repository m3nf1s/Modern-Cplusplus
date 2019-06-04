/*
Реализуйте шаблонную функцию Sqr, которая работает не только для чисел, но и для контейнеров.
Функция должна возвращать копию исходного контейнера, модифицировав его следующим образом:
	для vector элементы нужно возвести в квадрат;
	для map в квадрат нужно возвести только значения, но не ключи;
	для pair в квадрат нужно возвести каждый элемент пары.

Функция должна корректно работать не только для контейнеров, состоящих из чисел, но и для составных объектов, например, векторов словарей пар чисел.
Для успешной сдачи решения необходимо сделать предварительное объявление шаблонных функций перед всеми шаблонными функциями.
Пример предварительного объявления шаблонной функции
*/

#include <iostream>
#include <vector>
#include <map>

// Предварительное объявление шаблонных функций
template<typename T> T Sqr(T x);
template <typename First, typename Second> std::pair<First, Second> operator* (const std::pair<First, Second>& p1, const std::pair<First, Second>& p2);
template <typename Key, typename Value> std::map<Key, Value> operator* (const std::map<Key, Value>& m1, const std::map<Key, Value>& m2);
template <typename T> std::vector<T> operator* (const std::vector<T>& v1, const std::vector<T>& v2);

// Объявляем шаблонные функции
template <typename T>
T Sqr(T Collection)
{
	return Collection * Collection;
}

template <typename First, typename Second>
std::pair<First, Second> operator* (const std::pair<First, Second>& p1, const std::pair<First, Second>& p2)
{
	First f = p1.first * p2.first;
	Second s = p1.second * p2.second;

	return std::make_pair(f, s);
}

template <typename Key, typename Value>
std::map<Key, Value> operator* (const std::map<Key, Value>& m1, const std::map<Key, Value>& m2)
{
	std::map<Key, Value> result;
	for (auto& [key, value] : m1)
	{
		result[key] = Sqr(value);
	}

	return result;
}

template <typename T>
std::vector<T> operator* (const std::vector<T>& v1, const std::vector<T>& v2)
{
	std::vector<T> result;
	for (size_t i = 0; i < v1.size(); i++)
	{
		T res = v1.at(i) * v2.at(i);
		result.push_back(res);
	}

	return result;
}

int main()
{
	std::vector<int> v = { 1, 2, 3 };
	std::cout << "vector:";
	for (int x : Sqr(v)) {
		std::cout << ' ' << x;
	}
	std::cout << std::endl;

	std::map<int, std::pair<int, int>> map_of_pairs =
	{
		{4, {2, 2}},
		{7, {4, 3}}
	};
	std::cout << "map of pairs:" << std::endl;
	
	for (const auto& x : Sqr(map_of_pairs))
	{
		std::cout << x.first << ' ' << x.second.first << ' ' << x.second.second << std::endl;
	}
}