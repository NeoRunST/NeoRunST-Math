#include "libm_impl.h"
#include "../math.h"

double ldexp(double x, int n)
{
	return scalbn(x, n);
}

float ldexpf(float x, int n)
{
	return scalbnf(x, n);
}
