#include "libm_impl.h"
#include "../math.h"

float expf(float x)
{
	return (float)exp((double)x);
}
