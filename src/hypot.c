#include "libm_impl.h"

double hypot(double x, double y)
{
	union {double f; uint64_t i;} ux = {x}, uy = {y};
	ux.i &= -1ull >> 1;
	uy.i &= -1ull >> 1;
	x = ux.f;
	y = uy.f;

	if (isinf(x) || isinf(y)) return INFINITY;
	if (isnan(x) || isnan(y)) return NAN;

	if (x < y) {
		double t = x;
		x = y;
		y = t;
	}
	if (x == 0.0) return 0.0;
	double sc = 1.0;
	if (x < 0x1p-512) {
		sc = 0x1p54;
	} else if (x > 0x1p512) {
		sc = 0x1p-54;
	}
	x *= sc;
	y *= sc;
	return sqrt(x * x + y * y) / sc;
}
