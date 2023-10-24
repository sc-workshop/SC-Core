#pragma once

#include "IOGeneralException.h"

namespace sc
{
	class ReadFileException : public IOGeneralException
	{
	public:
		virtual const char* what() const override
		{
			return "Failed to read data from non-readable file";
		};
	};
}