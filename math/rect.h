#pragma once

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

	Rect();

	Rect(float a, float b);
	Rect(float a, float b, float c, float d);
	
	Rect(const float* arr);
};
