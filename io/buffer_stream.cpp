#include "shared/io/buffer_stream.h"

BufferStream::BufferStream(int capacity)
{
	m_buffer.resize(capacity);
}

void* BufferStream::data()
{
	return (void*)m_buffer.data();
}

const void* BufferStream::data() const
{
	return data();
}

size_t BufferStream::length() const
{
	return m_buffer.size();
}

size_t BufferStream::position() const
{
	return m_position;
}

size_t BufferStream::seek(size_t position)
{
	return m_position = (position < 0 ? 0 : (position > m_buffer.size() ? m_buffer.size() : position));
}

bool BufferStream::is_open() const
{
	return true;
}

bool BufferStream::is_readable() const
{
	return true;
}

bool BufferStream::is_writable() const
{
	return true;
}

void BufferStream::resize(size_t length)
{
	m_buffer.resize(length);
}

void BufferStream::clear()
{
	m_buffer.clear();
	m_position = 0;
}

size_t BufferStream::read_data(void* ptr, size_t length)
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
}

size_t BufferStream::write_data(const void* ptr, size_t length)
{
	size_t old_size = m_buffer.size();
	m_buffer.resize(old_size + length);

	std::memcpy(&m_buffer[old_size], ptr, length);

	m_position += length;

	return length;
}
