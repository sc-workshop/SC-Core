#pragma once

#include <cstdint>
#include <cstring>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4201)
#endif

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

#ifdef _MSC_VER
#pragma warning(pop)
#endif
