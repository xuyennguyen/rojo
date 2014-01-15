#ifndef ROJO_GRAPHICS_IMAGE_INFO_HPP
#define ROJO_GRAPHICS_IMAGE_INFO_HPP

#include <memory>

#include <rojo/graphics/graphic_types.hpp>

namespace rojo
{
    struct image_info
    {
        // TODO: add different formats for colours?
        typedef colour4 pixel;
        typedef std::unique_ptr<pixel[]> pixel_array;

        pixel_array pixels;
        unsigned width, height, bpp;
    };
}

#endif // ROJO_GRAPHICS_IMAGE_INFO_HPP
