#include "generic/image/raw_image.h"
#include "memory/alloc.h"
#include "memory/Allocator/STL/MemoryPool.h"

#include "exception/io/FileExceptions.h"

using namespace sc;

void throwing_function()
{
	throw IOGeneralException();
}

int main(int, char*)
{
	try
	{
		throwing_function();
	}
	catch (sc::GeneralRuntimeException& err)
	{
		const char* err_msg = err.message();
		std::cout << err_msg;
	}

	return 0;
}