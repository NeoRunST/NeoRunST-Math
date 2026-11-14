#include "libm_impl.h"

double exp2(double x)
{
	if (isnan(x)) return x;
	if (x > 1024.0) return INFINITY;
	if (x < -1075.0) return 0.0;
	int n = (int)x;
	if (n < 0 && (double)n != x) n -= 1;
	double f = x - (double)n;
	double p = 1.0;
	double t = 1.0;
	for (int i = 1; i <= 12; i++) {
		t *= f * 0.69314718055994530942 / (double)i;
		p += t;
	}
	return scalbn(p, n);
}
