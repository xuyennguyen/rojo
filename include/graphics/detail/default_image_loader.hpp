#ifndef ROJO_GRAPHICS_DETAIL_DEFAULT_IMAGE_LOADER_HPP
#define ROJO_GRAPHICS_DETAIL_DEFAULT_IMAGE_LOADER_HPP

#include <string>

#include <rojo/graphics/image_data.hpp>

namespace rojo
{
    namespace detail
    {
        class default_image_loader
        {
        public:

            bool load(image_data& data, const std::string& path);
            bool save(const image_data& data, const std::string& path) const;
        };
    }
}

#endif // ROJO_GRAPHICS_DETAIL_DEFAULT_IMAGE_LOADER_HPP
