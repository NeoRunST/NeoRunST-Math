#include "libm_impl.h"
#include "../math.h"

float cbrtf(float x)
{
	return (float)cbrt((double)x);
}
