#pragma once

#include "exception/GeneralRuntimeException.h"

namespace sc
{
	class InvalidParamsException : public GeneralRuntimeException
	{
	public:
		virtual const char* what() const override
		{
			return "Image params is corrupted or incorrect";
		}
	};
}