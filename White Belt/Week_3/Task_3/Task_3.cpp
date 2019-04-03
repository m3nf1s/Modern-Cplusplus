// Task_3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>

struct Lecture
{
	std::string title;
	int duration;
	std::string author;
};

void PrintLecture(const Lecture& lec)
{
	std::cout << lec.title << " " << lec.duration << " " << lec.author << std::endl;
}


int main()
{
	Lecture math = { "Math", 20, "Hennry" };
	PrintLecture(math);
}

