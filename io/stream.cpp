#include "shared/io/stream.h"

size_t Stream::read(void* buffer, size_t length)
{
	return read_data(buffer, length);
}

bool Stream::read_bool()
{
	bool value; read_data(&value, sizeof(bool));
	return value;
}

int8_t Stream::read_byte()
{
	int8_t value; read_data(&value, sizeof(int8_t));
	return value;
}

uint8_t Stream::read_unsigned_byte()
{
	uint8_t value; read_data(&value, sizeof(uint8_t));
	return value;
}

int16_t Stream::read_short(Endian endian)
{
	int16_t value; read_data(&value, sizeof(int16_t));
	if (!is_endian(endian)) swap_endian(&value);
	return value;
}

uint16_t Stream::read_unsigned_short(Endian endian)
{
	uint16_t value; read_data(&value, sizeof(uint16_t));
	if (!is_endian(endian)) swap_endian(&value);
	return value;
}

int32_t Stream::read_int(Endian endian)
{
	int32_t value; read_data(&value, sizeof(int32_t));
	if (!is_endian(endian)) swap_endian(&value);
	return value;
}

uint32_t Stream::read_unsigned_int(Endian endian)
{
	int32_t value; read_data(&value, sizeof(int32_t));
	if (!is_endian(endian)) value = swap_endian(value);
	return value;
}

int64_t Stream::read_long(Endian endian)
{
	int64_t value; read_data(&value, sizeof(int64_t));
	if (!is_endian(endian)) swap_endian(&value);
	return value;
}

uint64_t Stream::read_unsigned_long(Endian endian)
{
	uint64_t value; read_data(&value, sizeof(uint64_t));
	if (!is_endian(endian)) swap_endian(&value);
	return value;
}

float Stream::read_float(Endian endian)
{
	float value; read_data(&value, sizeof(float));
	if (!is_endian(endian)) swap_endian(&value);
	return value;
}

double Stream::read_double(Endian endian)
{
	double value; read_data(&value, sizeof(double));
	if (!is_endian(endian)) swap_endian(&value);
	return value;
}

std::string Stream::read_string(int32_t length)
{
	std::string result;

	if (length < 0)
	{
		char sym;
		while (read(&sym, 1) && sym != '\0') result += sym;
	}
	else
	{
		for (int i = 0; i < length; i++) result += read_byte();
		result += '\0';
	}

	return result;
}

size_t Stream::write(const void* buffer, size_t length)
{
	return write_data(buffer, length);
}

size_t Stream::write_bool(bool value)
{
	return write_data(&value, sizeof(bool));
}

size_t Stream::write_byte(int8_t value)
{
	return write_data(&value, sizeof(int8_t));
}

size_t Stream::write_unsigned_byte(uint8_t value)
{
	return write_data(&value, sizeof(uint8_t));
}

size_t Stream::write_short(int16_t value, Endian endian)
{
	if (!is_endian(endian)) swap_endian(&value);
	return write_data(&value, sizeof(int16_t));
}

size_t Stream::write_unsigned_short(uint16_t value, Endian endian)
{
	if (!is_endian(endian)) swap_endian(&value);
	return write_data(&value, sizeof(uint16_t));
}

size_t Stream::write_int(int32_t value, Endian endian)
{
	if (!is_endian(endian)) swap_endian(&value);
	return write_data(&value, sizeof(int32_t));
}

size_t Stream::write_unsigned_int(uint32_t value, Endian endian)
{
	if (!is_endian(endian)) swap_endian(&value);
	return write_data(&value, sizeof(uint32_t));
}

size_t Stream::write_long(int64_t value, Endian endian)
{
	if (!is_endian(endian)) swap_endian(&value);
	return write_data(&value, sizeof(int64_t));
}

size_t Stream::write_unsigned_long(uint64_t value, Endian endian)
{
	if (!is_endian(endian)) swap_endian(&value);
	return write_data(&value, sizeof(uint64_t));
}

size_t Stream::write_float(float value, Endian endian)
{
	if (!is_endian(endian)) swap_endian(&value);
	return write_data(&value, sizeof(float));
}

size_t Stream::write_double(double value, Endian endian)
{
	if (!is_endian(endian)) swap_endian(&value);
	return write_data(&value, sizeof(double));
}

size_t Stream::write_string(std::string str)
{
	return write_data(str.c_str(), str.size() + 1);
}