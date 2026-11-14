#include "libm_impl.h"

double remquo(double x, double y, int* q)
{
	double r = remainder(x, y);
	double n;
	int qi;

	if (r != r || r == 0.0) {
		*q = 0;
		return r;
	}
	n = (x - r) / y;
	if (n < 0.0) n = -n;
	qi = (int)fmod(n, 2147483648.0);
	if ((x - r) / y < 0.0) qi = -qi;
	*q = qi;
	return r;
}
