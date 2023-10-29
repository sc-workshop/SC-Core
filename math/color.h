#pragma once
#include <cstring>

namespace sc
{
	struct Color
	{
		union
		{
			struct
			{
				float r, g, b, a;
			};

			float channels[4];
		};

		Color(const float* arr)
		{
			memcpy(channels, arr, sizeof(channels));
		};

		Color(float red = 0.0f, float green = 0.0f, float blue = 0.0f, float alpha = 1.0f)
		{
			r = red;
			g = green;
			b = blue;
			a = alpha;
		};
	};
}
