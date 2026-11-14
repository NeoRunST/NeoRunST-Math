#include "libm_impl.h"

double logb(double x)
{
	if (isnan(x)) return x;
	if (isinf(x)) return INFINITY;
	if (x == 0.0) return -INFINITY;
	int e;
	frexp(x, &e);
	if (e == -1023) {
		double m = x * 0x1p1022;
		frexp(m, &e);
		e -= 1022;
	}
	return (double)(e - 1);
}
