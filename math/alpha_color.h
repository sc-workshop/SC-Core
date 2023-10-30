#pragma once
#include "color.h"

namespace sc
{
	struct AlphaColor : public Color
	{
		union
		{
			struct
			{
				float r, g, b, a;
			};

			float channels[4];
		};

		AlphaColor(const float* arr)
		{
			memcpy(channels, arr, sizeof(channels));
		};

		AlphaColor(float red = 0.0f, float green = 0.0f, float blue = 0.0f, float alpha = 0.0f)
		{
			r = red;
			g = green;
			b = blue;
            a = alpha;
		};
	};
}
