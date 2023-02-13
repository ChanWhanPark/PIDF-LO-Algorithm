#pragma once

#include <cmath>

using namespace std;

long double* radcur(long double lat);
long double rearth(long double lat);
long double gc2gd(long double flatgc, long double altkm);
long double* llhxyz(long double lat, long double lng, long double alt);
long double* xyzllh(long double x, long double y, long double z);