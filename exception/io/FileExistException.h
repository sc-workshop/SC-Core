#pragma once
#include <filesystem>

#include "IOGeneralException.h"

namespace sc
{
	class FileExistException : public IOGeneralException
	{
	public:
		FileExistException(const std::filesystem::path& path) : m_path(path.string())
		{
		}

	public:
		virtual const char* what() const override
		{
			std::stringstream message;
			message << "File does not exist: " << m_path;
			return message.str().c_str();
		};

	private:
		const std::string m_path;
	};
}