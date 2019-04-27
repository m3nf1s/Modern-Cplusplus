/*
Определите структуру «Студент» со следующими полями:
имя, фамилия, день, месяц и год рождения.
Создайте вектор из таких структур, заполните его из входных данных и затем по запросам выведите нужные поля.

Формат ввода

Первая строка содержит одно целое число N от 0 до 10000 — число студентов.

Далее идут N строк, каждая из которых содержит две строки длиной от 1 до 15 символов — имя и фамилию очередного студента,
и три целых числа от 0 до 1000000000 — день, месяц и год рождения.

Следующая строка содержит одно целое число M от 0 до 10000 — число запросов.

Следующие M строк содержат строку длиной от 1 до 15 символов — запрос,
и целое число от 0 до 1000000000 — номер студента (нумерация начинается с 1).

Формат вывода

Для запроса вида name K, где K от 1 до N, выведите через пробел имя и фамилию K-го студента.

Для запроса вида date K, где K от 1 до N, выведите через точку день, месяц и год рождения K-го студента.

Для остальных запросов выведите bad request.
*/

#include <iostream>
#include <string>
#include <vector>

struct Student
{
	std::string first_name;
	std::string last_name;
	int birthday;
	int birth_month;
	int birth_year;

	void GetFullName() const
	{
		std::cout << first_name << ' ' << last_name << std::endl;
	}

	void GetBirthDay() const
	{
		std::cout << birthday << '.' << birth_month << '.' << birth_year << std::endl;
	}
};

int main()
{
	int count_student;
	std::cin >> count_student;

	std::vector<Student> students;

	for (int i = 0; i < count_student; ++i)
	{
		std::string new_first_name, new_last_name;
		int new_birthday, new_birth_month, new_birth_year;

		std::cin >> new_first_name >> new_last_name >> new_birthday >> new_birth_month >> new_birth_year;

		students.emplace_back(Student{ new_first_name, new_last_name, new_birthday, new_birth_month, new_birth_year });
	}

	int count_command;
	std::cin >> count_command;

	for (int i = 0; i < count_command; ++i)
	{
		std::string command;
		int student;
		std::cin >> command >> student;

		if (command == "name" && student > 0 && student <= students.size())
		{
			students[--student].GetFullName();
			continue;
		}

		if (command == "date" && student > 0 && student <= students.size())
		{
			students[--student].GetBirthDay();
			continue;
		}

		std::cout << "bad request" << std::endl;
	}
}