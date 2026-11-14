#include "libm_impl.h"

int ilogb(double x)
{
	union {double f; uint64_t i;} u = {x};
	union {double f; uint64_t i;} v;
	int e = (int)(u.i >> 52 & 0x7ff);

	if (e == 0x7ff) return 2147483647;
	if (e == 0) {
		if (x == 0.0) return -2147483647;
		v.f = x * 0x1p64;
		return (int)(v.i >> 52 & 0x7ff) - 0x3ff - 64;
	}
	return e - 0x3ff;
}
