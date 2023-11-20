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

	size_t RawImage::data_length()
	{
		return Image::calculate_image_length(m_width, m_height, m_depth);
	};

	uint8_t* RawImage::data()
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

	Image* RawImage::resize(uint16_t new_width, uint16_t new_height)
	{
		Image* image = new RawImage(new_width, new_height, m_type, m_depth);

		Image::resize(
			m_data, image->data(),
			m_width, m_height,
			new_width, new_height,
			m_type, m_depth, m_space
		);

		return image;
	};

	void RawImage::write(Stream& buffer)
	{
		buffer.write(m_data, data_length());
	};
}