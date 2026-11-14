#include "libm_impl.h"
#include "../math.h"

float fabsf(float x)
{
	return (float)fabs((double)x);
}
