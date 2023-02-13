#include "eceflla.hpp"
#include <iostream>
using namespace std;

long double EARTH_A = 6378.137;
long double EARTH_F = 1 / 298.257223563;
long double EARTH_B = EARTH_A * (1.0 - EARTH_F);
long double EARTH_ECC = 1 - (pow(EARTH_B, 2.0) / pow(EARTH_A, 2.0));
long double EARTH_ECCSQ = sqrt(EARTH_ECC);
long double PI = 3.141592653;

/* Compute the radius at the geodetic latitude lat (in degrees) */
long double* radcur(long double lat) {
	
	long double rotate = PI / 180;

	long double clat = cos(rotate * lat);
	long double slat = sin(rotate * lat);

	long double dsquare = 1.0 - EARTH_ECC * pow(slat, 2.0);
	long double d = sqrt(dsquare);

	long double rn = EARTH_A / d;
	long double rm = rn * (1.0 - EARTH_ECC) / dsquare;

	long double rho = rn * clat;
	long double z = (1.0 - EARTH_ECC) * rn * slat;
	long double rsquare = pow(rho, 2.0) + pow(z, 2.0);
	long double r = sqrt(rsquare);

	long double* rrnrm = new long double[3];
	rrnrm[0] = r;
	rrnrm[1] = rn;
	rrnrm[2] = rm;

	return rrnrm;
}

/* Physical radius of earth from geodetic latitude */
long double rearth(long double lat) {
	long double* rrnrm = radcur(lat);
	long double r = rrnrm[0];
	return r;
}

/* Geocentric latitude to Geodetic latitude */
long double gc2gd(long double flatgc, long double altkm) {
	long double rotate = PI / 180;
	long double rrotate = 1 / rotate;

	long double* rrnrm = radcur(flatgc);
	long double rn = rrnrm[1];
	long double ratio = 1 - EARTH_ECC * rn / (rn + altkm);
	long double tlat = tan(rotate * flatgc) / ratio;
	long double flatgd = rotate * atan(tlat);

	rrnrm = radcur(flatgd);
	rn = rrnrm[1];
	ratio = 1 - EARTH_ECC * rn / (rn + altkm);
	tlat = tan(rotate * flatgc) / ratio;
	flatgd = rotate * atan(tlat);

	return flatgd;
}

long double* llhxyz(long double lat, long double lng, long double alt) {

	long double rotate = PI / 180;

	long double clat = cos(rotate * lat);
	long double clng = cos(rotate * lng);
	long double slat = sin(rotate * lat);
	long double slng = sin(rotate * lng);

	long double* rrnrm = radcur(lat);
	long double re = rrnrm[0];
	long double rn = rrnrm[1];

	long double x = (rn + alt * 0.001) * clat * clng;
	long double y = (rn + alt * 0.001) * clat * slng;
	long double z = ((1 - EARTH_ECC) * rn + alt * 0.001) * slat;

	long double* xyz = new long double[3];
	xyz[0] = x;
	xyz[1] = y;
	xyz[2] = z;

	return xyz;
}

long double* xyzllh(long double x, long double y, long double z) {
	long double rotate = PI / 180;
	long double flon, flat, altkm;

	long double *llhvec = new long double[3];
	
	long double rp = sqrt(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0));
	long double flatgc = asin(z / rp) / rotate;
	long double testval = abs(x) + abs(y);
	if (testval < 1.0e-10) flon = 0.0;
	else flon = atan2(y, x) / rotate;
	if (flon < 0.0) flon += 360.0;
	long double p = sqrt(pow(x, 2.0) + pow(y, 2.0));
	if (p < 1.0e-10) {
		flat = 90.0;
		if (z < 0.0) flat = -90.0;
		altkm = rp - rearth(flat);
		llhvec[0] = flat;
		llhvec[1] = flon;
		llhvec[2] = altkm;
		return llhvec;
	}
	else {
		long double rnow = rearth(flatgc);
		altkm = rp - rnow;
		flat = gc2gd(flatgc, altkm);

		long double* rrnrm = radcur(flat);
		long double rn = rrnrm[1];

		for (int i = 0; i < 5; i++) {
			long double slat = sin(rotate * flat);
			long double tangd = (z + rn * EARTH_ECC * slat) / p;
			long double flatn = atan(tangd) / rotate;

			long double dlat = flatn - flat;
			flat = flatn;
			long double clat = cos(rotate * flat);

			rrnrm = radcur(flat);
			rn = rrnrm[1];

			altkm = (p / clat) - rn;

			if (abs(dlat) < 1.0e-12) break;
		}

		llhvec[0] = flat;
		llhvec[1] = flon;
		llhvec[2] = altkm;
		cout << llhvec[0] << " " << llhvec[1] << " " << llhvec[2]*1000.0 << endl;
		return llhvec;
	}

}