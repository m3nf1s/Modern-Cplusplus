 //Task_3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.

//Реализуйте класс, поддерживающий набор строк в отсортированном порядке. 

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class SortedStrings
{
public:
	void AddString(const std::string& word)
	{
		sorted_string.push_back(word);
	}
	std::vector<std::string> GetSortedStrings()
	{
		std::sort(std::begin(sorted_string), std::end(sorted_string));
		return sorted_string;
	}
private:
	std::vector<std::string> sorted_string;
};

void PrintSortedStrings(SortedStrings& strings)
{
	for (const std::string& s : strings.GetSortedStrings())
	{
		std::cout << s << " ";
	}
	std::cout << std::endl;
}

struct Task
{
	void MakeRandom()
	{
		Text = "Hi";
	}
	int GetText()
	{
		return 2;
	}
	std::string Text;
};
int main()
{
	SortedStrings strings;
	strings.AddString("first");
	strings.AddString("second");
	strings.AddString("third");
	PrintSortedStrings(strings);

	strings.AddString("second");
	PrintSortedStrings(strings);

	return 0;
}

