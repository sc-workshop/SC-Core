#pragma once
#include "image.h"

namespace sc
{
	class RawImage : public Image
	{
	public:
		RawImage(const RawImage&) = delete;

		RawImage(
			uint8_t* data,
			uint16_t width, uint16_t height,
			Image::BasePixelType type,
			Image::PixelDepth depth = Image::PixelDepth::RGBA8,
			Image::ColorSpace space = Image::ColorSpace::Linear
		);

		RawImage(
			uint16_t width, uint16_t height,
			Image::BasePixelType type, Image::PixelDepth depth
		);

		~RawImage();

	public:
		virtual size_t data_length() const;
		virtual uint8_t* data() const;

		virtual BasePixelType base_type() const;
		virtual ColorSpace colorspace() const;
		virtual PixelDepth depth() const;

		virtual bool is_compressed() const
		{
			return false;
		};

	public:
		void copy(RawImage& image) const;

		void write(Stream& buffer);

	private:
		Image::BasePixelType m_type;
		Image::ColorSpace m_space;
		Image::PixelDepth m_depth;

		uint8_t* m_data = nullptr;
		uint8_t* m_allocated_data = nullptr;
	};
}