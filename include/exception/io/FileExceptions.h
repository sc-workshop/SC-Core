#pragma once
#include <filesystem>

#include "IOGeneralException.h"

namespace sc
{
	class FileExistException : public IOGeneralException
	{
	public:
		FileExistException(const std::filesystem::path& path)
		{
			std::stringstream message;
			message << "File does not exist: " << path;
			m_message = message.str();
		}
	};

	SC_CONSTRUCT_CHILD_EXCEPTION(IOGeneralException, ReadFileException, "Failed to read data from non-readable file");
	SC_CONSTRUCT_CHILD_EXCEPTION(IOGeneralException, WriteFileException, "Failed to write data to non-writeable file");
}