#include "libm_impl.h"

long lrint(double x)
{
	return (long)nearbyint(x);
}
