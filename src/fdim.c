#include "libm_impl.h"

double fdim(double x, double y)
{
	if (x != x || y != y) return x - y;
	return x > y ? x - y : 0.0;
}
