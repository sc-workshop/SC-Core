#pragma once

#include "../GeneralRuntimeException.h"

namespace sc
{
	class IOGeneralException : public GeneralRuntimeException
	{
	public:
		virtual const char* what() const override
		{
			return "Failed to make I/O operation";
		};
	};
}