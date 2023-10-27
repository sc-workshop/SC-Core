
#include "memory/alloc.h"

#define STBIR_MALLOC(size, c) ((void)(c), sc::memalloc(size))
#define STBIR_FREE(ptr,c)    ((void)(c), free(ptr))

#include "stb_image_resize.h"