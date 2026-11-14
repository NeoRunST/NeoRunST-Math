#include "libm_impl.h"

double rint(double x)
{
	return nearbyint(x);
}
