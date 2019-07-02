/*
В данном задании вам предстоит изменить код таким образом, чтобы он соответствовал изложенным в курсе принципам.

Представьте, что этот код вам достался в наследство от коллеги и теперь вам предстоит поддерживать его и улучшать.
Первое, что вы решили сделать — это провести рефакторинг.

Конечные цели рефакторинга:
	1) упростить дальнейшую поддержку кода;
	2) уменьшить сложность кода;
	3) упростить добавление новых абстракций в программу.

	Review criteria 

Задание будет оцениваться по следующим критериям:
	1) эффективность выполнения кода;
	2) задублированность кода;
	3) эффективность использования приёмов рефакторинга кода, показанных в лекциях.
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Person
{
public:
	Person(const string& type, const string& name) : Type(type), Name(name) {}
	virtual void Walk(const string& destination) const
	{
		cout << Type << ": " << Name << " walks to: " << destination << endl;
	}
	const string Type;
	const string Name;
};

class Student : public Person
{
public:
	Student(const string& name, const string& favouriteSong) : Person("Student", name), FavouriteSong(favouriteSong) {}

	void Learn() const
	{
		cout << "Student: " << Name << " learns" << endl;
	}

	void Walk(const string& destination) const override
	{
		Person::Walk(destination);
		SingSong();
	}

	void SingSong() const 
	{
		cout << "Student: " << Name << " sings a song: " << FavouriteSong << endl;
	}

private:
	const string FavouriteSong;
};


class Teacher : public Person
{
public:

	Teacher(const string& name, const string& subject) : Person("Teacher", name), Subject(subject) {}

	void Teach() const
	{
		cout << "Teacher: " << Name << " teaches: " << Subject << endl;
	}

private:
	const string Subject;
};


class Policeman : public Person
{
public:
	Policeman(const string& name) : Person("Policeman", name) {}

	void Check(const Person& p) const
	{
		cout << "Policeman: " << Name << " checks " << p.Type << ". " << p.Type << "'s name is: " << p.Name << endl;
	}
};

void VisitPlaces(const Person& person, const vector<string>& places)
{
	for (const auto& p : places)
	{
		person.Walk(p);
	}
}

int main()
{
	Teacher t("Jim", "Math");
	Student s("Ann", "We will rock you");
	Policeman p("Bob");

	VisitPlaces(t, { "Moscow", "London" });
	p.Check(s);
	VisitPlaces(s, { "Moscow", "London" });
	return 0;
}