#include "libm_impl.h"
#include "../math.h"

float tanf(float x)
{
	return (float)tan((double)x);
}
