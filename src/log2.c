#include "libm_impl.h"

double log2(double x)
{
	if (isnan(x)) return x;
	if (x <= 0.0) {
		if (x == 0.0) return -INFINITY;
		return NAN;
	}
	int e;
	double m = frexp(x, &e);
	if (m < 0.70710678118654752440) {
		m *= 2.0;
		e -= 1;
	}
	double r = (m - 1.0) / (m + 1.0);
	double r2 = r * r;
	double s = r * (2.0 + r2 * (0.66666666666666666667 + r2 * (0.4 + r2 * 0.28571428571428571429)));
	return (double)e + s * 0.72134752044448170368;
}
