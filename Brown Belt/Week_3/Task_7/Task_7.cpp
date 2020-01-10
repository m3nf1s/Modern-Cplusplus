/*
	Вы работаете с иерархией классов, описывающих животных.
	Вам нужно определить тип Zoo, представляющий собой набор различных животных,
	и написать две функции:
	*	Zoo CreateZoo(std::istream& in)
	*	void Process(const Zoo& zoo, std::ostream& out)
	
	Функция CreateZoo должна читать слова из потока ввода.
	Если на вход поступают слова "Tiger", "Wolf" или "Fox", она должна помещать соответствующего зверя в зоопарк.
	В противном случае она должна прекратить чтение и сгенерировать исключение std::runtime_error.
	
	Функция Process должна перебрать всех зверей в зоопарке в порядке создания
	и записать в поток вывода для каждого из них результат работы виртуальной функции Voice.
	
	Один ваш друг написал решение этой задачи, но оно почему-то не работает.
	Исправьте его и сдайте в систему.
	
	Замечания:
	*	Код классов из файла animals.h переписывать не надо, просто подключите заголовочный файл animals.h.
	*	Обратите внимание, что в нашей версии файла animals.h голоса зверей могут отличаться от того, что приведено в примере.
	*	Ваша программа должна создавать ровно столько объектов-зверей, сколько было передано во входном потоке в функцию CreateZoo.

*/
#include "animals.h"
#include "test_runner.h"

#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>
#include <vector>
#include <memory>

using Zoo = std::vector<std::unique_ptr<Animal>>;

// Эта функция получает на вход поток ввода и читает из него описание зверей.
// Если очередное слово этого текста - Tiger, Wolf или Fox, функция должна поместить соответствующего зверя в зоопарк.
// В противном случае она должна прекратить чтение и сгенерировать исключение runtime_error.
Zoo CreateZoo(std::istream& in)
{
	Zoo zoo;
	std::string word;
	while (in >> word)
	{
		if (word == "Tiger")
		{
			zoo.push_back(std::make_unique<Tiger>());
		}
		else if (word == "Wolf")
		{
			zoo.push_back(std::make_unique<Wolf>());
		}
		else if (word == "Fox")
		{
			zoo.push_back(std::make_unique<Fox>());
		}
		else
		{
			throw std::runtime_error("Unknown animal!");
		}
	}
	return zoo;
}

// Эта функция должна перебрать всех зверей в зоопарке в порядке их создания
// и записать в выходной поток для каждого из них результат работы виртуальной функции voice.
// Разделяйте голоса разных зверей символом перевода строки '\n'.
void Process(const Zoo& zoo, std::ostream& out)
{
	for (const auto& animal : zoo)
	{
		out << animal->Voice() << "\n";
	}
}

void TestZoo() 
{
	std::istringstream input("Tiger Wolf Fox Tiger");
	std::ostringstream output;
	Process(CreateZoo(input), output);

	const std::string expected =
		"Rrrr\n"
		"Wooo\n"
		"Tyaf\n"
		"Rrrr\n";

	ASSERT_EQUAL(output.str(), expected);
}

int main()
{
	TestRunner tr;
	RUN_TEST(tr, TestZoo);
}
