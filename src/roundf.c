#include "libm_impl.h"
#include "../math.h"

float roundf(float x)
{
	return (float)round((double)x);
}
