#include "matrix3.hpp"
#include "eceflla.hpp"
#include "utils.hpp"
#include <cmath>
#include <iostream>

#define PI 3.14159265

using namespace std;

int main(void)
{
	cout << fixed;
	cout.precision(8);

	long double lat, lng, alt;
	cout << "Input Lat & Lng & Alt(m)" << endl;
	cin >> lat >> lng >> alt;
	long double *xyz = llhxyz(lat, lng, alt);
	cout << "ECEF: " << xyz[0] << " " << xyz[1] << " " << xyz[2] << endl;
	double theta;
	long double rotate = 180 / PI;
	cout << "Input Rotate Angle" << endl;
	cin >> theta;
	long double angle = theta / rotate;

	cout << angle << endl;
	cout << cos(angle) << endl;
	cout << sin(angle) << endl;

	
	Matrix R(cos(angle), -sin(angle), 0, sin(angle), cos(angle), 0, 0, 0, 1);
	R.ShowMatrix();
	Matrix T_0(-sin(lng), cos(lng), 0, sin(lat)*cos(lng), -sin(lat)*sin(lng), cos(lat), cos(lat)*cos(lng), cos(lat)*sin(lng), sin(lat));
	T_0.ShowMatrix();
	Matrix Rotate = (R * T_0).Transpose();
	Rotate.ShowMatrix();
	
	long double x, y, z;
	cout << "Input X Y Z (km)" << endl;
	cin >> x >> y >> z;
	Matrix XYZ(x, 0, 0, y, 0, 0, z, 0, 0);
	Matrix C = Rotate * XYZ;
	C.ShowMatrix();

	Matrix Recef(xyz[0], 0, 0, xyz[1], 0, 0, xyz[2], 0, 0);
	Matrix Rresult = Recef + C;
	Rresult.ShowMatrix();

	long double newx = Rresult.GetElement(0, 0);
	long double newy = Rresult.GetElement(1, 0);
	long double newz = Rresult.GetElement(2, 0);

	long double *llh = xyzllh(newx, newy, newz);
	cout << "WGS84: " << llh[0] << " " << llh[1] << " " << llh[2] << "km" << endl;

	/*
	cout << "New Coordinate Input: ";
	cin >> lat >> lng;
	
	*/
	

	

	return 0;
}