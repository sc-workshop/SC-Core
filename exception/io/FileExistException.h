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
}