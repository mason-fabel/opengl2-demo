#include <cmath>
#include "func.h"

float func(float x) {
	float y;

	y = exp(-0.2 * x) * sin(3.0 * x);

	return y;
}
