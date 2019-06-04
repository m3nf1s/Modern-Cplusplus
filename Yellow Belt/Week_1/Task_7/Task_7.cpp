/*
Реализуйте шаблонную функцию GetRefStrict, которая на вход принимает: map и значение ключа k.\
Если элемент по ключу k в коллекции отсутствует, то функция должна бросить исключение runtime_error, иначе вернуть ссылку на элемент в коллекции.
*/

#include <iostream>
#include <map>
#include <string>
#include <stdexcept>

template <typename Key, typename Value> Value& GetRefStrict(std::map<Key, Value>& map, const Key key);

template <typename Key, typename Value>
Value& GetRefStrict(std::map<Key, Value>& map, Key key)
{
	if (map.count(key) == 0)
		throw std::runtime_error("Error");

	return map.at(key);
}

int main()
{
    std::map<int, std::string> m = { {0, "value"} };
	std::string& item = GetRefStrict(m, 0);
	item = "newvalue";
	std::cout << m[0] << std::endl; // выведет newvalue
}