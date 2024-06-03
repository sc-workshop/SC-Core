#pragma once

#include "core/memory/memory.h"

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4201)
#endif

namespace sc
{
	struct Rect
	{
		union
		{
			struct
			{
				float x, y;
				float width, height;
			};

			struct
			{
				float left, top;
				float right, bottom;
			};

			float points[4];
		};

		Rect(const float* arr)
		{
			Memory::copy<float>(arr, points, sizeof(points));
		};

		Rect(float a = 0.0f, float b = 0.0f, float c = 0.0f, float d = 0.0f)
		{
			x = a;
			y = b;
			width = c;
			height = d;
		};
	};
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
