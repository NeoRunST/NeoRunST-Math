#include "libm_impl.h"

double nearbyint(double x)
{
	double t = floor(x);
	double d = x - t;

	if (d > 0.5) return t + 1.0;
	if (d < 0.5) return t;
	if (fmod(t, 2.0) != 0.0) return t + 1.0;
	return t;
}
