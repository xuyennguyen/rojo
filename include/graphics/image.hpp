#ifndef ROJO_GRAPHICS_IMAGE_HPP
#define ROJO_GRAPHICS_IMAGE_HPP

#include <rojo/graphics/image_info.hpp>

#include <rojo/graphics/detail/default_image_loader.hpp>

namespace rojo
{
    /// \tparam ImageLoader An image loader concept
    /// The ImageLoader concept requires these methods:
    /// - bool load(image_info&, const std::string& path)
    /// - bool save(const image_info&, const std::string& path)
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
            grid(std::size_t x, image_info& info)
                : m_x{x}, m_image_info{info}
            {
            }

            pixel& operator[](const std::size_t y) { return m_image_info.pixels[m_image_info.width * m_x + y]; }
            const pixel& operator[](const std::size y) const { return m_image_info.pixels[m_image_info.width * m_x + y]; }

        private:

            image_info& m_image_info;
            std::size_t m_x;
        };

        image() {}
        image(const image_info& info) : m_info{info} {}
        /// \note If load fails, you can check if it has failed via the following code:
        ///       \code
        ///       rojo::image img{"my_image.png"};
        ///       if(!img)
        ///       {
        ///           std::cerr << "failed to load img\n";
        ///       }
        ///       /endcode
        image(const std::string& path) { load(path); }

        image(const image&) = delete;            // unique_ptr doesn't support copy ctor
        image& operator=(const image&) = delete; // unique_ptr doesn't support copy ctor
        image(image&&) = default;
        image& operator=(image&&) = default;

        bool load(const std::string& path) { return m_loader.load(m_info, path); }
        bool save(const std::string& path) { return m_loader.save(m_info, path); }

        pixel& pixel(const std::size_t index) { return m_info.pixel[index]; }
        const pixel& pixel(const std::size_t index) const { return m_info.pixels[index]; }

        pixel& pixel(const std::size_t x, const std::size_t y) { return pixel(x * m_info.width + y); }
        const pixel& pixel(const std::size_t x, const std::size_t y) const { return pixel(x * m_info.width + y); }

        const pixel_array& pixels() const { return m_info.pixels.get(); }

        pixel_array release() { m_info.width = m_info.height = m_info.bpp = 0; return std::move(m_info.pixels); }

        grid grid(const std::size_t x) { return grid{x, m_info}; }
        const grid grid(const std::size_t x) const { return grid{x, m_info}; } 

        grid operator[](const std::size_t x) { return grid(x); }
        const grid operator[](const std::size_t x) const { return grid(x); }

        const image_info& info() const { return m_info; }
        inline operator const image_info&() const { return info(); }

        inline operator bool() const
        { return m_info.pixels.get(); }

    private:

        /// The information associated with the image
        image_info m_info;
        
        /// The loader, used to load/save the image
        loader m_loader;
    };
}

#endif // ROJO_GRAPHICS_IMAGE_HPP
