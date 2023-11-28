#pragma once

#include "GeneralRuntimeException.h"

#include <sstream>

namespace sc
{
	class MemoryAllocationException : public GeneralRuntimeException
	{
	public:
		MemoryAllocationException(const size_t& bytes)
		{
			std::stringstream message;
			message << "Failed to allocate " << std::to_string(bytes) << " bytes of memory";
			m_message = message.str();
		}
	};
}