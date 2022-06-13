//#pragma once
//
//#include <iostream>
//#include <tuple>
//#include "Matrix.h"
//
//Matrix operator*(Matrix& matrix1, Matrix& matrix2)
//{
//	std::tuple<int, int> size1 = matrix1.Size();
//	std::tuple<int, int> size2 = matrix2.Size();
//
//	if (std::get<1>(size1) != std::get<0>(size2)) throw std::exception("Wrong dimensions");
//
//	int col = std::get<0>(size1);
//	int row = std::get<1>(size2);
//	Matrix tempMatrix = Matrix(row, col);
//	double tempValue;
//
//	for (int k = 0; k < row; k++)
//	{
//		for (int i = 0; i < col; i++)
//		{
//			tempValue = matrix1[k][0] * matrix2[0][i];
//			for (int j = 0; j < std::get<1>(size1)-1; j++)
//			{
//				tempValue += matrix1[k][j + 1] * matrix2[j + 1][i];
//			}
//			tempMatrix[k][i] = tempValue;
//		}
//
//	}
//
//	return tempMatrix;
//}
//
//Matrix operator*(Matrix& matrix, double number)
//{
//	std::tuple<int, int> size1 = matrix.Size();
//	int row = std::get<0>(size1);
//	int col = std::get<1>(size1);
//
//	Matrix tempMatrix = matrix;
//
//	for (int i = 0; i < row; i++)
//	{
//		for (int j = 0; j < col; j++)
//		{
//			tempMatrix[i][j] = tempMatrix[i][j] * number;
//		}
//	}
//	return tempMatrix;
//}
//
//Matrix operator/(Matrix& matrix, double number)
//{
//	if (number == 0) throw std::exception("Don't divide by 0");
//
//	std::tuple<int, int> size1 = matrix.Size();
//	int row = std::get<0>(size1);
//	int col = std::get<1>(size1);
//
//	Matrix tempMatrix = matrix;
//
//	for (int i = 0; i < row; i++)
//	{
//		for (int j = 0; j < col; j++)
//		{
//			tempMatrix[i][j] = tempMatrix[i][j] / number;
//		}
//	}
//	return tempMatrix;
//}
//
//Matrix operator+(Matrix& matrix1, Matrix& matrix2)
//{
//	std::tuple<int, int> size1 = matrix1.Size();
//	std::tuple<int, int> size2 = matrix2.Size();
//
//	if (size1 != size2) throw std::exception("Wrong dimensions");
//
//	int row = std::get<0>(size1);
//	int col = std::get<1>(size1);
//
//	Matrix tempMatrix = Matrix(row, col);
//
//	for (int i = 0; i < row; i++)
//	{
//		for (int j = 0; j < col; j++)
//		{
//			tempMatrix[i][j] = matrix1[i][j] + matrix2[i][j];
//		}
//	}
//
//	return tempMatrix;
//}
//
//Matrix operator+(Matrix& matrix, double number)
//{
//
//	std::tuple<int, int> size1 = matrix.Size();
//	int row = std::get<0>(size1);
//	int col = std::get<1>(size1);
//
//	Matrix tempMatrix = matrix;
//
//	for (int i = 0; i < row; i++)
//	{
//		for (int j = 0; j < col; j++)
//		{
//			tempMatrix[i][j] = tempMatrix[i][j] + number;
//		}
//	}
//	return tempMatrix;
//}
//
//Matrix operator-(Matrix& matrix1, Matrix& matrix2)
//{
//	std::tuple<int, int> size1 = matrix1.Size();
//	std::tuple<int, int> size2 = matrix2.Size();
//
//	if (size1 != size2) throw std::exception("Wrong dimensions");
//
//	int row = std::get<0>(size1);
//	int col = std::get<1>(size1);
//
//	Matrix tempMatrix = Matrix(row, col);
//
//	for (int i = 0; i < row; i++)
//	{
//		for (int j = 0; j < col; j++)
//		{
//			tempMatrix[i][j] = matrix1[i][j] - matrix2[i][j];
//		}
//	}
//
//	return tempMatrix;
//}
//
//Matrix operator-(Matrix& matrix, double number)
//{
//
//	std::tuple<int, int> size1 = matrix.Size();
//	int row = std::get<0>(size1);
//	int col = std::get<1>(size1);
//
//	Matrix tempMatrix = matrix;
//
//	for (int i = 0; i < row; i++)
//	{
//		for (int j = 0; j < col; j++)
//		{
//			tempMatrix[i][j] = tempMatrix[i][j] - number;
//		}
//	}
//	return tempMatrix;
//}
//
//Matrix operator&(Matrix& matrix1, Matrix& matrix2) // Elementwise multiply
//{
//	std::tuple<int, int> size1 = matrix1.Size();
//	std::tuple<int, int> size2 = matrix2.Size();
//
//	if (size1 != size2) throw std::exception("Wrong dimensions");
//
//	int row = std::get<0>(size1);
//	int col = std::get<1>(size1);
//
//	Matrix tempMatrix = Matrix(row, col);
//
//	for (int i = 0; i < row; i++)
//	{
//		for (int j = 0; j < col; j++)
//		{
//			tempMatrix[i][j] = matrix1[i][j] * matrix2[i][j];
//		}
//	}
//
//	return tempMatrix;
//}
//
//Matrix operator|(Matrix& matrix1, Matrix& matrix2) // Elementwise divide
//{
//	std::tuple<int, int> size1 = matrix1.Size();
//	std::tuple<int, int> size2 = matrix2.Size();
//
//	if (size1 != size2) throw std::exception("Wrong dimensions");
//
//	int row = std::get<0>(size1);
//	int col = std::get<1>(size1);
//
//	Matrix tempMatrix = Matrix(row, col);
//
//	for (int i = 0; i < row; i++)
//	{
//		for (int j = 0; j < col; j++)
//		{
//			tempMatrix[i][j] = matrix1[i][j] / matrix2[i][j];
//		}
//	}
//
//	return tempMatrix;
//}
//
//Matrix operator^(Matrix& matrix, double exponent)
//{
//	Matrix tempMatrix = matrix;
//	if (exponent > 0)
//	{
//		std::tuple<int, int> size1 = matrix.Size();
//		int row = std::get<0>(size1);
//		int col = std::get<1>(size1);
//
//		if (col != row) throw std::exception("Matrix must be square");
//
//		tempMatrix = tempMatrix * tempMatrix;
//	}
//
//	else if (exponent == 0)
//	{
//		tempMatrix.MakeIdentity();
//	}
//
//	else if (exponent < 0)
//	{
//
//	}
//
//
//
//	return tempMatrix;
//}

//std::tuple<Matrix, Matrix> LUDecomposition(Matrix& matrix) //This function decomposes input square matrix A into lower triangular matrix L and upper triangular matrix U such that A=LU (Doolittle)
//{
//	std::tuple<int, int> size = matrix.Size();
//	int col = std::get<0>(size);
//	int row = std::get<1>(size);
//
//	Matrix lower(col, row);
//	Matrix upper(col, row);
//
//	for (int i = 0; i < col; i++)
//	{
//		for (int k = i; k < col; k++)
//		{
//			int sum = 0;
//			for (int j = 0; j < i; j++)
//			{
//				sum += lower[j][i] * upper[k][j];
//			}
//			upper[k][i] = matrix[k][i] - sum;
//		}
//
//		for (int k = i; k < col; k++)
//		{
//			if (i == k) lower[i][i] = 1;
//			else
//			{
//				int sum = 0;
//				for (int j = 0; j < i; j++)
//				{
//					sum += lower[j][k] * upper[i][j];
//				}
//				lower[i][k] = (matrix[i][k] - sum) / upper[i][i];
//			}
//
//		}
//	}
//
//	return std::make_tuple(lower, upper);
//}