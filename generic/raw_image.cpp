#include "generic/image/raw_image.h"
#include "memory/alloc.h"

namespace sc
{
	RawImage::RawImage(uint8_t* data, uint16_t width, uint16_t height, Image::BasePixelType type, Image::ColorSpace space) : m_data(data), m_type(type), m_space(space)
	{
		m_width = width;
		m_height = height;
	};

	RawImage::RawImage(uint16_t width, uint16_t height, Image::BasePixelType type) : m_type(type)
	{
		m_width = width;
		m_height = height;

		m_allocated_data = memalloc((width * height) * (uint8_t)type);
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
		return Image::calculate_image_length(m_width, m_height, m_type);
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

	Image* RawImage::resize(uint16_t new_width, uint16_t new_height)
	{
		Image* image = new RawImage(new_width, new_height, m_type);

		Image::resize(
			m_data, image->data(),
			m_width, m_height,
			new_width, new_height,
			m_type, m_space
		);

		return image;
	};

	void RawImage::write(Stream& buffer)
	{
		buffer.write(m_data, data_length());
	};
}