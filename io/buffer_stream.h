#pragma once

#include <vector>

#include "shared/io/stream.h"

class BufferStream : public Stream
{
public:
	BufferStream() = default;
	BufferStream(int capacity);

	virtual ~BufferStream() = default;

public:
	void* data() override;
	const void* data() const override;

	size_t length() const override;

	size_t position() const override;
	size_t seek(size_t position) override;

	bool is_open() const override;
	bool is_readable() const override;
	bool is_writable() const override;

public:
	void resize(size_t length);
	void clear();

protected:
	size_t read_data(void* ptr, size_t length) override;
	size_t write_data(const void* ptr, size_t length) override;

private:
	std::vector<uint8_t> m_buffer;
	size_t m_position = 0;
};
