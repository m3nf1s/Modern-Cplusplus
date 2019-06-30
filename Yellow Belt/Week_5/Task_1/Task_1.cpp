/*
Дан следующий код:

		#include <iostream>

		using namespace std;

		class Animal {
		public:
			// ваш код

			const string Name;
		};


		class Dog {
		public:
			// ваш код

			void Bark() {
				cout << Name << " barks: woof!" << endl;
			}
		};

Определите до конца тела классов, соблюдая следующие требования:

	1) Класс Dog должен являться наследником класса Animal.
	2) Конструктор класса Dog должен принимать параметр типа string и инициализировать им поле Name в классе Animal.

*/

#include <iostream>

class Animal
{
public:
	Animal(const std::string& name) : Name(name)
	{
	}

	const std::string Name;
};

class Dog : public Animal
{
public:
	Dog(const std::string& name) : Animal(name)
	{
	}

	void Bark()
	{
		std::cout << Name << " barks: woof!" << std::endl;
	}
};

int main()
{
	Dog d("Charlie");
	d.Bark();
}