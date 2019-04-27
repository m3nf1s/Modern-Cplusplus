// Task_1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <stdexcept>
#include <fstream>


using namespace std;

class Matrix
{
public:
	Matrix() : Matrix(0, 0)
	{
		_num_rows = 0;
		_num_cols = 0;
	}

	Matrix(int num_rows, int num_cols)
	{
		Reset(num_rows, num_cols);
	}

	void Reset( int num_rows,  int num_cols)
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

	int _num_rows;
	int _num_cols;
};

std::istream& operator>> (std::istream& stream, Matrix& obj)
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

std::ostream& operator<< (std::ostream& stream, const Matrix& obj)
{
	stream << obj.GetNumRows() << ' ' << obj.GetNumColumns() << std::endl;
	for (int i = 0; i < obj.GetNumRows(); ++i)
	{
		for (int j = 0; j < obj.GetNumColumns(); ++j)
		{	
			if(j > 0)
			{
				stream <<  ' ';
			}
			
			stream << obj.At(i, j);
		}

		stream << std::endl;
	}
	return stream;
}

bool operator== (const Matrix& lhs, const Matrix& rhs)
{
	if (lhs.GetNumRows() != rhs.GetNumRows())
		return false;

	if (lhs.GetNumColumns() != rhs.GetNumColumns())
		return false;

	for(int i = 0; i < lhs.GetNumRows(); i++)
	{
		for(int j = 0; j < lhs.GetNumColumns(); j++)
		{
			if (lhs.At(i, j) != rhs.At(i, j))
				return false;
		}
	}

	return true;
}

Matrix operator+ (const Matrix& lhs, const Matrix& rhs)
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

// Реализуйте здесь
// * класс Matrix
// * оператор ввода для класса Matrix из потока istream
// * оператор вывода класса Matrix в поток ostream
// * оператор проверки на равенство двух объектов класса Matrix
// * оператор сложения двух объектов класса Matrix

int main() {
	Matrix one;
	Matrix two;

	std::cin >> one >> two;
	std::cout << one + two << std::endl;
	return 0;
}