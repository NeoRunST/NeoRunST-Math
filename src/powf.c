#include "libm_impl.h"
#include "../math.h"

float powf(float x, float y)
{
	return (float)pow((double)x, (double)y);
}
