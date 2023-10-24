#pragma once
#include <cstring>

namespace sc
{
	struct Point
	{
		union
		{
			struct
			{
				float x, y;
			};

			struct
			{
				float u, v;
			};

			struct
			{
				float s, t;
			};

			struct
			{
				float r, g;
			};

			struct
			{
				float l, a;
			};

			float coords[2];
		};

		Point(const float* arr)
		{
			memcpy(coords, arr, sizeof(coords));
		}

		Point(float a = 0.0f, float b = 0.0f)
		{
			x = a;
			y = b;
		};
	};
}
