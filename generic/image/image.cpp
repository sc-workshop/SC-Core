#include "image.h"
#include "stb/stb.h"

namespace sc
{
	//			<---------------- Const members ---------------->
	const Image::PixelDepthInfo Image::PixelDepthTable[] =
	{
		{4, 8, 8, 8, 8},			//RGBA8
		{2, 4, 4, 4, 4},			//RGBA4
		{2, 5, 5, 5, 1},			//RGB5_A1
		{3, 8, 8, 8, 0xFF},			//RGB8
		{2, 5, 6, 5, 0xFF},			//RGB565
		{2, 8, 0xFF, 0xFF, 8},		//LUMINANCE8_ALPHA8
		{1, 8, 0xFF, 0xFF, 0xFF},	//LUMINANCE8
	};

	const Image::BasePixelType Image::PixelDepthBaseTypeTable[] =
	{
		Image::BasePixelType::RGBA, //RGBA8
		Image::BasePixelType::RGBA,	//RGBA4
		Image::BasePixelType::RGBA,	//RGB5_A1
		Image::BasePixelType::RGB,	//RGB8
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
		BasePixelType type, ColorSpace space,
		bool premultiply
	)
	{
		bool has_alpha = type == BasePixelType::LA || type == BasePixelType::RGBA;

		stbir_resize_uint8_generic(
			input_data, width, height, 0,
			output_data, new_width, new_height, 0,
			(uint8_t)type, has_alpha ? (uint8_t)type - 1 : -1, premultiply ? STBIR_FLAG_ALPHA_PREMULTIPLIED : 0, STBIR_EDGE_CLAMP,
			STBIR_FILTER_DEFAULT, space == Image::ColorSpace::Linear ? STBIR_COLORSPACE_LINEAR : STBIR_COLORSPACE_SRGB, NULL
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
			uint32_t input_pixel_buffer = 0;
			uint32_t output_pixel_buffer = 0;

			uint8_t* input_pixel_data = input_data + (pixel_index * input_pixel_info.byte_count);
			uint8_t* output_pixel_data = output_data + (pixel_index * output_pixel_info.byte_count);

			memcopy(
				input_pixel_data,
				(uint8_t*)(&input_pixel_buffer),
				input_pixel_info.byte_count
			);

			uint8_t r_channel = 0;
			uint8_t g_channel = 0;
			uint8_t b_channel = 0;
			uint8_t a_channel = 0;

			// Pixel Decoding
			{
				uint8_t bit_index = 0;

				if (input_pixel_info.r_bits != 0xFF)
				{
					uint64_t r_bits_mask = (uint64_t)pow(2, input_pixel_info.r_bits) - 1;
					r_channel = static_cast<uint8_t>(r_bits_mask & input_pixel_buffer);
					bit_index += input_pixel_info.r_bits;
				}

				if (input_pixel_info.g_bits != 0xFF)
				{
					uint64_t g_bits_mask = (uint64_t)pow(2, input_pixel_info.g_bits) - 1;
					g_channel = static_cast<uint8_t>(((g_bits_mask << bit_index) & input_pixel_buffer) >> bit_index);
					bit_index += input_pixel_info.g_bits;
				}
				else
				{
					g_channel = r_channel;
				}

				if (input_pixel_info.b_bits != 0xFF)
				{
					uint64_t b_bits_mask = (uint64_t)pow(2, input_pixel_info.b_bits) - 1;
					b_channel = static_cast<uint8_t>(((b_bits_mask << bit_index) & input_pixel_buffer) >> bit_index);
					bit_index += input_pixel_info.b_bits;
				}
				else
				{
					b_channel = g_channel;
				}

				if (input_pixel_info.a_bits != 0xFF)
				{
					uint64_t a_bits_mask = (uint64_t)pow(2, input_pixel_info.a_bits) - 1;
					a_channel = static_cast<uint8_t>(((a_bits_mask << bit_index) & input_pixel_buffer) >> bit_index);
				}
				else
				{
					a_channel = 0xFF;
				}
			}

			// Some Pixel Type Specific actions
			switch (destination)
			{
			case sc::Image::PixelDepth::LUMINANCE8_ALPHA8:
			case sc::Image::PixelDepth::LUMINANCE8:
				r_channel = (r_channel * g_channel * b_channel) / 3;
				break;
			default:
				break;
			}

			// Pixel Encoding
			{
				uint8_t bit_index = output_pixel_info.byte_count * 8;

				if (output_pixel_info.a_bits != 0xFF)
				{
					bit_index -= output_pixel_info.a_bits;
					int8_t bit_offset = (input_pixel_info.a_bits - output_pixel_info.a_bits) >= 0 ? input_pixel_info.a_bits - output_pixel_info.a_bits : 0;
					uint64_t bits_mask = (uint64_t)((pow(2, output_pixel_info.a_bits) - 1)) << bit_offset;
					output_pixel_buffer |= ((a_channel & bits_mask) >> bit_offset) << bit_index;
				}

				if (output_pixel_info.r_bits != 0xFF)
				{
					bit_index -= output_pixel_info.r_bits;
					int8_t bit_offset = (input_pixel_info.r_bits - output_pixel_info.r_bits) >= 0 ? input_pixel_info.r_bits - output_pixel_info.r_bits : 0;
					uint64_t bits_mask = (uint64_t)((pow(2, output_pixel_info.r_bits) - 1)) << bit_offset;
					output_pixel_buffer |= ((r_channel & bits_mask) >> bit_offset) << bit_index;
				}

				if (output_pixel_info.g_bits != 0xFF)
				{
					bit_index -= output_pixel_info.g_bits;
					int8_t bit_offset = (input_pixel_info.g_bits - output_pixel_info.g_bits) >= 0 ? input_pixel_info.g_bits - output_pixel_info.g_bits : 0;
					uint64_t bits_mask = (uint64_t)((pow(2, output_pixel_info.g_bits) - 1)) << bit_offset;
					output_pixel_buffer |= ((g_channel & bits_mask) >> bit_offset) << bit_index;
				}

				if (output_pixel_info.b_bits != 0xFF)
				{
					bit_index -= output_pixel_info.b_bits;
					int8_t bit_offset = (input_pixel_info.b_bits - output_pixel_info.b_bits) >= 0 ? input_pixel_info.b_bits - output_pixel_info.b_bits : 0;
					uint64_t bits_mask = (uint64_t)((pow(2, output_pixel_info.b_bits) - 1)) << bit_offset;
					output_pixel_buffer |= ((b_channel & bits_mask) >> bit_offset) << bit_index;
				}
			}

			memcopy(
				(uint8_t*)&output_pixel_buffer,
				output_pixel_data,
				output_pixel_info.byte_count
			);
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