#pragma once

#include "exception/GeneralRuntimeException.h"
#include <sstream>

namespace sc
{
	class StbWritingException : public GeneralRuntimeException
	{
	public:
		virtual const char* what() const override
		{
			return "STB Image writing finished with failure code";
		}
	};
}