#include "shared/math/point.h"

#include <cstring>

Point::Point()
{
	x = 0.0f;
	y = 0.0f;
}

Point::Point(float a)
{
	x = a;
	y = 0.0f;
}

Point::Point(float a, float b)
{
	x = a;
	y = b;
}

Point::Point(const float* arr)
{
	memcpy(coords, arr, sizeof(coords));
}
