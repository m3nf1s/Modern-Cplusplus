/*
	Студента попросили написать класс Learner, помогающий изучать иностранный язык.
	В публичном интерфейсе класса должны быть две функции:

	int Learn(const vector<string>& words);
	vector<string> KnownWords();

	Функция Learn должна получать порцию слов, "запоминать" их и возвращать количество различных новых слов.
	Функция KnownWords должна возвращать отсортированный по алфавиту список всех выученных слов. В списке не должно быть повторов.

	Студент написал следующее решение этой задачи, однако оно почему-то работает очень медленно.
	Вам надо его ускорить.

	Вам дан файл learner.cpp с медленным решением задачи.
	Не меняя публичный интерфейс класса Learner, найдите в нём узкие места,
		исправьте их и сдайте переделанный класс в тестирующую систему.
*/
#include "learner.h"
#include "profiler.h"

#include <iostream>
#include <sstream>

using namespace std;
int main()
{
	Learner learner;
	string line;
	while (getline(cin, line))
	{
		vector<string> words;
		stringstream ss(line);
		string word;
		while (ss >> word)
		{
			words.push_back(word);
		}
		{
			LOG_DURATION("Learn");
			cout << learner.Learn(words) << "\n";
		}
		
	}

	cout << "=== known words ===\n";
	{
		LOG_DURATION("KnowWords");
		for (auto word : learner.KnownWords())
		{
			cout << word << "\n";
		}
	}
}