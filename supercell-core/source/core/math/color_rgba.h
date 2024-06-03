#pragma once

#include "core/memory/memory.h"

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4201)
#endif

namespace sc
{
	struct ColorRGBA
	{
		union
		{
			struct
			{
				std::uint8_t r, g, b, a;
			};

			std::uint8_t channels[4];
		};

		ColorRGBA(const std::uint8_t* arr)
		{
			Memory::copy<std::uint8_t>(arr, channels, sizeof(channels));
		};

		ColorRGBA(std::uint8_t red = 0, std::uint8_t green = 0, std::uint8_t blue = 0, std::uint8_t alpha = 0)
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
