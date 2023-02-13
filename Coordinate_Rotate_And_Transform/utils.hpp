#pragma once
using namespace std;

struct Point {
	long double x;
	long double y;
};

struct Point3 {
	long double x;
	long double y;
	long double z;
};

double angle2(Point a, Point b);
double angle3(Point3 a, Point3 b);
double harversine(Point a, Point b);