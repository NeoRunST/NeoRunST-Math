#include "libm_impl.h"

double atanh(double x)
{
	double a = x < 0.0 ? -x : x;

	if (a >= 1.0) {
		if (a == 1.0) return (x > 0.0 ? 1.0 : -1.0) / 0.0;
		return (x - x) / 0.0;
	}
	if (a < 0x1p-28) return x;
	return 0.5 * log1p(2.0 * x / (1.0 - x));
}
