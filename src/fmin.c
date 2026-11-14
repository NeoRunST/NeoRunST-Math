#include "libm_impl.h"
#include "../math.h"

double fmin(double x, double y)
{
	if (isnan(x)) return y;
	if (isnan(y)) return x;
	return x < y ? x : y;
}

float fminf(float x, float y)
{
	if (isnan(x)) return y;
	if (isnan(y)) return x;
	return x < y ? x : y;
}
