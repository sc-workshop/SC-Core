#include "shared/math/rect.h"

#include <cstring>

Rect::Rect()
{
	x = 0.0f;
	y = 0.0f;
	width = 0.0f;
	height = 0.0f;
}

Rect::Rect(float a, float b)
{
	x = 0.0f;
	y = 0.0f;
	width = a;
	height = b;
}

Rect::Rect(float a, float b, float c, float d)
{
	x = a;
	y = b;
	width = c;
	height = d;
}

Rect::Rect(const float* arr)
{
	memcpy(points, arr, sizeof(points));
}
