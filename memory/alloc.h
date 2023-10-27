#pragma once

#include <memory.h>
#include "exception/MemoryAllocationException.h"

namespace sc
{
    template<typename T = uint8_t>
    constexpr T* memalloc(size_t size)
    {
        T* ptr = (T*)malloc(size);
        if (!ptr)
        {
            throw MemoryAllocationException(size);
        }

        return ptr;
    }
}