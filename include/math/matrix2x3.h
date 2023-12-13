#pragma once
#include <cstring>

namespace sc
{
	template <typename T = float>
	struct Matrix2x3
	{
		union
		{
			struct
			{
				T a, b;
				T c, d;
				T tx, ty;
			};

			T elements[6];
		};

		Matrix2x3(const T* arr)
		{
			memcpy(elements, arr, sizeof(elements));
		};

		Matrix2x3(
			T m00 = 1.0f,
			T m01 = 0.0f,
			T m10 = 0.0f,
			T m11 = 1.0f,
			T m02 = 0.0f,
			T m12 = 0.0f
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
