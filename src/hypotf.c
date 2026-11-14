#include "libm_impl.h"
#include "../math.h"

float hypotf(float x, float y)
{
	return (float)hypot((double)x, (double)y);
}
