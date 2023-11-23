#pragma once

#include "exception/image/StbLoadingException.h"

#include "io/stream.h"
#include "memory/alloc.h"
#include "generic/image/raw_image.h"

#define STBIR_MALLOC(size, c) ((void)(c), sc::memalloc(size))
#define STBIR_FREE(ptr,c)    ((void)(c), free(ptr))

#define STBI_MALLOC(sz)           sc::memalloc(sz)
#define STBI_REALLOC(p,newsz)     realloc(p,newsz)
#define STBI_FREE(p)              free(p)

#define STBIW_MALLOC(sz)        sc::memalloc(sz)
#define STBIW_REALLOC(p,newsz)  realloc(p,newsz)
#define STBIW_FREE(p)           free(p)

#define STBI_NO_GIF
#define STBI_NO_HDR
#define STBI_NO_PNM
#define STBI_NO_PIC
#define STBI_NO_STDIO
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace sc
{
	namespace stb
	{
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

			return RawImage(
				data,
				static_cast<uint16_t>(width), static_cast<uint16_t>(height),
				type, depth
			);
		}
	}
}

#include "stb_image_write.h"
#include "stb_image_resize.h"