/*
 * Условие
 * В этой задаче вам надо разработать класс Matrix для представления целочисленной матрицы. Более подробно класс Matrix должен иметь:
 *
 * 1) конструктор по умолчанию, который создаёт матрицу с нулём строк и нулём столбцов
 * 2) конструктор от двух целочисленных параметров: num_rows и num_cols, — которые задают количество строк и столбцов матрицы соответственно
 * 3) метод Reset, принимающий два целочисленных параметра, которые задают количество строк и столбцов матрицы соответственно
 * 4) константный метод At, который принимает номер строки и номер столбца (именно в этом порядке; нумерация строк и столбцов начинается с нуля) и возвращает значение в соответствущей ячейке матрицы
 * 5) неконстантный метод At с такими же параметрами, но возвращающий ссылку на значение в соответствущей ячейке матрицы
 * 6) константные методы GetNumRows и GetNumColumns, которые возвращают количество строк и столбцов матрицы соответственно
 *
 * Если количество строк или количество столбцов, переданное в конструктор класса Matrix или метод Reset, оказалось отрицательным, то должно быть выброшено стандартное исключение out_of_range.
 *
 * Это же исключение должен бросать метод At, если переданная в него ячейка выходит за границы матрицы.
 *
 * Кроме того для класса Matrix должны быть определены следующие операторы:
 * 1) оператор ввода из потока istream; формат ввода простой — сначала задаётся количество строк и столбцов (именно в этом порядке),
 *		а затем все элементы матрицы: сначала элемент первой строки и первого столбца, затем элемент первой строки и второго столбца и так далее
 * 2) оператор вывода в поток ostream; он должен выводить матрицу в том же формате, в каком её читает оператор ввода, — в первой строке количество строк и столбцов,
 *		во второй — элементы первой строки, в третьей — элементы второй строки и т.д.
 * 3) оператор проверки на равенство (==): он должен возвращать true,
 *		если сравниваемые матрицы имеют одинаковый размер и все их соответствующие элементы равны между собой,
 *		в противном случае он должен возвращать false.
 * 4) оператор сложения: он должен принимать две матрицы и возвращать новую матрицу,
 *		которая является их суммой; если переданные матрицы имеют разные размеры этот оператор должен выбрасывать стандартное исключение invalid_argument.
 */

#include <iostream>
#include <vector>
#include <stdexcept>
#include <fstream>

class Matrix
{
public:
	Matrix()
	{
		_num_rows = 0;
		_num_cols = 0;
	}

	Matrix(int num_rows, int num_cols);

	void Reset(int num_rows, int num_cols)
	{
		if (num_rows < 0 || num_cols < 0)
			throw std::out_of_range("out_of_range");

		if (num_rows == 0 || num_cols == 0)
			num_rows = num_cols = 0;

		_num_rows = num_rows;
		_num_cols = num_cols;

		_matrix.assign(num_rows, std::vector<int>(num_cols));
	}

	int At(const int row, const int column) const
	{
		if (row < 0 || column < 0 || row > _num_rows || column > _num_cols)
			throw std::out_of_range("out_of_range");

		return _matrix.at(row).at(column);
	}

	int& At(const int row, const int column)
	{
		if (row < 0 || column < 0 || row > _num_rows || column > _num_cols)
			throw std::out_of_range("out_of_range");

		return _matrix.at(row).at(column);
	}

	int GetNumRows() const
	{
		return _num_rows;
	}

	int GetNumColumns() const
	{
		return _num_cols;
	}

private:
	std::vector<std::vector<int>> _matrix;

	int _num_rows{};
	int _num_cols{};
};

std::istream& operator>> (std::istream & stream, Matrix & obj)
{
	int rows = 0;
	int columns = 0;
	stream >> rows >> columns;

	obj.Reset(rows, columns);
	for (int i = 0; i < obj.GetNumRows(); ++i)
	{
		for (int j = 0; j < obj.GetNumColumns(); ++j)
		{
			stream >> obj.At(i, j);
		}
	}
	return stream;
}

std::ostream& operator<< (std::ostream & stream, const Matrix & obj)
{
	stream << obj.GetNumRows() << ' ' << obj.GetNumColumns() << std::endl;
	for (int i = 0; i < obj.GetNumRows(); ++i)
	{
		for (int j = 0; j < obj.GetNumColumns(); ++j)
		{
			if (j > 0)
			{
				stream << ' ';
			}

			stream << obj.At(i, j);
		}

		stream << std::endl;
	}
	return stream;
}

bool operator== (const Matrix & lhs, const Matrix & rhs)
{
	if (lhs.GetNumRows() != rhs.GetNumRows())
		return false;

	if (lhs.GetNumColumns() != rhs.GetNumColumns())
		return false;

	for (int i = 0; i < lhs.GetNumRows(); i++)
	{
		for (int j = 0; j < lhs.GetNumColumns(); j++)
		{
			if (lhs.At(i, j) != rhs.At(i, j))
				return false;
		}
	}

	return true;
}

Matrix operator+ (const Matrix & lhs, const Matrix & rhs)
{
	if (lhs.GetNumRows() != rhs.GetNumRows())
		throw std::invalid_argument("invalid_argument");

	Matrix result(lhs.GetNumRows(), lhs.GetNumColumns());
	for (int i = 0; i < lhs.GetNumRows(); ++i)
	{
		for (int j = 0; j < lhs.GetNumColumns(); ++j)
		{
			result.At(i, j) = lhs.At(i, j) + rhs.At(i, j);
		}
	}

	return result;
}

int main()
{
	Matrix one;
	Matrix two;

	std::cin >> one >> two;
	std::cout << one + two << std::endl;
	return 0;
}

inline Matrix::Matrix(int num_rows, int num_cols)
{
	Reset(num_rows, num_cols);
}
