#pragma once

#include "IOGeneralException.h"

namespace sc
{
	class ReadFileException : public IOGeneralException
	{
	public:
		ReadFileException()
		{
			m_message = "Failed to read data from non-readable file";
		}
	};
}