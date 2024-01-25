#pragma once

#include "stream.h"
#include "memory/alloc.h"
#include "exception/MemoryAllocationException.h"

namespace sc
{
	class MemoryStream : public Stream
	{
	public:
		MemoryStream(const MemoryStream&) = delete;
		MemoryStream& operator=(const MemoryStream&) = delete;

	public:
		MemoryStream(size_t length) : m_allocated_data(memalloc(length))
		{
			m_data = m_allocated_data;
			m_length = length;
		}

		MemoryStream(uint8_t* data, size_t length)
		{
			m_data = data;
			m_length = length;
		};

		virtual ~MemoryStream()
		{
			if (m_allocated_data)
			{
				free((void*)m_allocated_data);
			}
		};

	public:
		void* data() const
		{
			return (void*)m_data;
		};

		void* data() override
		{
			return const_cast<void*>(const_cast<const MemoryStream*>(this)->data());
		};

		size_t length() const override
		{
			return m_length;
		};

		size_t position() const override
		{
			return m_position;
		};
		size_t seek(size_t position, Seek mode = Seek::Set) override
		{
			switch (mode)
			{
			case Seek::Set:
				m_position = position;
				break;
			case Seek::Add:
				m_position += position;
				break;
			default:
				break;
			}

			return m_position;
		};

		bool is_open() const override
		{
			return m_data != nullptr && m_length > 0;
		};
		bool is_readable() const override
		{
			return m_data != nullptr && m_length > 0;
		};
		bool is_writable() const override
		{
			return m_data != nullptr && m_length > 0;
		};

	protected:
		size_t read_data(void* ptr, size_t length) override
		{
			if (m_data == nullptr || ptr == nullptr || length <= 0 || m_length <= 0 || m_position >= m_length)
				return 0;

			if (length > m_length - m_position)
				length = m_length - m_position;

			memcpy(ptr, m_data + m_position, length);
			m_position += length;

			return length;
		};

		size_t write_data(const void* ptr, size_t length) override
		{
			if (m_data == nullptr || ptr == nullptr || length <= 0 || m_length <= 0 || m_position >= m_length)
				return 0;

			if (length > m_length - m_position)
				length = m_length - m_position;

			memcpy(m_data + m_position, ptr, length);
			m_position += length;

			return length;
		};

	private:
		uint8_t* m_data;
		uint8_t* const m_allocated_data = nullptr;

		size_t m_length = 0;
		size_t m_position = 0;
	};
}
