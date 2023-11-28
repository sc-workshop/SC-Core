#pragma once

#include "IOGeneralException.h"

namespace sc
{
	class WriteFileException : public IOGeneralException
	{
	public:
		WriteFileException()
		{
			m_message = "Failed to write data to non-writeable file";
		}
	};
}