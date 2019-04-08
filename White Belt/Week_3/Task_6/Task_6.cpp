// Task_6.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

/*
Реализуйте класс ReversibleString,
	хранящий строку и поддерживающий методы Reverse для
	переворота строкии ToString для получения строки.
*/
#include <iostream>
#include <string>
#include <algorithm>

class ReversibleString
{
public:
	ReversibleString (const std::string& str)
	{
		line = str;
	}
	ReversibleString()
	{
		line = "";
	}
	void Reverse()
	{
		std::reverse(std::begin(line), std::end(line));
	}
	std::string ToString() const
	{
		return line;
	}
private:
	std::string line;
};
int main()
{
	ReversibleString s("live");
	s.Reverse();
	std::cout << s.ToString() << std::endl;

	s.Reverse();
	const ReversibleString& s_ref = s;
	std::string tmp = s_ref.ToString();
	std::cout << tmp << std::endl;

	ReversibleString empty;
	std::cout << '"' << empty.ToString() << '"' << std::endl;

	return 0;
}
