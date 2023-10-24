#pragma once

#include "shared/io/stream.h"

class MemoryStream : public Stream
{
public:
	MemoryStream() = default;

	MemoryStream(uint8_t* data, size_t length);
	MemoryStream(const uint8_t* data, size_t length);

	virtual ~MemoryStream();

public:
	void* data() override;
	const void* data() const override;

	size_t length() const override;

	size_t position() const override;
	size_t seek(size_t position) override;

	bool is_open() const override;
	bool is_readable() const override;
	bool is_writable() const override;

protected:
	size_t read_data(void* ptr, size_t length) override;
	size_t write_data(const void* ptr, size_t length) override;

private:
	uint8_t* m_data = nullptr;
	const uint8_t* m_const_data = nullptr;

	size_t m_length = 0;
	size_t m_position = 0;
};
