#pragma once

#include "exception/GeneralRuntimeException.h"

namespace sc
{
	SC_CONSTRUCT_SIMPLE_EXCEPTION(ImageInvalidParamsException, "Image params is corrupted or incorrect");
	SC_CONSTRUCT_SIMPLE_EXCEPTION(CorruptedImageBufferException, "Image buffer is corrupted");
}