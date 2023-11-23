#pragma once

#include "exception/GeneralRuntimeException.h"
#include <sstream>

namespace sc
{
	class StbLoadingException : public GeneralRuntimeException
	{
	public:
		StbLoadingException(const char* reason) : m_reason(reason) {};

	public:
		virtual const char* what() const override
		{
			std::stringstream message;
			message << "Failed to load stb image: ";
			message << m_reason;
			return message.str().c_str();
		}
	private:
		const char* m_reason;
	};
}