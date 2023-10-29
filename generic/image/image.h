#pragma once

#include <stdint.h>
#include "io/stream.h"

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
        static size_t calculate_image_length(uint16_t width, uint16_t height, BasePixelType type);

        static void resize(
            uint8_t* input_data, uint8_t* output_data,
            uint16_t width, uint16_t height,
            uint16_t new_width, uint16_t new_height,
            BasePixelType type, ColorSpace space, bool premultiply = true
        );

    public:
        virtual void write(Stream& buffer) = 0;

    public:
        virtual uint16_t width() const;
        virtual uint16_t height() const;

        virtual BasePixelType base_type() const = 0;
        virtual ColorSpace colorspace() const = 0;

        virtual size_t data_length() = 0;
        virtual uint8_t* data() = 0;

        virtual bool is_compressed() const = 0;

    protected:
        uint16_t m_width = 0;
        uint16_t m_height = 0;
    };
}