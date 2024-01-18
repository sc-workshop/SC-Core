#pragma once

#include <string>

#include "endian.h"

namespace sc
{
	enum class Seek
	{
		Set = 0,
		Add,
	};

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

		virtual size_t length() const = 0;

		virtual size_t position() const = 0;
		virtual size_t seek(size_t position, Seek mode = Seek::Set) = 0;

		virtual bool is_open() const = 0;
		virtual bool is_readable() const = 0;
		virtual bool is_writable() const = 0;

	public:
		size_t read(void* buffer, size_t length)
		{
			return read_data(buffer, length);
		};

		bool read_bool()
		{
			bool value; read_data(&value, sizeof(bool));
			return value;
		};

		int8_t read_byte()
		{
			int8_t value; read_data(&value, sizeof(int8_t));
			return value;
		};
		uint8_t read_unsigned_byte()
		{
			uint8_t value; read_data(&value, sizeof(uint8_t));
			return value;
		};

		int16_t read_short(Endian endian = Endian::Little)
		{
			int16_t value; read_data(&value, sizeof(int16_t));
			if (!is_endian(endian)) swap_endian(&value);
			return value;
		};
		uint16_t read_unsigned_short(Endian endian = Endian::Little)
		{
			uint16_t value; read_data(&value, sizeof(uint16_t));
			if (!is_endian(endian)) swap_endian(&value);
			return value;
		};

		int32_t read_int(Endian endian = Endian::Little)
		{
			int32_t value; read_data(&value, sizeof(int32_t));
			if (!is_endian(endian)) swap_endian(&value);
			return value;
		};
		uint32_t read_unsigned_int(Endian endian = Endian::Little)
		{
			uint32_t value; read_data(&value, sizeof(uint32_t));
			if (!is_endian(endian)) value = swap_endian(value);
			return value;
		};

		int64_t read_long(Endian endian = Endian::Little)
		{
			int64_t value; read_data(&value, sizeof(int64_t));
			if (!is_endian(endian)) swap_endian(&value);
			return value;
		};
		uint64_t read_unsigned_long(Endian endian = Endian::Little)
		{
			uint64_t value; read_data(&value, sizeof(uint64_t));
			if (!is_endian(endian)) swap_endian(&value);
			return value;
		};

		float read_float(Endian endian = Endian::Little)
		{
			float value; read_data(&value, sizeof(float));
			if (!is_endian(endian)) swap_endian(&value);
			return value;
		};
		double read_double(Endian endian = Endian::Little)
		{
			double value; read_data(&value, sizeof(double));
			if (!is_endian(endian)) swap_endian(&value);
			return value;
		};

		std::string read_string(int32_t length = 0)
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
		};

	public:
		size_t write(const void* buffer, size_t length)
		{
			if (length)
			{
				return write_data(buffer, length);
			}
			return 0;
		};

		size_t write_bool(bool value)
		{
			return write_data(&value, sizeof(bool));
		};

		size_t write_byte(int8_t value)
		{
			return write_data(&value, sizeof(int8_t));
		};
		size_t write_unsigned_byte(uint8_t value)
		{
			return write_data(&value, sizeof(uint8_t));
		};

		size_t write_short(int16_t value, Endian endian = Endian::Little)
		{
			if (!is_endian(endian)) value = swap_endian(value);
			return write_data(&value, sizeof(int16_t));
		};
		size_t write_unsigned_short(uint16_t value, Endian endian = Endian::Little)
		{
			if (!is_endian(endian)) value = swap_endian(value);
			return write_data(&value, sizeof(uint16_t));
		};

		size_t write_int(int32_t value, Endian endian = Endian::Little)
		{
			if (!is_endian(endian)) value = swap_endian(value);
			return write_data(&value, sizeof(int32_t));
		};
		size_t write_unsigned_int(uint32_t value, Endian endian = Endian::Little)
		{
			if (!is_endian(endian)) value = swap_endian(value);
			return write_data(&value, sizeof(uint32_t));
		};

		size_t write_long(int64_t value, Endian endian = Endian::Little)
		{
			if (!is_endian(endian)) value = swap_endian(value);
			return write_data(&value, sizeof(int64_t));
		};
		size_t write_unsigned_long(uint64_t value, Endian endian = Endian::Little)
		{
			if (!is_endian(endian)) value = swap_endian(value);
			return write_data(&value, sizeof(uint64_t));
		};

		size_t write_float(float value, Endian endian = Endian::Little)
		{
			if (!is_endian(endian)) value = swap_endian(value);
			return write_data(&value, sizeof(float));
		};
		size_t write_double(double value, Endian endian = Endian::Little)
		{
			if (!is_endian(endian)) value = swap_endian(value);
			return write_data(&value, sizeof(double));
		};

		size_t write_string(std::string str)
		{
			return write_data(str.c_str(), str.size() + 1);
		};

	protected:
		virtual size_t read_data(void* buffer, size_t length) = 0;
		virtual size_t write_data(const void* buffer, size_t length) = 0;
	};
}