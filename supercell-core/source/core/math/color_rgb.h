#pragma once

#include "core/memory/memory.h"

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4201)
#endif

namespace sc
{
	struct ColorRGB
	{
		union
		{
			struct
			{
				std::uint8_t r, g, b;
			};

			std::uint8_t channels[3];
		};

		ColorRGB(const std::uint8_t* arr)
		{
			Memory::copy<std::uint8_t>(arr, channels, sizeof(channels));
		};

		ColorRGB(std::uint8_t red = 0, std::uint8_t green = 0, std::uint8_t blue = 0)
		{
			r = red;
			g = green;
			b = blue;
		};
	};
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif