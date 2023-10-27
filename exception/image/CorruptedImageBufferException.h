#include "GeneralRuntimeException.h"

namespace sc
{
	class CorruptedImageBufferException : public GeneralRuntimeException
	{
	public:
		virtual const char* what() const override
		{
			return "Image buffer is corrupted";
		}
	};
}