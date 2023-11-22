#include "raw_image.h"
#include "memory/alloc.h"

#include "exception/image/InvaliParamsException.h"

namespace sc
{
	RawImage::RawImage(
		uint8_t* data,
		uint16_t width, uint16_t height,
		Image::BasePixelType type,
		Image::PixelDepth depth,
		Image::ColorSpace space
	) : m_data(data), m_type(type), m_space(space), m_depth(depth)
	{
		if (!check_depth_base_type(type, depth))
		{
			throw InvalidParamsException();
		}
		m_width = width;
		m_height = height;
	};

	RawImage::RawImage(
		uint16_t width, uint16_t height,
		Image::BasePixelType type, Image::PixelDepth depth
	) : m_type(type), m_depth(depth)
	{
		if (!check_depth_base_type(type, depth))
		{
			throw InvalidParamsException();
		}

		m_width = width;
		m_height = height;

		uint8_t pixel_size = PixelDepthTable[(uint16_t)depth].byte_count;

		m_allocated_data = memalloc((width * height) * pixel_size);
		m_data = m_allocated_data;
	};

	RawImage::~RawImage()
	{
		if (m_allocated_data)
		{
			free(m_allocated_data);
		}
	};

	size_t RawImage::data_length() const
	{
		return Image::calculate_image_length(m_width, m_height, m_depth);
	};

	uint8_t* RawImage::data() const
	{
		return m_data;
	};

	Image::BasePixelType RawImage::base_type() const
	{
		return m_type;
	};

	Image::ColorSpace RawImage::colorspace() const
	{
		return m_space;
	}

	Image::PixelDepth RawImage::depth() const
	{
		return m_depth;
	}

	/// <summary>
	/// Copies data from current image to provided one and converts size, data type, etc.
	/// </summary>
	/// <param name="image"></param>
	void RawImage::copy(RawImage& image) const
	{
		size_t data_size = Image::calculate_image_length(m_width, m_height, m_depth);
		uint8_t* data = nullptr;
		Image::PixelDepth depth = m_depth;

		if (image.width() != m_width || image.height() != m_height)
		{
			uint8_t* resize_data = nullptr;

			switch (m_depth)
			{
				// RGBA
			case sc::Image::PixelDepth::RGBA4:
			case sc::Image::PixelDepth::RGB5_A1:
				depth = Image::PixelDepth::RGBA8;
				break;

				// RGB
			case sc::Image::PixelDepth::RGB565:
				depth = Image::PixelDepth::RGB8;
				break;

			case sc::Image::PixelDepth::RGB8:
			case sc::Image::PixelDepth::LUMINANCE8_ALPHA8:
			case sc::Image::PixelDepth::LUMINANCE8:
			case sc::Image::PixelDepth::RGBA8:
			default:
				break;
			}

			if (depth != m_depth)
			{
				resize_data = memalloc(Image::calculate_image_length(m_width, m_height, depth));
				Image::remap(m_data, resize_data, m_width, m_height, m_depth, depth);
			}

			data = memalloc(Image::calculate_image_length(image.width(), image.height(), depth));
			Image::resize(
				resize_data ? resize_data : m_data, data,
				m_width, m_height,
				image.width(), image.height(),
				m_type, m_space
			);

			if (resize_data)
			{
				free(resize_data);
			}
		}

		if (image.depth() != m_depth)
		{
			Image::remap(data ? data : m_data, image.data(), image.width(), image.height(), depth, image.depth());
		}
	};

	void RawImage::write(Stream& buffer)
	{
		buffer.write(m_data, data_length());
	};
}