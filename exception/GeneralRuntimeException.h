#pragma once

#include <exception>
#include <sstream>
#include <iostream>

namespace sc
{
	class GeneralRuntimeException : std::exception
	{
	public:
		virtual const char* what() const override
		{
			return "Unknown runtime error";
		};
	};
}