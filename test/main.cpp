#include "generic/image/raw_image.h"
#include "memory/alloc.h"
#include "memory/Allocator/STL/MemoryPool.h"

#include "exception/io/FileExceptions.h"

using namespace sc;

int main(int, char*)
{
	std::vector<int, STL::MemoryPoolAllocator<int>> vec;

	vec.resize(123123);

	std::cout << vec[123122] << std::endl;

	return 0;
}