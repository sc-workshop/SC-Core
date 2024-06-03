#include "core/exception/exception.h"

#include <cstdio>

namespace sc
{
	Exception::Exception(const char* format, ...)
	{
		va_list args;
		va_start(args, format);

		proceed_vargs(format, args);

		va_end(args);
	}

	void Exception::proceed_vargs(const char* format, va_list args)
	{
		vsprintf(m_message.data(), format, args);
	}
}
