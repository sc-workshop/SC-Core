#include "shared/io/memory_stream.h"

MemoryStream::MemoryStream(uint8_t* data, size_t length)
{
	m_data = data;
	m_const_data = nullptr;

	m_length = length;
	m_position = 0;
}

MemoryStream::MemoryStream(const uint8_t* data, size_t length)
{
	m_data = nullptr;
	m_const_data = data;

	m_length = length;
	m_position = 0;
}

MemoryStream::~MemoryStream()
{
	if (m_data)
	{
		delete[] m_data;
		m_data = nullptr;
	}

	if (m_const_data)
	{
		delete[] m_const_data;
		m_const_data = nullptr;
	}

	m_length = 0;
	m_position = 0;
}

void* MemoryStream::data()
{
	return (void*)m_data;
}

const void* MemoryStream::data() const
{
	return (void*)(m_data ? m_data : m_const_data);
}

size_t MemoryStream::length() const
{
	return m_length;
}

size_t MemoryStream::position() const
{
	return m_position;
}

size_t MemoryStream::seek(size_t position)
{
	m_position = position;
	return m_position;
}

bool MemoryStream::is_open() const
{
	return (m_data || m_const_data) && m_length > 0;
}

bool MemoryStream::is_readable() const
{
	return (m_data || m_const_data) && m_length > 0;
}

bool MemoryStream::is_writable() const
{
	return m_data != nullptr && m_length > 0;
}

size_t MemoryStream::read_data(void* ptr, size_t length)
{
	const uint8_t* src = (m_data ? m_data : m_const_data);

	if (src == nullptr || ptr == nullptr || length <= 0 || m_length <= 0 || m_position >= m_length)
		return 0;

	if (length > m_length - m_position)
		length = m_length - m_position;

	memcpy(ptr, src + m_position, length);
	m_position += length;

	return length;
}

size_t MemoryStream::write_data(const void* ptr, size_t length)
{
	if (m_data == nullptr || ptr == nullptr || length <= 0 || m_length <= 0 || m_position >= m_length)
		return 0;

	if (length > m_length - m_position)
		length = m_length - m_position;

	memcpy(m_data + m_position, ptr, length);
	m_position += length;

	return length;
}
