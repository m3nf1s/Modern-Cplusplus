/*
	В лекциях мы уже начали реализовывать свой вектор.
	В этой задаче вам надо его развить: добавить методы Size, Capacity и PushBack.
	Пришлите на проверку заголовочный файл simple_vector.h,
		содержащий объявление и определение шаблона класса SimpleVector.

	Требования:
	*	метод Capacity должен возвращать текущую ёмкость вектора — количество элементов,
			которое помещается в блок памяти, выделенный вектором в данный момент
	*	метод Size должен возвращать количество элементов в векторе
	*	метод PushBack добавляет новый элемент в конец вектора;
		если в текущем выделенном блоке памяти не осталось свободного места (т.е. Size() == Capacity()),
			вектор должен выделить блок размера 2 * Capacity(), скопировать в него все элементы и удалить старый.
	*	первый вызов метода PushBack для вновь созданного объекта должен делать ёмкость, равной единице
	*	метод PushBack должен иметь амортизированную константную сложность
	*	методы begin и end должны возвращать итераторы текущие начало и конец вектора
	*	в деструкторе должен освобождаться текущий блок памяти, выделенный вектором
	*	также см. дополнительные требования к работе SimpleVector в юнит-тестах в приложенном шаблоне решения

	Замечание
	Заголовочный файл, который вы пришлёте на проверку,
		не должен подключать файлы <vector>, <list>, <forward_list>, <deque>, <map>.
	Если у вас будет подключен один из этих файлов, вы получите ошибку компиляции.
*/
#include "simple_vector.h"
#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

void TestConstruction()
{
	SimpleVector<int> empty;
	ASSERT_EQUAL(empty.Size(), 0u);
	ASSERT_EQUAL(empty.Capacity(), 0u);
	ASSERT(empty.begin() == empty.end());

	SimpleVector<std::string> five_strings(5);
	ASSERT_EQUAL(five_strings.Size(), 5u);
	ASSERT(five_strings.Size() <= five_strings.Capacity());
	for (auto& item : five_strings)
	{
		ASSERT(item.empty());
	}
	five_strings[2] = "Hello";
	ASSERT_EQUAL(five_strings[2], "Hello");
}

void TestPushBack()
{
	SimpleVector<int> v;
	for (int i = 10; i >= 1; --i)
	{
		v.PushBack(i);
		ASSERT(v.Size() <= v.Capacity());
	}
	std::sort(std::begin(v), std::end(v));

	const std::vector<int> expected = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	ASSERT_EQUAL(v.Size(), expected.size());
	ASSERT(equal(std::begin(v), std::end(v), std::begin(expected)));
}

int main()
{
	TestRunner tr;
	RUN_TEST(tr, TestConstruction);
	RUN_TEST(tr, TestPushBack);
	return 0;
}