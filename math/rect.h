#pragma once
#include <cstring>

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
			memcpy(points, arr, sizeof(points));
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