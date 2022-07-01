#include "Matrix.h"
#include <stdexcept>
//#include <sstream>

Matrix::Matrix(int rows, int columns) : col(columns), row(rows), data(rows, std::vector<double>(columns))
{}

Matrix::Matrix(int rows, int columns, MatrixType matrixType) : col(columns), row(rows), data(rows, std::vector<double>(columns))
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

Matrix::Matrix(int rows, int columns, double dataArray[], int datasetSize) : col(columns), row(rows), data(rows, std::vector<double>(columns))
{
	if (datasetSize != rows * columns) throw std::runtime_error("Data size does not match declared matrix size");
	int k{};
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			data[i][j] = dataArray[k];
			k++;
		}
	}
}

Matrix::Matrix(int rows, int columns, std::vector<double> dataVector) : col(columns), row(rows), data(rows, std::vector<double>(columns))
{
	if (dataVector.size() != rows * columns) throw std::runtime_error("Data size does not match declared matrix size");
	int k{};
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			data[i][j] = dataVector[k];
			k++;
		}
	}
}

void Matrix::Fill(double number)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			data[i][j] = number;
		}
	}
}

void Matrix::MakeIdentity()
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			data[i][j] = (i == j) ? 1 : 0;
		}
	}
}

void Matrix::Transpose()
{
	std::vector<Column> dataTemp;
	std::vector<double> colTemp;
	for (int i = 0; i < col; i++)
	{
		colTemp.clear();
		for (int j = 0; j < row; j++)
		{
			colTemp.push_back(data[j][i]);
		}
		dataTemp.push_back(colTemp);
	}

	data = dataTemp;
	col = data[0].size();
	row = data.size();
}

void Matrix::MakeHessenberg()
{
	Matrix matrix = *this;
	Matrix x = Matrix(1, row - 1);
	Matrix v = Matrix(1, row - 1, Zeros);
	Matrix vt = Matrix(1, row - 1);
	Matrix P = Matrix(col - 1, row - 1, Zeros);
	for (int i = 1; i < row; i++)
	{
		x[1][i] = matrix[1][i];
	}
	v[0][0] = x.FrobeniusNorm();
	v = v - x;
	vt = v;
	vt.Transpose();


	// This is not working yet
}

std::tuple<int, int> Matrix::Size() const
{
	return std::make_tuple(row, col);
}

double Matrix::DiagonalProduct() const
{
	if (col != row) throw std::exception("Matrix must be square");
	double product = 1;
	for (int i = 0; i < col; i++)
	{
		product *= data[i].at(i);
	}

	return product;
}

double Matrix::Trace() const
{
	if (col != row) throw std::exception("Matrix must be square");
	double sum = 0;
	for (int i = 0; i < col; i++)
	{
		sum += data[i].at(i);
	}

	return sum;
}

double Matrix::FrobeniusNorm() const
{
	Matrix matrix = *this;
	double sum{};
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			sum += pow(matrix[i][j], 2);
		}
	}
	return sqrt(sum);
}

double Matrix::Determinant() const
{
	if (col != row) throw std::exception("Matrix must be square");

	Matrix tempMatrix = *this;
	std::tuple<Matrix, Matrix> LU = LUDecomposition();
	double determinant = std::get<0>(LU).DiagonalProduct() * std::get<1>(LU).DiagonalProduct();

	return determinant;
}

std::vector<double> Matrix::Eigenvalues() const
{
	std::vector<double> eigenvalues;
	if (col != row) throw std::exception("Matrix must be square");
	Matrix tempMatrix = *this;
	std::tuple<Matrix, Matrix> QR = QRDecomposition();
	tempMatrix = std::get<1>(QR) * std::get<0>(QR);
	Matrix identityMatrix = Matrix(col, row, Identity);
	Matrix sk = Matrix(row, row);

	while (!tempMatrix.IsUpperTri(0.000001))
	{
		sk = identityMatrix * tempMatrix[col-1][row-1];
		tempMatrix = tempMatrix - sk;
		QR = tempMatrix.QRDecomposition();
		tempMatrix = std::get<1>(QR) * std::get<0>(QR) + sk;
	}
	QR = tempMatrix.QRDecomposition();
	Matrix V = std::get<0>(QR);
	for (int i = 0; i < col; i++)
	{
		eigenvalues.push_back(tempMatrix[i][i]);
	}

	return eigenvalues;
}

bool Matrix::IsUpperTri(double tolerance) const
{
	bool IsZero = true;
	for (int i = 1; i < row; i++)
	{
		for (int j = 0; j < i; j++)
		{
			IsZero = data[i].at(j) < tolerance;
			if (!IsZero)
			{
				return IsZero;
			}
		}
	}

	return IsZero;
}

bool Matrix::IsLowerTri(double tolerance) const
{
	bool IsZero = true;
	for (int i = 0; i < row-1; i++)
	{
		for (int j = i+1; j < col-i-1; j++)
		{
			IsZero = data[i].at(j) < tolerance;
			if (!IsZero)
			{
				return IsZero;
			}
		}
	}

	return IsZero;
}

bool Matrix::IsHessenberg(double tolerance) const
{
	bool IsZero = true;
	for (int i = 2; i < row; i++)
	{
		for (int j = 0; j < i - 1; j++)
		{
			IsZero = data[i].at(j) < tolerance;
			if (!IsZero)
			{
				return IsZero;
			}
		}
	}

	return IsZero;
}

bool Matrix::IsSymmetric(double tolerance) const
{
	Matrix matrix = *this;
	std::tuple<int, int> size = matrix.Size();
	int row = std::get<0>(size);
	int col = std::get<1>(size);
	bool IsSymmetric = row == col;
	if (!IsSymmetric) return IsSymmetric;

	for (int i = 0; i < col; i++)
	{
		for (int j = i; j < col - i; j++)
		{
			IsSymmetric = matrix[i][j] == matrix[j][i];
			if (!IsSymmetric) return IsSymmetric;
		}
	}

	return IsSymmetric;
}

std::tuple<Matrix, Matrix> Matrix::LUDecomposition() const //This function decomposes input square matrix A into lower triangular matrix L and upper triangular matrix U such that A=LU (Doolittle)
{
	Matrix matrix = *this;
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

std::tuple<Matrix, Matrix> Matrix::QRDecomposition() const // Decompose input matrix A into a product of an orthogonal matrix Q and an upper triangular matrix R (Modified Gram-Schmidt, Gander 1980)
{
	Matrix matrix = *this;
	std::tuple<int, int> size = matrix.Size();
	int row = std::get<0>(size);
	int col = std::get<1>(size);

	Matrix Q(row, col);
	Matrix R(row, col);
	double s;

	for (int k = 0; k < row; k++)
	{
		s = 0;
		for (int j = 0; j < col; j++)
		{
			s += matrix[j][k] * matrix[j][k];
		}
		R[k][k] = sqrt(s);
		for (int j = 0; j < col; j++)
		{
			Q[j][k] = matrix[j][k] / R[k][k];
		}

		for (int i = k + 1; i < row; i++)
		{
			s = 0;
			for (int j = 0; j < col; j++)
			{
				s += matrix[j][i] * Q[j][k];
			}
			R[k][i] = s;
			for (int j = 0; j < col; j++)
			{
				matrix[j][i] -= R[k][i] * Q[j][k];
			}
		}
	}

	return std::make_tuple(Q, R);
}


// Operator overloads:

//Column& Matrix::operator[](int i) //Operator overload to allow for use of Matrix[i][j]
//{
//	return data[i]; //This essentially allows us to stack data[i][j] -  the j index is what we added here, so data[i] gives ith columns, and then stacking [j] gives you reference to jth row
//}

Matrix Matrix::operator*(Matrix& matrix2)
{
	Matrix matrix1 = *this;
	std::tuple<int, int> size1 = matrix1.Size();
	std::tuple<int, int> size2 = matrix2.Size();

	if (std::get<1>(size1) != std::get<0>(size2)) throw std::exception("Wrong dimensions");

	int col = std::get<0>(size1);
	int row = std::get<1>(size2);
	Matrix tempMatrix = Matrix(row, col);
	double tempValue;

	for (int k = 0; k < row; k++)
	{
		for (int i = 0; i < col; i++)
		{
			tempValue = matrix1[k][0] * matrix2[0][i];
			for (int j = 0; j < std::get<1>(size1) - 1; j++)
			{
				tempValue += matrix1[k][j + 1] * matrix2[j + 1][i];
			}
			tempMatrix[k][i] = tempValue;
		}

	}

	return tempMatrix;
}

Matrix Matrix::operator*(double number)
{
	Matrix matrix = *this;
	std::tuple<int, int> size1 = matrix.Size();
	int row = std::get<0>(size1);
	int col = std::get<1>(size1);

	Matrix tempMatrix = matrix;

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			tempMatrix[i][j] = tempMatrix[i][j] * number;
		}
	}
	return tempMatrix;
}

Matrix operator*(double number, Matrix& matrix)
{
	std::tuple<int, int> size1 = matrix.Size();
	int row = std::get<0>(size1);
	int col = std::get<1>(size1);

	Matrix tempMatrix = matrix;

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			tempMatrix[i][j] = tempMatrix[i][j] * number;
		}
	}
	return tempMatrix;
}

Matrix Matrix::operator/(double number)
{
	if (number == 0) throw std::exception("Don't divide by 0");

	Matrix matrix = *this;
	std::tuple<int, int> size1 = matrix.Size();
	int row = std::get<0>(size1);
	int col = std::get<1>(size1);

	Matrix tempMatrix = matrix;

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			tempMatrix[i][j] = tempMatrix[i][j] / number;
		}
	}
	return tempMatrix;
}

Matrix operator/(double number, Matrix& matrix)
{
	if (number == 0) throw std::exception("Don't divide by 0");

	std::tuple<int, int> size1 = matrix.Size();
	int row = std::get<0>(size1);
	int col = std::get<1>(size1);

	Matrix tempMatrix = matrix;

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			tempMatrix[i][j] = tempMatrix[i][j] / number;
		}
	}
	return tempMatrix;
}

Matrix Matrix::operator+( Matrix& matrix2)
{
	Matrix matrix1 = *this;
	std::tuple<int, int> size1 = matrix1.Size();
	std::tuple<int, int> size2 = matrix2.Size();

	if (size1 != size2) throw std::exception("Wrong dimensions");

	int row = std::get<0>(size1);
	int col = std::get<1>(size1);

	Matrix tempMatrix = Matrix(row, col);

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			tempMatrix[i][j] = matrix1[i][j] + matrix2[i][j];
		}
	}

	return tempMatrix;
}

Matrix Matrix::operator+(double number)
{
	Matrix matrix = *this;
	std::tuple<int, int> size1 = matrix.Size();
	int row = std::get<0>(size1);
	int col = std::get<1>(size1);

	Matrix tempMatrix = matrix;

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			tempMatrix[i][j] = tempMatrix[i][j] + number;
		}
	}
	return tempMatrix;
}

Matrix operator+(double number, Matrix& matrix)
{
	std::tuple<int, int> size1 = matrix.Size();
	int row = std::get<0>(size1);
	int col = std::get<1>(size1);

	Matrix tempMatrix = matrix;

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			tempMatrix[i][j] = tempMatrix[i][j] + number;
		}
	}
	return tempMatrix;
}

Matrix Matrix::operator-(Matrix& matrix2)
{
	Matrix matrix1 = *this;
	std::tuple<int, int> size1 = matrix1.Size();
	std::tuple<int, int> size2 = matrix2.Size();

	if (size1 != size2) throw std::exception("Wrong dimensions");

	int row = std::get<0>(size1);
	int col = std::get<1>(size1);

	Matrix tempMatrix = Matrix(row, col);

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			tempMatrix[i][j] = matrix1[i][j] - matrix2[i][j];
		}
	}

	return tempMatrix;
}

Matrix Matrix::operator-(double number)
{
	Matrix matrix = *this;
	std::tuple<int, int> size1 = matrix.Size();
	int row = std::get<0>(size1);
	int col = std::get<1>(size1);

	Matrix tempMatrix = matrix;

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			tempMatrix[i][j] = tempMatrix[i][j] - number;
		}
	}
	return tempMatrix;
}

Matrix operator-(double number, Matrix& matrix)
{
	std::tuple<int, int> size1 = matrix.Size();
	int row = std::get<0>(size1);
	int col = std::get<1>(size1);

	Matrix tempMatrix = matrix;

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			tempMatrix[i][j] = tempMatrix[i][j] - number;
		}
	}
	return tempMatrix;
}

Matrix Matrix::operator&(Matrix& matrix2) // Elementwise multiply
{
	Matrix matrix1 = *this;
	std::tuple<int, int> size1 = matrix1.Size();
	std::tuple<int, int> size2 = matrix2.Size();

	if (size1 != size2) throw std::exception("Wrong dimensions");

	int row = std::get<0>(size1);
	int col = std::get<1>(size1);

	Matrix tempMatrix = Matrix(row, col);

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			tempMatrix[i][j] = matrix1[i][j] * matrix2[i][j];
		}
	}

	return tempMatrix;
}

Matrix Matrix::operator|(Matrix& matrix2) // Elementwise divide
{
	Matrix matrix1 = *this;
	std::tuple<int, int> size1 = matrix1.Size();
	std::tuple<int, int> size2 = matrix2.Size();

	if (size1 != size2) throw std::exception("Wrong dimensions");

	int row = std::get<0>(size1);
	int col = std::get<1>(size1);

	Matrix tempMatrix = Matrix(row, col);

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			tempMatrix[i][j] = matrix1[i][j] / matrix2[i][j];
		}
	}

	return tempMatrix;
}

Matrix Matrix::operator^(double exponent)
{
	Matrix tempMatrix = *this;
	if (exponent > 0)
	{
		std::tuple<int, int> size1 = tempMatrix.Size();
		int row = std::get<0>(size1);
		int col = std::get<1>(size1);

		if (col != row) throw std::exception("Matrix must be square");

		tempMatrix = tempMatrix * tempMatrix;
	}

	else if (exponent == 0)
	{
		tempMatrix.MakeIdentity();
	}

	else if (exponent < 0)
	{

	}
	return tempMatrix;
}

Matrix ForwardSolve(Matrix L, Matrix b)
{
	std::tuple<int, int> sizeL = L.Size();
	std::tuple<int, int> sizeb = b.Size();

	if (!L.IsLowerTri(0.000001) || std::get<0>(sizeL) != std::get<0>(sizeb)) throw std::exception("Wrong dimensions");

	Matrix x = Matrix(std::get<0>(sizeL), 1, Zeros);
	double tmp;
	for (int i = 0; i < std::get<1>(sizeL); i++)
	{
		tmp = b[i][0];
		for (int j = 0; j < i; j++)
		{
			tmp -= L[i][j] * x[j][0];
		}
		x[i][0] = tmp / L[i][i];
	}

	return x;
}

Matrix BackwardSolve(Matrix U, Matrix b)
{
	std::tuple<int, int> sizeU = U.Size();
	std::tuple<int, int> sizeb = b.Size();

	if (!U.IsUpperTri(0.000001) || std::get<0>(sizeU) != std::get<0>(sizeb)) throw std::exception("Wrong matrix dimension or given matrix is not upper tri");

	Matrix x = Matrix(std::get<0>(sizeU), 1, Zeros);
	double tmp;
	int i = std::get<1>(sizeU);
	//for (int i = std::get<1>(sizeU); i > 0 ; i--)
	while (i --> 0)
	{
		tmp = b[i][0];
		for (int j = i; j < std::get<0>(sizeU); j++)
		{
			tmp -= U[i][j] * x[j][0];
		}
		x[i][0] = tmp / U[i][i];
	}

	return x;
}

Matrix LinsolveLU(Matrix A, Matrix b)
{
	std::tuple<int, int> sizeA = A.Size();
	std::tuple<int, int> sizeb = b.Size();
	Matrix y = Matrix(std::get<0>(sizeb), std::get<1>(sizeb));
	Matrix x = Matrix(std::get<0>(sizeb), std::get<1>(sizeb));


	if (std::get<0>(sizeA) != std::get<0>(sizeb)) throw std::exception("Wrong matrix dimension");

	std::tuple<Matrix, Matrix> LU = A.LUDecomposition();

	y = ForwardSolve(std::get<0>(LU), b);
	x = BackwardSolve(std::get<1>(LU), y);

	return x;
}