#pragma once

class Complex
{
private:
	double Real, Imaginary;
public:
	Complex(double number);
	Complex(double real, double imaginary);
	double Magnitude() const;
	double Phase() const;


	Complex operator+(double number);
	Complex operator-(double number);
	Complex operator*(double number);
	Complex operator/(double number);
	Complex operator>(double number);
	Complex operator<(double number);
};

Complex operator+(double number, Complex complex);
Complex operator-(double number, Complex complex);
Complex operator*(double number, Complex complex);
Complex operator/(double number, Complex complex);
Complex operator>(double number, Complex complex);
Complex operator<(double number, Complex complex);
