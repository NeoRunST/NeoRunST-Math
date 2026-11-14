#include "libm_impl.h"

double scalbln(double x, long n)
{
	if (n > 2147483647L) n = 2147483647L;
	if (n < -2147483647L) n = -2147483647L;
	return scalbn(x, (int)n);
}
