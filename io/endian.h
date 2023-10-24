#pragma once

enum class Endian
{
	Little,
	Big
};

template<typename T>
constexpr T swap_endian(T value)
{
	union
	{
		T value;
		char array[sizeof(T)];
	} src, dst;

	src.value = value;

	for (size_t i = 0; i < sizeof(T); i++)
		dst.array[i] = src.array[sizeof(T) - i - 1];

	return dst.value;
}

inline bool is_big_endian()
{
	return (*((int16_t*)"AB") == 0x4243);
}

inline bool is_little_endian()
{
	return (*((int16_t*)"AB") != 0x4243);
}

inline bool is_endian(const Endian& endian)
{
	return (endian == Endian::Little && is_little_endian()) || (endian == Endian::Big && is_big_endian());
}
