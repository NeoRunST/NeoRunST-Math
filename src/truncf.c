#include "libm_impl.h"
#include "../math.h"

float truncf(float x)
{
	return (float)trunc((double)x);
}
