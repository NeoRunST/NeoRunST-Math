#include "libm_impl.h"

long long llrint(double x)
{
	return (long long)nearbyint(x);
}
