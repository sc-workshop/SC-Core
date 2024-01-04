#pragma once
#include "image.h"

namespace sc
{
	class CompressedImage : public Image
	{
	public:
		CompressedImage() = default;
		virtual ~CompressedImage() = default;

	public:
		virtual size_t decompressed_data_length() = 0;
		virtual void decompress_data(Stream& buffer) = 0;
	};
}