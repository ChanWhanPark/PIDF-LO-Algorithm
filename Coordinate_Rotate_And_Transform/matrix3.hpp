#pragma once
#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

using namespace std;

class Matrix
{
private:
	long double m[3][3];
public:
	Matrix(long double a = 0.0, long double b = 0, long double c = 0, long double d = 0, long double e = 0, long double f = 0, long double g = 0, long double h = 0, long double i = 0);
	~Matrix()
	{
	}

	void ShowMatrix();
	long double GetElement(int i, int j);
	Matrix Transpose();
	Matrix operator+(const Matrix &a);
	Matrix operator-(const Matrix &a);
	Matrix operator*(const Matrix &a);
	void operator=(const Matrix &a);
};

#endif