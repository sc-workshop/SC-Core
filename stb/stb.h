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

#include "stb_image.h"
#pragma endregion STB Image Defines

#pragma region
#define STBIW_MALLOC(sz)        sc::memalloc(sz)
#define STBIW_REALLOC(p,newsz)  realloc(p,newsz)
#define STBIW_FREE(p)           free(p)

#define STBI_WRITE_NO_STDIO

#include "stb_image_write.h"
#pragma endregion STB Image Write Defines

namespace sc
{
	namespace stb
	{
#pragma region
		int stbi_sc_io_read(void* user, char* data, int size);
		void stbi_sc_io_skip(void* user, int n);
		int stbi_sc_io_eof(void* user);

		const stbi_io_callbacks stbi_sc_io_callback = { &stbi_sc_io_read, &stbi_sc_io_skip, &stbi_sc_io_eof };

		/// <summary>
		/// Loads png, jpeg, psd, tga and bmp images
		/// </summary>
		/// <param name="stream"></param>
		/// <returns>Loaded image</returns>
		RawImage load_image(Stream& stream);
#pragma endregion Image Read

		enum class ImageFormat : uint8_t
		{
			PNG = 0,
			BMP,
			TGA,
			JPEG
		};

#pragma region
		int stbi_sc_io_write(void* user, void* data, int size);

		void write_image(RawImage& image, ImageFormat format, Stream& output);

		/// <summary>
		/// Saves images depending on path extension
		/// </summary>
		/// <param name="image"></param>
		/// <param name="extension"> Must be in lowercase </param>
		/// <param name="output"></param>
		void write_image(RawImage& image, std::string extension, Stream& output);
#pragma endregion Image Write
	}
}