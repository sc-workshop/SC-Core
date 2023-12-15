#pragma once

#include "../GeneralRuntimeException.h"

namespace sc
{
	SC_CONSTRUCT_PARENT_EXCEPTION(GeneralRuntimeException, IOGeneralException, "Failed to make I/O operation");
}