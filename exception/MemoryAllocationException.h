#pragma once

#include "GeneralRuntimeException.h"

#include <sstream>

namespace sc
{
	class MemoryAllocationException : public GeneralRuntimeException
	{
	public:
		MemoryAllocationException(const size_t& bytes) : m_bytes(bytes)
		{}

		virtual const char* what() const override
		{
			std::stringstream message;
			message << "Failed to allocate " << std::to_string(m_bytes) << " bytes of memory";
			return message.str().c_str();
		}

	private:
		const size_t& m_bytes;
	};
}