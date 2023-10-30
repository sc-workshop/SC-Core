#pragma once

#include <memory.h>
#include "exception/MemoryAllocationException.h"

namespace sc
{
	template<typename T = uint8_t>
	constexpr T* memalloc(size_t size)
	{
		if (size == 0)
		{
			return nullptr;
		}

		T* ptr = (T*)std::malloc(size);
		if (!ptr)
		{
			throw MemoryAllocationException(size);
		}

		return ptr;
	}

	template<typename T>
	constexpr T* memcopy(const T* source, void* destination, size_t size)
	{
		if (size == 0)
		{
			return nullptr;
		}

		return (T*)std::memcpy(destination, source, size);
	}
}