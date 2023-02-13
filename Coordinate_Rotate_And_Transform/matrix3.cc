#include "matrix3.hpp"
#include <iomanip> //setw ����
#include <cmath>
#define MAX 3
Matrix::Matrix(long double a, long double b, long double c, long double d, long double e, long double f, long double g, long double h, long double i)
{
	// �ʱ�ȭ
	m[0][0] = a;
	m[0][1] = b;
	m[0][2] = c;
	m[1][0] = d;
	m[1][1] = e;
	m[1][2] = f;
	m[2][0] = g;
	m[2][1] = h;
	m[2][2] = i;
}

Matrix Matrix::Transpose()
{
	Matrix copy; // ���ο� Matrix ����

	// ��� ����
	for (int i = 0; i < MAX; i++)
		for (int j = 0; j < MAX; j++)
			copy.m[i][j] = m[i][j];
	// ��ġ

	for (int i = 0; i < MAX; i++)
		for (int j = 0; j < MAX; j++)
			m[j][i] = copy.m[i][j];

	return *this;
}

Matrix Matrix::operator+(const Matrix &a)
{
	Matrix b; // ���ο� Matrix ����

	for (int i = 0; i < MAX; i++)
		for (int j = 0; j < MAX; j++)
			b.m[i][j] = m[i][j] + a.m[i][j]; // ����

	return b;
}

Matrix Matrix::operator-(const Matrix &a)
{
	Matrix b; // ���ο� Matrix ����
	for (int i = 0; i < MAX; i++)
		for (int j = 0; j < MAX; j++)
			b.m[i][j] = m[i][j] - a.m[i][j]; // ����

	return b;
}

Matrix Matrix::operator*(const Matrix &a)
{
	Matrix b; // ���ο� Matrix ����
	for (int i = 0; i < MAX; i++)
		for (int j = 0; j < MAX; j++)
			for (int k = 0; k < MAX; k++) {
				b.m[i][j] += (m[i][k] * a.m[k][j]); // ����
			}
				
				

	

	return b;
}

void Matrix::operator=(const Matrix &a)
{
	for (int i = 0; i < MAX; i++)
		for (int j = 0; j < MAX; j++)
			m[i][j] = a.m[i][j]; // �����Ѵ�
}

void Matrix::ShowMatrix()
{
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++)
			cout << setw(20) << m[i][j]; // ������ ����
		cout << endl;
	}
}

long double Matrix::GetElement(int i, int j) {
	if (i >= MAX || j >= MAX) return -999.999;
	else return m[i][j];
}