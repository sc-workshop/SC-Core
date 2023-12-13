#pragma once
#include <cstring>

namespace sc
{
	template <typename T = float>
	struct Color
	{
		union
		{
			struct
			{
				T r, g, b;
			};

			T channels[3];
		};

		Color(const T* arr)
		{
			memcpy(channels, arr, sizeof(channels));
		};

		Color(T red = 0.0f, T green = 0.0f, T blue = 0.0f)
		{
			r = red;
			g = green;
			b = blue;
		};
	};
}
