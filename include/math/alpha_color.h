#pragma once
#include "color.h"

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4201)
#endif

namespace sc
{
	template <typename T = float>
	struct AlphaColor : public Color<T>
	{
		union
		{
			struct
			{
				T r, g, b, a;
			};

			T channels[4];
		};

		AlphaColor(const T* arr)
		{
			memcpy(channels, arr, sizeof(channels));
		};

		AlphaColor(T red = 0.0f, T green = 0.0f, T blue = 0.0f, T alpha = 0.0f)
		{
			r = red;
			g = green;
			b = blue;
            a = alpha;
		};
	};
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
