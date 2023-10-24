#pragma once

struct Matrix2x3
{
	union
	{
		struct
		{
			float a, b;
			float c, d;
			float tx, ty;
		};

		float elements[6];
	};

	Matrix2x3();
	Matrix2x3(float m00, float m01, float m10, float m11, float m02, float m12);
	Matrix2x3(const float* arr);
};
