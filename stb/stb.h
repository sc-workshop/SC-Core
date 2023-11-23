#pragma once

#include "exception/image/StbLoadingException.h"
#include "exception/image/StbWritingException.h"

#include "io/stream.h"
#include "memory/alloc.h"
#include "generic/image/raw_image.h"

#pragma region
#define STBIR_MALLOC(size, c) ((void)(c), sc::memalloc(size))
#define STBIR_FREE(ptr,c)    ((void)(c), free(ptr))

#include "stb_image_resize.h"
#pragma endregion STB Image Resize Defines

#pragma region
#define STBI_MALLOC(sz)           sc::memalloc(sz)
#define STBI_REALLOC(p,newsz)     realloc(p,newsz)
#define STBI_FREE(p)              free(p)

#define STBI_NO_GIF
#define STBI_NO_HDR
#define STBI_NO_PNM
#define STBI_NO_PIC
#define STBI_NO_STDIO

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#pragma endregion STB Image Defines

#pragma region
#define STBIW_MALLOC(sz)        sc::memalloc(sz)
#define STBIW_REALLOC(p,newsz)  realloc(p,newsz)
#define STBIW_FREE(p)           free(p)

#define STBI_WRITE_NO_STDIO

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#pragma endregion STB Image Write Defines

namespace sc
{
	namespace stb
	{
#pragma region
		int stbi_sc_io_read(void* user, char* data, int size)
		{
			Stream* stream = (sc::Stream*)user;

			return static_cast<int>(stream->read(data, size));
		}

		void stbi_sc_io_skip(void* user, int n)
		{
			Stream* stream = (sc::Stream*)user;

			stream->seek(n, sc::Seek::Add);
		}

		int stbi_sc_io_eof(void* user)
		{
			Stream* stream = (sc::Stream*)user;

			stream->position() == stream->length() ? -1 : 0;
		}

		const stbi_io_callbacks stbi_sc_io_callback = { &stbi_sc_io_read, &stbi_sc_io_skip, &stbi_sc_io_eof };

		/// <summary>
		/// Loads png, jpeg, psd, tga and bmp images
		/// </summary>
		/// <param name="stream"></param>
		/// <returns>Loaded image</returns>
		RawImage load_image(Stream& stream)
		{
			int width, height, channels;

			uint8_t* data = (uint8_t*)stbi_load_from_callbacks(&stbi_sc_io_callback, (void*)&stream, &width, &height, &channels, 0);

			if (data == NULL)
			{
				throw StbLoadingException(stbi_failure_reason());
			}

			Image::BasePixelType type = Image::BasePixelType::RGBA;
			Image::PixelDepth depth = Image::PixelDepth::RGB8;

			switch (channels)
			{
			case 1:
				type = Image::BasePixelType::L;
				depth = Image::PixelDepth::LUMINANCE8;
				break;

			case 2:
				type = Image::BasePixelType::LA;
				depth = Image::PixelDepth::LUMINANCE8_ALPHA8;
				break;

			case 3:
				type = Image::BasePixelType::RGB;
				depth = Image::PixelDepth::RGB8;
				break;

			case 4:
				type = Image::BasePixelType::RGBA;
				depth = Image::PixelDepth::RGBA8;
				break;

			default:
				break;
			}

			// TODO: Make tests in debugger about that
			return RawImage(
				data,
				static_cast<uint16_t>(width), static_cast<uint16_t>(height),
				type, depth
			);
		}
#pragma endregion Image Read

		enum class ImageFormat : uint8_t
		{
			PNG = 0,
			BMP,
			TGA,
			JPEG
		};

#pragma region
		int stbi_sc_io_write(void* user, void* data, int size)
		{
			Stream* stream = (Stream*)user;
			return static_cast<int>(stream->write(data, size));
		}

		/// <summary>
		/// Saves images depending on path extension
		/// </summary>
		/// <param name="image"></param>
		/// <param name="extension"> Must be in lowercase </param>
		/// <param name="output"></param>
		void write_image(RawImage& image, std::string extension, Stream& output)
		{
			ImageFormat format = ImageFormat::PNG;

			if (extension.empty())
			{
				extension = ".png";
			}

			if (extension.at(0) == '.')
			{
				extension = std::string(extension.begin() + 1, extension.end());
			}

			if (extension == "png")
			{
				format = ImageFormat::PNG;
			}

			if (extension == "jpg" || extension == "jpeg")
			{
				format = ImageFormat::JPEG;
			}

			if (extension == "tga")
			{
				format = ImageFormat::TGA;
			}

			if (extension == "bmp")
			{
				format = ImageFormat::BMP;
			}
		}

		void write_image(RawImage& image, ImageFormat format, Stream& output)
		{
			uint8_t* buffer = nullptr;

			uint8_t channels = 0;

			Image::BasePixelType source_type = image.base_type();
			switch (source_type)
			{
			case Image::BasePixelType::RGBA:
				channels = 4;
				break;
			case Image::BasePixelType::RGB:
				channels = 3;
				break;
			case Image::BasePixelType::LA:
				channels = 2;
				break;
			case Image::BasePixelType::L:
				channels = 1;
				break;
			default:
				break;
			}

			Image::PixelDepth destination_depth = Image::PixelDepth::RGBA8;
			if (source_type == Image::BasePixelType::RGBA)
			{
				destination_depth = Image::PixelDepth::RGBA8;
			}
			else if (source_type == Image::BasePixelType::RGB)
			{
				destination_depth = Image::PixelDepth::RGB8;
			}
			else if (source_type == Image::BasePixelType::LA)
			{
				destination_depth = Image::PixelDepth::LUMINANCE8_ALPHA8;
			}
			else if (source_type == Image::BasePixelType::L)
			{
				destination_depth = Image::PixelDepth::LUMINANCE8;
			}

			if (image.depth() != destination_depth)
			{
				buffer = sc::memalloc(Image::calculate_image_length(image.width(), image.height(), destination_depth));

				Image::remap(image.data(), buffer,
					image.width(), image.height(),
					image.depth(), destination_depth
				);
			}

			int result = 0;
			switch (format)
			{
			case ImageFormat::PNG:
				result = stbi_write_png_to_func((stbi_write_func*)&stbi_sc_io_write, (void*)&output, image.width(), image.height(), channels, image.data(), 0);
				break;
			case sc::stb::ImageFormat::BMP:
				result = stbi_write_bmp_to_func((stbi_write_func*)&stbi_sc_io_write, (void*)&output, image.width(), image.height(), channels, image.data());
				break;
			case sc::stb::ImageFormat::TGA:
				result = stbi_write_tga_to_func((stbi_write_func*)&stbi_sc_io_write, (void*)&output, image.width(), image.height(), channels, image.data());
				break;
			case sc::stb::ImageFormat::JPEG:
				result = stbi_write_jpg_to_func((stbi_write_func*)&stbi_sc_io_write, (void*)&output, image.width(), image.height(), channels, image.data());
				break;
			default:
				break;
			}

			if (buffer)
			{
				free(buffer);
			}

			if (result == 0)
			{
				throw StbWritingException();
			}
		}

#pragma endregion Image Write
	}
}