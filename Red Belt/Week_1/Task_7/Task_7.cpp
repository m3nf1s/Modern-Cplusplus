/*
	Вам надо написать шаблонный класс Table для электронной таблицы.
	Для простоты будем считать, что все ячейки таблицы имеют один и тот же тип данных T.
	Таблица должна уметь менять свой размер по требованию пользователя.
	Вновь созданные ячейки должны заполняться значениями по умолчанию типа T.

	Требования к классу такие:

	1.	Класс должен называться Table.

	2.	У класса должен быть шаблонный параметр T - тип элемента в ячейке.

	3.	У класса должен быть конструктор,
			получающий на входе два числа типа size_t, - количество строк и столбцов соответственно.

	4.	У класса должны быть константная и неконстантная версии оператора [],
			возвращающего нечто такое, к чему снова можно было бы применить оператор [].
		То есть, должны работать конструкции вида cout << table[i][j];и table[i][j] = value;.
		Проверять корректность индексов при этом не нужно.

	5.	У класса должна быть функция Resize, получающая на вход два параметра типа size_t и меняющая размер таблицы.
		Старые данные, умещающиеся в новый размер, должны при этом сохраниться.

	6.	У класса должен быть константный метод Size,
			возвращающий pair<size_t, size_t> размер таблицы (в том же порядке, в котором эти аргументы передавались в конструктор).
*/

#include "test_runner.h"

#include <utility>

using namespace std;

template <typename T>
class Table
{
public:
	Table(const size_t rows, const size_t columns)
		: rows_(rows)
		, columns_ (columns)
	{
		Resize(rows, columns);
	}

	void Resize(size_t new_count_rows, size_t new_count_columns)
	{
		this->rows_ = new_count_rows;
		this->columns_ = new_count_columns;
		
		table_.resize(rows_);
		for (size_t i = 0; i < table_.size(); ++i)
		{
			table_.at(i).resize(columns_);
		}
	}

	const vector<T>& operator[](const size_t index) const
	{
		return table_[index];
	}

	vector<T>& operator[] (const size_t index)
	{
		return table_[index];
	}

	pair<size_t, size_t> Size() const
	{
		return make_pair(rows_, columns_);
	}

private:
	size_t rows_;
	size_t columns_;
	vector<vector<T>> table_;
};

void TestTable()
{
	Table<int> t(1, 1);
	ASSERT_EQUAL(t.Size().first, 1u);
	ASSERT_EQUAL(t.Size().second, 1u);
	t[0][0] = 42;
	ASSERT_EQUAL(t[0][0], 42);
	t.Resize(3, 4);
	ASSERT_EQUAL(t.Size().first, 3u);
	ASSERT_EQUAL(t.Size().second, 4u);
}

int main()
{
	TestRunner tr;
	RUN_TEST(tr, TestTable);

	return 0;
}