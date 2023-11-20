#include "image.h"
#include <math.h>

#include "stb/stb.h"

namespace sc
{
	//			<---------------- Const members ---------------->
	const Image::PixelDepthInfo Image::PixelDepthTable[] =
	{
		{4, 8, 8, 8, 8},	//RGBA8
		{2, 4, 4, 4, 4},	//RGBA4
		{2, 5, 5, 5, 1},	//RGB5_A1
		{2, 5, 6, 5, 0xFF},	//RGB565
		{2, 8, 0, 0, 8},	//LUMINANCE8_ALPHA8
		{1, 8, 0, 0, 0xFF},	//LUMINANCE8
	};

	const Image::BasePixelType Image::PixelDepthBaseTypeTable[] =
	{
		Image::BasePixelType::RGBA, //RGBA8
		Image::BasePixelType::RGBA,	//RGBA4
		Image::BasePixelType::RGBA,	//RGB5_A1
		Image::BasePixelType::RGB,	//RGB565
		Image::BasePixelType::LA,	//LUMINANCE8_ALPHA8
		Image::BasePixelType::L,	//LUMINANCE8
	};

	//			<---------------- Static members ---------------->
	size_t Image::calculate_image_length(uint16_t width, uint16_t height, PixelDepth depth)
	{
		uint8_t pixel_size = PixelDepthTable[(uint16_t)depth].byte_count;
		return (width * height) * pixel_size;
	}

	bool Image::check_depth_base_type(Image::BasePixelType type, Image::PixelDepth depth)
	{
		Image::BasePixelType depth_base_type = Image::PixelDepthBaseTypeTable[(uint16_t)depth];

		return depth_base_type == type;
	}

	//			<---------------- Function declarations ---------------->
	void Image::resize(
		uint8_t* input_data, uint8_t* output_data,
		uint16_t width, uint16_t height,
		uint16_t new_width, uint16_t new_height,
		BasePixelType type, PixelDepth depth, ColorSpace space,
		bool premultiply
	)
	{
		bool has_alpha = type == BasePixelType::LA || type == BasePixelType::RGBA;

		stbir__resize_arbitrary(NULL,
			input_data, width, height, 0,
			output_data, new_width, new_height, 0,
			0, 0, 1, 1, NULL,
			(uint8_t)type, has_alpha ? (uint8_t)type - 1 : -1, premultiply ? STBIR_FLAG_ALPHA_PREMULTIPLIED : 0, STBIR_TYPE_UINT8, STBIR_FILTER_DEFAULT, STBIR_FILTER_DEFAULT,
			STBIR_EDGE_CLAMP, STBIR_EDGE_CLAMP, space == Image::ColorSpace::Linear ? STBIR_COLORSPACE_LINEAR : STBIR_COLORSPACE_SRGB
		);
	};

	void Image::remap(
		uint8_t* input_data, uint8_t* output_data,
		uint16_t width, uint16_t height,
		Image::PixelDepth source, Image::PixelDepth destination
	)
	{
		uint64_t pixel_count = width * height;

		const PixelDepthInfo& input_pixel_info = PixelDepthTable[(uint16_t)source];
		const PixelDepthInfo& output_pixel_info = PixelDepthTable[(uint16_t)destination];

		for (uint64_t pixel_index = 0; pixel_count > pixel_index; pixel_index++)
		{
			uint64_t input_pixel_buffer;
			uint64_t output_pixel_buffer;

			uint8_t* input_pixel_data = input_data + (pixel_index * input_pixel_info.byte_count);
			uint8_t* output_pixel_data = output_data + (pixel_index * output_pixel_info.byte_count);

			// Copy pixel bytes to end of buffer
			memcopy(
				input_pixel_data,
				&input_pixel_buffer + (sizeof(input_pixel_buffer) - input_pixel_info.byte_count),
				input_pixel_info.byte_count
			);

			uint16_t r_channel = 0;
			uint16_t g_channel = 0;
			uint16_t b_channel = 0;
			uint16_t a_channel = 0;

			// Pixel decoding
			{
				uint8_t bit_index = 0;

				// Small trick for LA/L pixels. Helps for LA -> RGBA remap cases
				uint8_t last_bits_count = 0;
				{
					uint64_t r_bits_mask = pow(2, input_pixel_info.r_bits) - 1;
					r_channel = r_bits_mask & input_pixel_buffer;
					bit_index += input_pixel_info.r_bits;
					last_bits_count = input_pixel_info.r_bits;
				}

				{
					uint64_t g_bits_mask = pow(
						2,
						input_pixel_info.g_bits ? last_bits_count = input_pixel_info.g_bits : last_bits_count
					) - 1;

					g_channel = (g_bits_mask << bit_index) & input_pixel_buffer;
					bit_index += input_pixel_info.r_bits;
				}

				{
					uint64_t b_bits_mask = pow(
						2,
						input_pixel_info.b_bits ? last_bits_count = input_pixel_info.b_bits : last_bits_count
					) - 1;

					b_channel = (b_bits_mask << bit_index) & input_pixel_buffer;
					bit_index += input_pixel_info.b_bits;
				}

				{
					if (input_pixel_info.a_bits != 0xFF)
					{
						uint64_t a_bits_mask = pow(
							2,
							input_pixel_info.a_bits ? last_bits_count = input_pixel_info.a_bits : last_bits_count
						) - 1;

						a_channel = (a_bits_mask << bit_index) & input_pixel_buffer;
					}
					else
					{
						a_channel = 0xFFFF;
					}
				}
			}

			// TODO: yeah
			// Pixel Encoding
			{
			}
		}
	}

	uint16_t Image::width() const
	{
		return m_width;
	};

	uint16_t Image::height() const
	{
		return m_height;
	};
}