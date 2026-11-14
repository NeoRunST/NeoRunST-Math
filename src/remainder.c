#include "libm_impl.h"

double remainder(double x, double y)
{
	double r = fmod(x, y);
	double ay;
	double q;

	if (r != r || r == 0.0) return r;
	ay = fabs(y);
	if (fabs(r) > 0.5 * ay) return r + (r > 0.0 ? -ay : ay);
	if (fabs(r) < 0.5 * ay) return r;
	q = (x - r) / y;
	if (fmod(q, 2.0) != 0.0) return r + (r > 0.0 ? -ay : ay);
	return r;
}
