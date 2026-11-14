#include "libm_impl.h"

double cbrt(double x)
{
	if (isnan(x)) return x;
	if (isinf(x)) return x;
	if (x == 0.0) return x;

	int sign = 1;
	if (x < 0.0) {
		sign = -1;
		x = -x;
	}

	int e;
	double m = frexp(x, &e);
	while (e % 3 != 0) {
		m *= 2.0;
		e -= 1;
	}
	e /= 3;

	double r = 0.5 * (1.0 + m);
	for (int i = 0; i < 6; i++) {
		r = (2.0 * r + m / (r * r)) / 3.0;
	}
	double v = scalbn(r, e);
	return sign < 0 ? -v : v;
}
