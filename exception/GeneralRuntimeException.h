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
			return m_message.c_str();
		};

	protected:
		std::string m_message = "Unknown runtime error";
	};
}