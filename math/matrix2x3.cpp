#include "shared/math/matrix2x3.h"

#include <cstring>

Matrix2x3::Matrix2x3()
{
	a = 1.0f;
	b = 0.0f;

	c = 0.0f;
	d = 0.0f;

	tx = 0.0f;
	ty = 0.0f;
}

Matrix2x3::Matrix2x3(float m00, float m01, float m10, float m11, float m02, float m12)
{
	a = m00;
	b = m01;

	c = m10;
	d = m11;

	tx = m02;
	ty = m12;
}

Matrix2x3::Matrix2x3(const float* arr)
{
	memcpy(elements, arr, sizeof(elements));
}
