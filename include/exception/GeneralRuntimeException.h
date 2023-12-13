#pragma once

#include <exception>
#include <sstream>
#include <iostream>

#define SC_CONSTRUCT_CHILD_EXCEPTION(Parent, Name, Message) \
class Name : public Parent \
{ \
public: \
	Name() \
	{ \
		m_message = Message; \
	} \
}

#define SC_CONSTRUCT_SIMPLE_EXCEPTION(Name, Message) SC_CONSTRUCT_CHILD_EXCEPTION(GeneralRuntimeException, Name, Message)

namespace sc
{
	class GeneralRuntimeException : public std::exception
	{
	public:
		virtual const char* what() const override
		{
			return m_message.c_str();
		};

	protected:
		std::string m_message = "Unknown runtime error";
	};
}