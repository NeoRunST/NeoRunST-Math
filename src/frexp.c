#include "libm_impl.h"

double frexp(double x, int* e)
{
	union {double f; uint64_t i;} u = {x};
	int ee = u.i >> 52 & 0x7ff;

	if (!ee) {
		if (x) {
			x = frexp(x * 0x1p64, e);
			*e -= 64;
		} else {
			*e = 0;
		}
		return x;
	} else if (ee == 0x7ff) {
		return x;
	}

	*e = ee - 0x3fe;
	u.i &= 0x800fffffffffffffull;
	u.i |= 0x3fe0000000000000ull;
	return u.f;
}
