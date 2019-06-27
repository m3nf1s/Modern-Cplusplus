/*
Часть 1
Реализуйте построение арифметического выражения согласно следующей схеме:
	1) изначально есть выражение, состоящее из некоторого целого числа x;
	2) на каждом шаге к текущему выражению применяется некоторая операция:
		прибавление числа, вычитание числа, умножение на число или деление на число;
		перед применением операции выражение всегда должно быть заключено в скобки.

Формат ввода
В первой строке содержится исходное целое число x.
Во второй строке содержится целое неотрицательное число N— количество операций.
В каждой из следующих N строк содержится очередная операция:
	1) прибавление числа a: + a;
	2) либо вычитание числа b: - b;
	3) либо умножение на число c: * c;
	4) либо деление на число d: / d.
Количество операций может быть нулевым — в этом случае необходимо вывести исходное число.

Формат вывода
Выведите единственную строку — построенное арифметическое выражение.

Обратите внимание на расстановку пробелов вокруг символов:

каждый символ бинарной операции (+, -, * или /) должен быть окружён ровно одним пробелом с каждой стороны: (8) * 3;
символ унарного минуса (для отрицательных чисел) не нуждается в дополнительном пробеле: -5;
скобки и числа не нуждаются в дополнительных пробелах.

Часть 2. Без лишних скобок
Модифицируйте решение предыдущей части так, чтобы предыдущее выражение обрамлялось скобками лишь при необходимости,
	то есть только в том случае, когда очередная операция имеет бо́льший приоритет, чем предыдущая.
*/

#include <iostream>
#include <deque>
#include <string>

void with_bracers();
void with_priority_bracers();

int main()
{
	with_bracers();
	with_priority_bracers();
}

void with_bracers()
{
	std::deque<std::string> arithmetic_expression;

	int first_number{};
	std::cin >> first_number;
	arithmetic_expression.push_back(std::to_string(first_number));

	size_t command_count{};
	std::cin >> command_count;

	for (size_t i = 0; i < command_count; i++)
	{
		std::string symbol;
		int number{};

		std::cin >> symbol >> number;

		arithmetic_expression.push_front("(");
		std::string buf = ") " + symbol + " " + std::to_string(number);
		arithmetic_expression.push_back(buf);
	}

	for (const auto& v : arithmetic_expression)
	{
		std::cout << v;
	}
}

void with_priority_bracers()
{
	std::deque<std::string> arithmetic_expression;

	int first_number{};
	std::cin >> first_number;
	arithmetic_expression.push_back(std::to_string(first_number));

	size_t command_count{};
	std::cin >> command_count;
	bool first = true;

	std::string prev;

	for (size_t i = 0; i < command_count; ++i)
	{
		std::string symbol;
		int number{};
		std::cin >> symbol >> number;

		if ((symbol == "*" || symbol == "/") && (prev == "+" || prev == "-"))
		{
			arithmetic_expression.push_front("(");
			arithmetic_expression.push_back(")");
		}

		prev = symbol;

		std::string buf = " " + symbol + " " + std::to_string(number);
		arithmetic_expression.push_back(buf);

	}

	for (const auto& val : arithmetic_expression)
	{
		std::cout << val;
	}
}