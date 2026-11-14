#include "libm_impl.h"

double nan(const char* s)
{
	(void)s;
	return NAN;
}
