#pragma once

#include "../GeneralRuntimeException.h"

namespace sc
{
	class IOGeneralException : public GeneralRuntimeException
	{
	public:
		IOGeneralException()
		{
			m_message = "Failed to make I/O operation";
		}
	};
}