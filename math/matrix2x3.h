#pragma once
#include <cstring>

namespace sc
{
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

		Matrix2x3(const float* arr)
		{
			memcpy(elements, arr, sizeof(elements));
		};

		Matrix2x3(
			float m00 = 1.0f,
			float m01 = 0.0f,
			float m10 = 0.0f,
			float m11 = 1.0f,
			float m02 = 0.0f,
			float m12 = 0.0f
		)
		{
			a = m00;
			b = m01;

			c = m10;
			d = m11;

			tx = m02;
			ty = m12;
		};
	};
}
