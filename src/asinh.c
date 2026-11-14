#include "libm_impl.h"

double asinh(double x)
{
	union {double f; uint64_t i;} u = {x};
	double h = 2.0 / 0x1p28;
	double e = 0x1p28;

	if (u.i >> 63) return -asinh(-x);
	if (u.i >= 0x7ff0000000000000ULL) return x + x;
	if (x >= e) return log(x) + 0.693147180559945309417232121458176568;
	if (x >= h) {
		double t = x * x;
		return log1p(x + t / (1.0 + sqrt(1.0 + t)));
	}
	return x;
}
