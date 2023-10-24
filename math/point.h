#pragma once

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

	Point();

	Point(float a);
	Point(float a, float b);

	Point(const float* arr);
};
