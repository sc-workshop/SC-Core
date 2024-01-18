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

constexpr bool is_endian(const Endian& endian)
{
	const char* test_string = "AB";
	const int16_t* test_number = (const int16_t*)test_string;

	return endian == Endian::Little && *test_number == 0x4243 || endian == Endian::Big && *test_number != 0x4243;
}
