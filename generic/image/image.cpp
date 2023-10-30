#include "image.h"

#include "stb/stb.h"

namespace sc
{
    size_t Image::calculate_image_length(uint16_t width, uint16_t height, BasePixelType type)
    {
        return (width * height) * (uint8_t)type;
    }

    void Image::resize(
        uint8_t* input_data, uint8_t* output_data,
        uint16_t width, uint16_t height,
        uint16_t new_width, uint16_t new_height,
        BasePixelType type, ColorSpace space, bool premultiply
    )
    {
        bool has_alpha = type == BasePixelType::LA || type == BasePixelType::RGBA;

        stbir__resize_arbitrary(NULL,
            input_data, width, height, 0,
            output_data, new_width, new_height, 0,
            0, 0, 1, 1, NULL,
            (uint8_t)type, has_alpha ? (uint8_t)type - 1 : -1, premultiply ? STBIR_FLAG_ALPHA_PREMULTIPLIED : 0, STBIR_TYPE_UINT8, STBIR_FILTER_DEFAULT, STBIR_FILTER_DEFAULT,
            STBIR_EDGE_CLAMP, STBIR_EDGE_CLAMP, space == Image::ColorSpace::Linear ? STBIR_COLORSPACE_LINEAR : STBIR_COLORSPACE_SRGB
        );
    };

    uint16_t Image::width() const
    {
        return m_width;
    };

    uint16_t Image::height() const
    {
        return m_height;
    };
}