#pragma once

#include <string>

#include "shared/io/endian.h"

class Stream
{
public:
	Stream() = default;
	
	// Non-copyable
	Stream(const Stream&) = delete;
	Stream& operator=(const Stream&) = delete;

	virtual ~Stream() = default;

public:
	virtual void* data() = 0;
	virtual const void* data() const = 0;

	virtual size_t length() const = 0;

	virtual size_t position() const = 0;
	virtual size_t seek(size_t position) = 0;

	virtual bool is_open() const = 0;
	virtual bool is_readable() const = 0;
	virtual bool is_writable() const = 0;

public:
	size_t read(void* buffer, size_t length);

	bool read_bool();

	int8_t read_byte();
	uint8_t read_unsigned_byte();

	int16_t read_short(Endian endian);
	uint16_t read_unsigned_short(Endian endian);

	int32_t read_int(Endian endian);
	uint32_t read_unsigned_int(Endian endian);

	int64_t read_long(Endian endian);
	uint64_t read_unsigned_long(Endian endian);

	float read_float(Endian endian);
	double read_double(Endian endian);

	std::string read_string(int32_t length);

public:
	size_t write(const void* buffer, size_t length);

	size_t write_bool(bool value);

	size_t write_byte(int8_t value);
	size_t write_unsigned_byte(uint8_t value);

	size_t write_short(int16_t value, Endian endian);
	size_t write_unsigned_short(uint16_t value, Endian endian);

	size_t write_int(int32_t value, Endian endian);
	size_t write_unsigned_int(uint32_t value, Endian endian);

	size_t write_long(int64_t value, Endian endian);
	size_t write_unsigned_long(uint64_t value, Endian endian);

	size_t write_float(float value, Endian endian);
	size_t write_double(double value, Endian endian);

	size_t write_string(std::string str);

protected:
	virtual size_t read_data(void* buffer, size_t length) = 0;
	virtual size_t write_data(const void* buffer, size_t length) = 0;
};
