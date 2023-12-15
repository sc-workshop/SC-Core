#pragma once

#include "GeneralRuntimeException.h"

#include <sstream>

namespace sc
{
	class MemoryAllocationException final : public GeneralRuntimeException
	{
	public:
		MemoryAllocationException(const size_t& bytes) : GeneralRuntimeException("MemoryAllocationException", 1)
		{
			std::stringstream message;
			message << "Failed to allocate " << std::to_string(bytes) << " bytes of memory";
			m_message = message.str();
		}
	};
}