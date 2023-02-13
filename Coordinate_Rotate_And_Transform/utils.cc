#include "utils.hpp"
#include <cmath>

double angle2(Point a, Point b) {

}

double angle3(Point3 a, Point3 b) {

}

double harversine(Point a, Point b) {
	long double radius = 6378.137;
	long double PI = 3.14159265;
	long double rotate = PI / 180;

	long double deltaLat = abs(a.x - b.x) * rotate;
	long double deltaLng = abs(a.y - b.y) * rotate;

	long double sinDeltaLat = sin(deltaLat / 2);
	long double sinDeltaLng = sin(deltaLng / 2);

	long double squareRoot = sqrt(sinDeltaLat * sinDeltaLat + cos(a.x * rotate) * cos(b.x * rotate) * sinDeltaLng * sinDeltaLng);

	long double distance = 2 * radius * asin(squareRoot);

	return distance;
}