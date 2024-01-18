#pragma once

#include <vector>

#include "stream.h"

namespace sc
{
	class BufferStream : public Stream
	{
	public:
		BufferStream(const BufferStream&) = delete;
		BufferStream& operator=(const BufferStream&) = delete;

	public:
		BufferStream() = default;
		BufferStream(size_t capacity)
		{
			m_buffer.resize(capacity);
		};

		virtual ~BufferStream() = default;

	public:
		void* data() const
		{
			return (void*)m_buffer.data();
		};

		void* data() override
		{
			return const_cast<void*>(const_cast<const BufferStream*>(this)->data());
		};

		size_t length() const override
		{
			return m_buffer.size();
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
				m_position = position > m_buffer.size() ? m_buffer.size() : position;
				break;
			case Seek::Add:
				m_position = m_position + position > length() ? length() : m_position + position;
				break;
			default:
				break;
			}

			return m_position;
		};

		bool is_open() const override
		{
			return true;
		};
		bool is_readable() const override
		{
			return true;
		};
		bool is_writable() const override
		{
			return true;
		};

	public:
		void resize(size_t length)
		{
			m_buffer.resize(length);
		};

		void clear()
		{
			m_buffer.clear();
			m_position = 0;
		};

	protected:
		size_t read_data(void* ptr, size_t length) override
		{
			if (length == 0 || m_position >= this->length())
			{
				return 0;
			}

			size_t result = this->length() - m_position;

			if (result > length)
			{
				result = length;
			}

			std::memcpy(ptr, m_buffer.data() + m_position, result);

			m_position += result;

			return result;
		};

		size_t write_data(const void* ptr, size_t length) override
		{
			size_t old_size = m_buffer.size();
			m_buffer.resize(old_size + length);

			std::memcpy(&m_buffer[old_size], ptr, length);

			m_position += length;

			return length;
		};

	private:
		std::vector<uint8_t> m_buffer;
		size_t m_position = 0;
	};
}
