#include "libm_impl.h"
#include "../math.h"

float sinf(float x)
{
	return (float)sin((double)x);
}
