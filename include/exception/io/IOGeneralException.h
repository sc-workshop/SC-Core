#pragma once

#include "../GeneralRuntimeException.h"

namespace sc
{
	//class IOGeneralException : public GeneralRuntimeException
	//{
	//public:
	//	IOGeneralException(const char* type_name = nullptr, uint16_t call_offset = 1) : GeneralRuntimeException(type_name == nullptr ? "IOGeneralException" : type_name, call_offset)
	//	{
	//		m_message = "Failed to make I/O operation";
	//	}
	//};

	SC_CONSTRUCT_PARENT_EXCEPTION(GeneralRuntimeException, IOGeneralException, "Failed to make I/O operation");
}