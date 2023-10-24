#pragma once

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

	Color();

	Color(float red);
	Color(float red, float green);
	Color(float red, float green, float blue);
	Color(float red, float green, float blue, float alpha);

	Color(const float* arr);
};
