#pragma once

#include <vector>
#include <tuple>
//#include "MatrixOperations.h"



enum MatrixType
{
	Identity,
	Zeros,
	Ones
};

class Matrix; // This lets LUDecomposition know a Matrix type exists
std::tuple<Matrix, Matrix> LUDecomposition(Matrix& matrix); // this lets the Matrix class knows that a LUDecomposition function exists.



class Matrix
{
private:
	int col, row; // columns and row numbers
	typedef std::vector<double> Column; //Typedef vector of doubles to define each column - this is not a variable, just a declaration of a type (you can't assign to this)
	std::vector<Column> data; //A vector of columns creates our 2D matrix of data
public:
	//Construct the vector of rows data, with size equal to columns, and containing instances of vectors of doubles the size of rows (remember how you instantiate a vector)
	Matrix(int rows, int columns): col(columns), row(rows), data(rows, std::vector<double>(columns))
	{

	}

	Matrix(int rows, int columns, MatrixType matrixType) : col(columns), row(rows), data(rows, std::vector<double>(columns))
	{
		switch (matrixType)
		{
		case Identity:
			this->MakeIdentity();
			break;
		case Zeros:
			this->Fill(0);
			break;
		case Ones:
			this->Fill(1);
			break;
		default:
			break;
		}
	}

	Column& operator[](int i) //Operator overload to allow for use of Matrix[i][j]
	{
		return data[i]; //This essentially allows us to stack data[i][j] -  the j index is what we added here, so data[i] gives ith columns, and then stacking [j] gives you reference to jth row
	}

	void Fill(double number)
	{
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				data[i][j] = number;
			}
		}
	}

	void MakeIdentity()
	{
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				data[i][j] = (i == j) ? 1 : 0;
			}
		}
	}

	void Transpose()
	{
		std::vector<Column> dataTemp;
		std::vector<double> colTemp;

		for (int i = 0; i < col; i++)
		{
			colTemp.clear();
			for (int j = 0; j < row; j++)
			{
				colTemp.push_back(data[j].at(i));
			}
			dataTemp.push_back(colTemp);
		}

		data = dataTemp;
		col = data[0].size();
		row = data.size();
	}

	std::tuple<int,int> Size() const
	{
		return std::make_tuple(row, col);
	}

	double DiagonalProduct() const
	{
		if (col != row) throw std::exception("Matrix must be square");
		double product = 1;
		for (int i = 0; i < col; i++)
		{
			product *= data[i].at(i);
		}

		return product;
	}


	double Trace() const
	{
		if (col != row) throw std::exception("Matrix must be square");
		double sum = 0;
		for (int i = 0; i < col; i++)
		{
			sum += data[i].at(i);
		}

		return sum;
	}

	double Determinant() const
	{
		if (col != row) throw std::exception("Matrix must be square");

		Matrix tempMatrix = *this;
		std::tuple<Matrix, Matrix> LU = LUDecomposition(tempMatrix);
		double determinant  = std::get<0>(LU).DiagonalProduct() * std::get<1>(LU).DiagonalProduct();

		return determinant;
	}

	void Inverse()
	{

	}
};



std::tuple<Matrix, Matrix> LUDecomposition(Matrix& matrix) //This function decomposes input square matrix A into lower triangular matrix L and upper triangular matrix U such that A=LU (Doolittle)
{
	std::tuple<int, int> size = matrix.Size();
	int row = std::get<0>(size);
	int col = std::get<1>(size);

	Matrix lower(row, col);
	Matrix upper(row, col);

	for (int i = 0; i < col; i++)
	{
		for (int k = i; k < col; k++)
		{
			int sum = 0;
			for (int j = 0; j < i; j++)
			{
				sum += lower[i][j] * upper[j][k];
			}
			upper[i][k] = matrix[i][k] - sum;
		}

		for (int k = i; k < col; k++)
		{
			if (i == k) lower[i][i] = 1;
			else
			{
				int sum = 0;
				for (int j = 0; j < i; j++)
				{
					sum += lower[k][j] * upper[j][i];
				}
				lower[k][i] = (matrix[k][i] - sum) / upper[i][i];
			}

		}
	}

	return std::make_tuple(lower, upper);
}

