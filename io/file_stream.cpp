#include "shared/io/file_stream.h"

InputFileStream::InputFileStream(const fs::path& path)
{
	m_file.open(path.c_str(), std::ios_base::binary);

	m_file.seekg(0, std::ios::end);
	m_file_size = static_cast<size_t>(m_file.tellg());
	m_file.seekg(0);
}

void* InputFileStream::data()
{
	size_t saved_position = position();

	uint8_t* buffer = new uint8_t[m_file_size];

	m_file.seekg(0);
	read_data(buffer, m_file_size);
	m_file.seekg(saved_position);

	return (void*)buffer;
}

const void* InputFileStream::data() const
{
	return data();
}

size_t InputFileStream::length() const
{
	return m_file_size;
}

size_t InputFileStream::position()
{
	return static_cast<size_t>(m_file.tellg());
}

size_t InputFileStream::position() const
{
	return this->position();
}

size_t InputFileStream::seek(size_t position)
{
	m_file.seekg(position);
	return this->position();
}

bool InputFileStream::is_open() const
{
	return true;
}

bool InputFileStream::is_readable() const
{
	return true;
}

bool InputFileStream::is_writable() const
{
	return false;
}

size_t InputFileStream::read_data(void* ptr, size_t length)
{
	size_t to_read = (position() + length) > this->length() ? this->length() - position() : length;

	m_file.read((char*)ptr, to_read);

	return to_read;
}

size_t InputFileStream::write_data(const void* ptr, size_t length)
{
	return 0;
}

OutputFileStream::OutputFileStream(const fs::path& path)
{
	m_file.open(path, std::ios_base::binary);

	m_file.seekp(0, std::ios::end);
	m_file_size = static_cast<size_t>(m_file.tellp());
	m_file.seekp(0);
}

void* OutputFileStream::data()
{
	// TODO(pavidloq): getting data from std::ofstream
	return nullptr;
}

const void* OutputFileStream::data() const
{
	return data();
}

size_t OutputFileStream::length() const
{
	return m_file_size;
}

size_t OutputFileStream::position()
{
	return m_file.tellp();
}

size_t OutputFileStream::position() const
{
	return this->position();
}

size_t OutputFileStream::seek(size_t position)
{
	m_file.seekp(position);
	return this->position();
}

bool OutputFileStream::is_open() const
{
	return true;
}

bool OutputFileStream::is_readable() const
{
	return false;
}

bool OutputFileStream::is_writable() const
{
	return true;
}

size_t OutputFileStream::read_data(void* ptr, size_t length)
{
	return 0;
}

size_t OutputFileStream::write_data(const void* ptr, size_t length)
{
	size_t pos = m_file.tellp();

	m_file.write((char*)ptr, length);

	const size_t result = (size_t)m_file.tellp() - pos;
	m_file_size += result;

	return result;
}
