#include "GeneralRuntimeException.h"

namespace sc
{
	class MemoryAllocationException : public GeneralRuntimeException
	{
	public:
		MemoryAllocationException(const size_t& bytes) : m_bytes(bytes)
		{}

		virtual const char* what() const override
		{
			return "Failed to allocate " std::to_string(m_bytes) " bytes of memory";
		}

	private:
		const size_t& m_bytes
	};
}