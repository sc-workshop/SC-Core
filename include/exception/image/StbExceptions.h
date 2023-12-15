#pragma once

#include "exception/GeneralRuntimeException.h"

namespace sc
{
	class StbLoadingException : public GeneralRuntimeException
	{
	public:
		StbLoadingException(const char* reason) : GeneralRuntimeException("StbLoadingException")
		{
			std::stringstream message;
			message << "Failed to load stb image: ";
			message << reason;

			m_message = message.str();
		};
	};

	SC_CONSTRUCT_SIMPLE_EXCEPTION(StbWritingException, "STB Image writing finished with failure code");
}