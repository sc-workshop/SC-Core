#pragma once
#include <cstring>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4201)
#endif

namespace sc
{
	template <typename T = float>
	struct Point
	{
		union
		{
			struct
			{
				T x, y;
			};

			struct
			{
				T u, v;
			};

			struct
			{
				T s, t;
			};

			struct
			{
				T r, g;
			};

			struct
			{
				T l, a;
			};

			T coords[2];
		};

		Point(const T* arr)
		{
			memcpy(coords, arr, sizeof(coords));
		}

		Point(T a = 0.0f, T b = 0.0f)
		{
			x = a;
			y = b;
		};
	};
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
