#pragma once

#include <stdint.h>
#include "io/stream.h"

namespace sc
{
	class Image
	{
	public:
		const enum class BasePixelType : uint8_t
		{
			RGBA = 4,
			RGB = 3,
			LA = 2,
			L = 1,
		};

		const enum class ColorSpace : uint8_t
		{
			Linear = 0,
			sRGB,
		};

		struct PixelDepthInfo
		{
			uint8_t byte_count;
			uint8_t r_bits;
			uint8_t g_bits;
			uint8_t b_bits;
			uint8_t a_bits;
		};

		static const PixelDepthInfo PixelDepthTable[];

		static const BasePixelType PixelDepthBaseTypeTable[];

		const enum class PixelDepth : uint16_t
		{
			RGBA8 = 0,
			RGBA4,
			RGB5_A1,
			RGB8,
			RGB565,
			LUMINANCE8_ALPHA8,
			LUMINANCE8
		};

	public:
		static size_t calculate_image_length(uint16_t width, uint16_t height, PixelDepth depth);

		static bool check_depth_base_type(BasePixelType type, PixelDepth depth);

		/// <summary>
		/// !! Input Image Data depth must be RGBA8, RGB8, LA8 or L !!
		/// </summary>
		/// <param name="input_data"></param>
		/// <param name="output_data"></param>
		/// <param name="width"></param>
		/// <param name="height"></param>
		/// <param name="new_width"></param>
		/// <param name="new_height"></param>
		/// <param name="type"></param>
		/// <param name="depth"></param>
		/// <param name="space"></param>
		/// <param name="premultiply"></param>
		static void resize(
			uint8_t* input_data, uint8_t* output_data,
			uint16_t width, uint16_t height,
			uint16_t new_width, uint16_t new_height,
			BasePixelType type, ColorSpace space,
			bool premultiply = true
		);

		static void remap(
			uint8_t* input_data, uint8_t* output_data,
			uint16_t width, uint16_t height,
			PixelDepth source, PixelDepth destination
		);

	public:
		virtual void write(Stream& buffer) = 0;

	public:
		virtual uint16_t width() const;
		virtual uint16_t height() const;

		virtual BasePixelType base_type() const = 0;
		virtual ColorSpace colorspace() const = 0;
		virtual PixelDepth depth() const = 0;

		virtual size_t data_length() const = 0;
		virtual uint8_t* data() const = 0;

		virtual bool is_compressed() const = 0;

	protected:
		uint16_t m_width = 0;
		uint16_t m_height = 0;
	};
}