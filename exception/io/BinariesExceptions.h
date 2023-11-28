#pragma once

#include "exception/GeneralRuntimeException.h"
#include <iomanip>

namespace sc
{
	class BadMagicException : public GeneralRuntimeException
	{
	public:
		BadMagicException(uint8_t* expected_magic, uint8_t* magic, size_t size)
		{
			std::stringstream message;
			message << "Magic bytes is not same. Excepted ";
			for (size_t i = 0; size > i; i++)
			{
				message << std::setfill('0') << std::setw(2) << std::hex << (0xff & (unsigned int)*(expected_magic + i));
			}

			message << ", Get ";

			for (size_t i = 0; size > i; i++)
			{
				message << std::setfill('0') << std::setw(2) << std::hex << (0xff & (unsigned int)*(magic + i));
			}

			m_message = message.str();
		}
	};
}