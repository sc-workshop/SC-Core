#pragma once

#include <stdint.h>
#include "io/stream.h"
#include "io/memory_stream.h"

#include "stb/stb.h"

#include "exception/image/CorruptedImageBufferException.h"
#include "exception/MemoryAllocationException.h"

namespace sc
{
    class Image
    {
    public:
        enum class BasePixelType : uint8_t
        {
            RGBA = 4,
            RGB = 3,
            LA = 2,
            L = 1,
        };

        enum class ColorSpace : uint8_t
        {
            Linear = 0,
            sRGB,
        };

    public:
        virtual void write(Stream& buffer) = 0;

    public:
        virtual uint16_t width() const
        {
            return m_width;
        };
        virtual uint16_t height() const
        {
            return m_height;
        };

        virtual BasePixelType base_type() const = 0;
        virtual ColorSpace colorspace() const  = 0;

        virtual size_t data_length()  = 0;
        virtual uint8_t* data()  = 0;

        virtual bool is_compressed() const  = 0;

    public:
        virtual Image* clone();
        virtual void resize(uint16_t new_width, uint16_t new_height) = 0;

    protected:
        uint16_t m_width = 0;
        uint16_t m_height = 0;
    };

    class CompressedImage : public Image
    {
    public:
        virtual size_t decompressed_data_length();
        virtual void decompress_data(Stream& buffer);
    };

    class RawImage : public Image
    {
    public:
        RawImage(const RawImage&) = delete;

        RawImage(uint8_t* data, uint16_t width, uint16_t height, Image::BasePixelType type, Image::ColorSpace space = Image::ColorSpace::Linear) :  m_data(data), m_type(type), m_space(space)
        {
            m_width = width;
            m_height = height;
        }

        RawImage(uint16_t width, uint16_t height, Image::BasePixelType type) : m_type(type)
        {
            m_width = width;
            m_height = height;

            m_allocated_data = memalloc((width * height) * (uint8_t)type);
            m_data = m_allocated_data;
        }

        ~RawImage()
        {
            if (m_allocated_data)
            {
                free(m_allocated_data);
            }
        }

    public:
        virtual size_t data_length()
        {
            return (m_width * m_height) * (uint8_t)m_type;
        };
        virtual uint8_t* data()
        {
            return m_data;
        };

        virtual BasePixelType base_type() const
        {
            return m_type;
        };

        virtual ColorSpace colorspace() const
        {
            return m_space;
        };

        virtual bool is_compressed() const
        {
            return false;
        };

    public:
        virtual Image* clone()
        {
            Image* result = new RawImage(m_width, m_height, m_type);
            std::memcpy(result->data(), m_data, result->data_length());
        };

        void resize(uint16_t new_width, uint16_t new_height)
        {
            uint8_t* resized;
            switch (m_type)
            {
            case Image::BasePixelType::RGBA:
                resized = resize_rgba(new_width, new_height);
                break;
            case Image::BasePixelType::RGB:
                resized = resize_rgb(new_width, new_height);
                break;
             case Image::BasePixelType::LA:
                resized = resize_la(new_width, new_height);
                break;
            case Image::BasePixelType::L:
                resized = resize_l(new_width, new_height);
                break;
            }

            if (m_allocated_data)
            {
                free(m_allocated_data);
            }

            m_width = new_width;
            m_height = new_height;
            m_data = m_allocated_data;
            m_allocated_data = resized;
        };

        void write(Stream& buffer)
        {
            buffer.write(m_data, data_length());
        }

    private:
        uint8_t* resize_rgba(uint16_t new_width, uint16_t new_height)
        {
            uint8_t* buffer = memalloc((new_width * new_height) * 4);

            stbir__resize_arbitrary(NULL,
                m_data, m_width, m_height, 0,
                buffer, new_width, new_height, 0,
                0, 0, 1, 1, NULL,
                4, 3, STBIR_FLAG_ALPHA_PREMULTIPLIED, STBIR_TYPE_UINT8, STBIR_FILTER_DEFAULT, STBIR_FILTER_DEFAULT,
                STBIR_EDGE_CLAMP, STBIR_EDGE_CLAMP, m_space == Image::ColorSpace::Linear ? STBIR_COLORSPACE_LINEAR : STBIR_COLORSPACE_SRGB
            );

            return buffer;
        }

        uint8_t* resize_rgb(uint16_t new_width, uint16_t new_height)
        {
            uint8_t* buffer = memalloc((new_width * new_height) * 3);

            stbir__resize_arbitrary(NULL,
                m_data, m_width, m_height, 0,
                buffer, new_width, new_height, 0,
                0, 0, 1, 1, NULL,
                3, -1, 0, STBIR_TYPE_UINT8, STBIR_FILTER_DEFAULT, STBIR_FILTER_DEFAULT,
                STBIR_EDGE_CLAMP, STBIR_EDGE_CLAMP, m_space == Image::ColorSpace::Linear ? STBIR_COLORSPACE_LINEAR : STBIR_COLORSPACE_SRGB
            );

            return buffer;
        }

        uint8_t* resize_la(uint16_t new_width, uint16_t new_height)
        {
            uint8_t* buffer = memalloc((new_width * new_height) * 2);

            stbir__resize_arbitrary(NULL,
                m_data, m_width, m_height, 0,
                buffer, new_width, new_height, 0,
                0, 0, 1, 1, NULL,
                2, 1, STBIR_FLAG_ALPHA_PREMULTIPLIED, STBIR_TYPE_UINT8, STBIR_FILTER_DEFAULT, STBIR_FILTER_DEFAULT,
                STBIR_EDGE_CLAMP, STBIR_EDGE_CLAMP, m_space == Image::ColorSpace::Linear ? STBIR_COLORSPACE_LINEAR : STBIR_COLORSPACE_SRGB
            );

            return buffer;
        }

        uint8_t* resize_l(uint16_t new_width, uint16_t new_height)
        {
            uint8_t* buffer = memalloc((new_width * new_height) * 3);

            stbir__resize_arbitrary(NULL,
                m_data, m_width, m_height, 0,
                buffer, new_width, new_height, 0,
                0, 0, 1, 1, NULL,
                1, -1, 0, STBIR_TYPE_UINT8, STBIR_FILTER_DEFAULT, STBIR_FILTER_DEFAULT,
                STBIR_EDGE_CLAMP, STBIR_EDGE_CLAMP, m_space == Image::ColorSpace::Linear ? STBIR_COLORSPACE_LINEAR : STBIR_COLORSPACE_SRGB
            );

            return buffer;
        }


    private:
        Image::BasePixelType m_type;
        Image::ColorSpace m_space;

        uint8_t* m_data;
        uint8_t* m_allocated_data;
    };
}