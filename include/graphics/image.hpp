#ifndef ROJO_GRAPHICS_IMAGE_HPP
#define ROJO_GRAPHICS_IMAGE_HPP

#include <rojo/graphics/image_info.hpp>

#include <rojo/graphics/detail/default_image_loader.hpp>

namespace rojo
{
    /// \tparam ImageLoader An image loader concept
    /// The ImageLoader concept requires these methods:
    /// - load(image_info&, const std::string& path)
    /// - save(const image_info&, const std::string& path)
    template <class ImageLoader = detail::default_image_loader>
    class image
    {
    public:

        // TODO: make this more generic?
        // i.e. let the user define the pixel type?
        typedef ImageLoader loader;
        typedef image_info::pixel pixel;
        typedef image_info::pixel_array pixel_array;

        struct grid
        {
            grid(std::size_t x, image_info& info);

            pixel& operator[](const std::size_t y);
            const pixel& operator[](const std::size y) const;

        private:

            image_info& m_image_info;
            std::size_t m_x;
        };

        image();
        image(const image_info& info);
        image(const std::string& path);

        image(const image&) = default;
        image(image&&) = default;
        image& operator=(const image&) = default;
        image& operator=(image&&) = default;

        void load(const std::string& path);
        void save(const std::string& path);

        grid grid(const std::size_t x);
        const grid grid(const std::size_t x) const;

        pixel& pixel(const std::size_t index);
        const pixel& pixel(const std::size_t index) const;

        pixel& pixel(const std::size_t x, const std::size_t y);
        const pixel& pixel(const std::size_t x, const std::size_t y) const;

        const pixel_array& pixels() const;

        pixel_array release();

        grid operator[](const std::size_t x);
        const grid operator[](const std::size_t x) const;

        const image_info& info() const;
        inline operator const image_info& const;

    private:

        /// The information associated with the image
        image_info m_info;
        
        /// The loader, used to load/save the image
        loader m_loader;
    };
}

#endif // ROJO_GRAPHICS_IMAGE_HPP
