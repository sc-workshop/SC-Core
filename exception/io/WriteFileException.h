#pragma once

#include "IOGeneralException.h"

namespace sc
{
	class WriteFileException : public IOGeneralException
	{
	public:
		virtual const char* what() const override
		{
			return "Failed to write data to non-writeable file";
		};
	};
}