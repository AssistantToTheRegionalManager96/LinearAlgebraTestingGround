#pragma once

#include <vector>
#include <tuple>
#include <complex>

enum MatrixType
{
	Identity,
	Zeros,
	Ones
};

class Matrix
{
private:
	int col, row; // columns and row numbers
	typedef std::vector<double> Column; //Typedef vector of doubles to define each column - this is not a variable, just a declaration of a type (you can't assign to this)
	std::vector<Column> data; //A vector of columns creates our 2D matrix of data
public:
	//Constructors:
	Matrix(int rows, int columns);
	Matrix(int rows, int columns, MatrixType matrixType);

	//Const methods:
	std::tuple<int, int> Size() const; //Return size of matrix (col, row)
	double DiagonalProduct() const; //Product of diagonal terms (must be square)
	double Trace() const; //Sum of diagonal terms (must be square)
	double Determinant() const; //Determinant (must be square)
	std::vector<double> Eigenvalues() const; //Eigenvalues (must be square)
	bool IsUpperTri(double tolerance) const; //Is the matrix upper triangular ?
	bool IsSymmetric(double tolerance) const; //Is the matrix symmetric ?
	std::tuple<Matrix, Matrix> LUDecomposition() const; //Decompose A into lower triangular matrix L and upper triangular matrix U such that A=LU (Doolittle)
	std::tuple<Matrix, Matrix> QRDecomposition() const; //Decompose A into orthogonal matrix Q and upper triangular matrix R such that A=QR (Modified Gram-Schmidt)

	//Non-const methods:
	void Fill(double number); // Fill matrix entries with a number
	void MakeIdentity(); // Make the matrix an identity
	void Transpose(); //Transpose matrix
	void Inverse(); //Invert the matrix


	//Operator overloads with *this on LHS:
	Column& operator[](int i) //Operator overload to allow for use of Matrix[i][j]
	{
		return data[i]; //This essentially allows us to stack data[i][j] -  the j index is what we added here, so data[i] gives ith columns, and then stacking [j] gives you reference to jth row
	}
	Matrix operator*(double number); //Elementwise multiplication by a number
	Matrix operator*(Matrix& matrix2); //Matrix multiplication
	Matrix operator/(double number); //Elementwise division by a number
	Matrix operator+(Matrix& matrix2); //Add matrices
	Matrix operator+(double number); //Elementwise add number
	Matrix operator-(Matrix& matrix2); //Subtract matrices
	Matrix operator-(double number); //Elementwise subtract number
	Matrix operator&(Matrix& matrix2); //Elementwise multiply matrices
	Matrix operator|(Matrix& matrix2); //Elementwise divide matrices
	Matrix operator^(double exponent); //Matrix exponent
};

// Operator overloads with matrix on RHS:

Matrix operator*(double number, Matrix& matrix); //Elementwise multiplication by a number
Matrix operator/(double number, Matrix& matrix); //Elementwise division by a number
Matrix operator+(double number, Matrix& matrix); //Elementwise add number
Matrix operator-(double number, Matrix& matrix); //Elementwise subtract number