#include "libm_impl.h"
#include "../math.h"

float fmodf(float x, float y)
{
	return (float)fmod((double)x, (double)y);
}
