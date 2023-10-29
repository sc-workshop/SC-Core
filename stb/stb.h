#pragma once

#include "memory/alloc.h"

#define STBIR_MALLOC(size, c) ((void)(c), sc::memalloc(size))
#define STBIR_FREE(ptr,c)    ((void)(c), free(ptr))

#define STBI_MALLOC(sz)           sc::memalloc(sz)
#define STBI_REALLOC(p,newsz)     realloc(p,newsz)
#define STBI_FREE(p)              free(p)

#define STBIW_MALLOC(sz)        sc::memalloc(sz)
#define STBIW_REALLOC(p,newsz)  realloc(p,newsz)
#define STBIW_FREE(p)           free(p)

#include "stb_image.h"
#include "stb_image_write.h"
#include "stb_image_resize.h"