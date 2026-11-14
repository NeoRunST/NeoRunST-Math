#include "libm_impl.h"

double acosh(double x)
{
	union {double f; uint64_t i;} u = {x};
	double t;

	if (u.i >= 0x7ff0000000000000ULL) return x + x;
	if (x < 1.0) return (x - x) / 0.0;
	if (x == 1.0) return 0.0;
	if (x >= 0x1p28) return log(x) + 0.693147180559945309417232121458176568;
	t = x - 1.0;
	return log1p(t + sqrt(t * t + 2.0 * t));
}
