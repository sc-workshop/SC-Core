#pragma once

#include <exception>
#include <iostream>

namespace sc
{
	class GeneralRuntimeException : std::exception
	{
	private:
		char* m_file = nullptr;
		int m_line = -1;

	public:
		GeneralRuntimeException() {};
		GeneralRuntimeException(char* file, int line) : m_file(file), m_line(line)
		{}

		virtual const char* what() const
		{
			return "Unknown runtime error";
		}
	};
}