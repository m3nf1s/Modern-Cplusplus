#include "test_runner.h"

#include <utility>

using namespace std;

template <typename T>
class Table
{
public:
	Table(const size_t rows, const size_t columns) : _rows(rows), _columns (columns)
	{
		Resize(rows, columns);
	}

	void Resize(size_t new_count_rows, size_t new_count_columns)
	{
		this->_rows = new_count_rows;
		this->_columns = new_count_columns;
		
		_table.resize(_rows);
		for (size_t i = 0; i < _table.size(); ++i)
		{
			_table.at(i).resize(_columns);
		}
	}

	const vector<T>& operator[](const size_t index) const
	{
		return _table[index];
	}

	vector<T>& operator[] (const size_t index)
	{
		return _table[index];
	}

	pair<size_t, size_t> Size() const
	{
		return make_pair(_rows, _columns);
	}

private:
	size_t _rows;
	size_t _columns;
	vector<vector<T>> _table;
};

void TestTable() {
	Table<int> t(1, 1);
	ASSERT_EQUAL(t.Size().first, 1u);
	ASSERT_EQUAL(t.Size().second, 1u);
	t[0][0] = 42;
	ASSERT_EQUAL(t[0][0], 42);
	t.Resize(3, 4);
	ASSERT_EQUAL(t.Size().first, 3u);
	ASSERT_EQUAL(t.Size().second, 4u);
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestTable);

	return 0;
}