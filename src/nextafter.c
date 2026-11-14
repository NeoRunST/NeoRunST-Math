#include "libm_impl.h"

double nextafter(double x, double y)
{
	if (isnan(x) || isnan(y)) return x + y;
	if (x == y) return y;

	union {double f; uint64_t i;} ux = {x}, uy = {y};
	if (x == 0.0) {
		ux.i = 1;
		ux.i |= uy.i & (1ull << 63);
	} else if ((ux.i ^ uy.i) & (1ull << 63)) {
		ux.i -= 1;
	} else {
		ux.i += 1;
	}
	return ux.f;
}
