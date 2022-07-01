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
	// -----Constructors:
	
	// Construct matrix of pre-defined common type
	Matrix(int rows, int columns, MatrixType matrixType);

	// Standard constructor
	Matrix(int rows, int columns);

	// Constructor for run-time sized arrays (not recommended, use vectors), datasetSize must be equal to size of dataArray.
	Matrix(int rows, int columns, double dataArray[], int datasetSize);

	// Constructor for dynamically sized arrays (vectors), recommended approach.
	Matrix(int rows, int columns, std::vector<double> dataVector);

	//-------Const methods:
	
	//Return size of matrix (col, row)
	std::tuple<int, int> Size() const; 
	//Product of diagonal terms (must be square)
	double DiagonalProduct() const; 
	//Sum of diagonal terms (must be square)
	double Trace() const; 
	// Frobenius norm
	double FrobeniusNorm() const;
	//Determinant (must be square)
	double Determinant() const; 
	//Eigenvalues (must be square)
	std::vector<double> Eigenvalues() const; 
	//Is the matrix upper triangular ?
	bool IsUpperTri(double tolerance) const; 
	//Is the matrix lower triangular ?
	bool IsLowerTri(double tolerance) const;
	//Is the matrix in hessenberg form ?
	bool IsHessenberg(double tolerance) const;
	//Is the matrix symmetric ?
	bool IsSymmetric(double tolerance) const; 
	//Decompose A into lower triangular matrix L and upper triangular matrix U such that A=LU (Doolittle)
	std::tuple<Matrix, Matrix> LUDecomposition() const; 
	//Decompose A into orthogonal matrix Q and upper triangular matrix R such that A=QR (Modified Gram-Schmidt)
	std::tuple<Matrix, Matrix> QRDecomposition() const; 


	//-------Non-const methods:
	
	// Fill matrix entries with a number
	void Fill(double number); 
	// Make the matrix an identity
	void MakeIdentity();
	//Transpose matrix
	void Transpose(); 
	//Invert the matrix
	void Inverse(); 
	//Turn square matrix into a Hessenberg matrix
	void MakeHessenberg();


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

// Independent functions on matrices:

// Solve Lx = b, where L is lower tri
Matrix ForwardSolve(Matrix L, Matrix b);

//Solve Ux = b where U is upper tri
Matrix BackwardSolve(Matrix U, Matrix b);

// Solve Ax = b using LU decomposition and Forward/Backward solve methods
Matrix LinsolveLU(Matrix A, Matrix b);
