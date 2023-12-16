#pragma once

#include <exception>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cpptrace/cpptrace.hpp>

#define SC_CONSTRUCT_CHILD_EXCEPTION_CLASS(Parent, Name, Message, Args, Definition) \
class Name final : public Parent \
{ \
public: \
	Name(Args) : Parent(#Name, 1) \
	{ \
		Definition \
	} \
}

#define SC_CONSTRUCT_PARENT_EXCEPTION(Parent, Name, BaseMessage) \
class Name : public Parent \
{ \
public: \
	Name(const char* type_name = nullptr, uint16_t call_offset = 1) : Parent(type_name == nullptr ? #Name : type_name, call_offset) \
	{ \
		m_message = BaseMessage; \
	} \
}

#define SC_CONSTRUCT_CHILD_EXCEPTION(Parent, Name, Message) SC_CONSTRUCT_CHILD_EXCEPTION_CLASS(Parent, Name, Message, , m_message = ##Message;)
#define SC_CONSTRUCT_SIMPLE_EXCEPTION(Name, Message) SC_CONSTRUCT_CHILD_EXCEPTION(GeneralRuntimeException, Name, Message)

namespace sc
{
	class GeneralRuntimeException : public std::exception
	{
	public:
		static inline cpptrace::raw_trace init_trace{};

	public:
		GeneralRuntimeException() = delete;

		GeneralRuntimeException(const char* type_name = "Exception", uint16_t call_offset = 1) : m_trace_holder(cpptrace::generate_raw_trace(call_offset + 1, 0xFF)), m_typename(type_name)
		{};

		virtual ~GeneralRuntimeException() = default;

	public:
		virtual const char* what() const noexcept
		{
			return m_message.c_str();
		};

		virtual cpptrace::stacktrace& trace() const noexcept
		{
			return m_trace_holder.get_resolved_trace();
		}

		virtual const char* message() noexcept
		{
			if (m_trace_message.empty())
			{
				std::stringstream message;
				cpptrace::stacktrace& traceback = m_trace_holder.get_resolved_trace();

				message << "Traceback (most recent call last):" << std::endl;

				size_t ib = traceback.frames.size() - 1;
				for (size_t i = 0; traceback.frames.size() > i; i++, ib--)
				{
					const cpptrace::stacktrace_frame& frame = traceback.frames[ib];

					if (ib == 0)
					{
						message << std::endl;
					}

					message << "  File \"" << (frame.filename.empty() ? "Unknown" : frame.filename) << "\"";

					if (frame.is_inline)
					{
						message << ", inlined function " << frame.line.value();
					}

					if (frame.line.has_value())
					{
						message << ", line " << frame.line.value();
					}

					message << ", in ";
					if (!frame.symbol.empty())
					{
						message << frame.symbol;
					}
					else
					{
						message << "0x";

						for (size_t t = 0; sizeof(cpptrace::frame_ptr) > t; t++)
						{
							message << std::setfill('0') << std::setw(2) << std::hex << (0xff & (unsigned int)*(&frame.address + t));
						}
					}

					message << std::endl;
				}

				message << std::endl << m_typename << ": " << m_message << std::endl;

				m_trace_message = message.str();
			}

			return m_trace_message.c_str();
		}

	protected:
		mutable cpptrace::detail::lazy_trace_holder m_trace_holder;

		const char* m_typename;
		std::string m_message = "Unknown runtime error";

		std::string m_trace_message;
	};
}