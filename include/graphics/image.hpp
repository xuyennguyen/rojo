#ifndef ROJO_GRAPHICS_IMAGE_HPP
#define ROJO_GRAPHICS_IMAGE_HPP

#include <rojo/graphics/image_data.hpp>

#include <rojo/graphics/detail/default_image_loader.hpp>

namespace rojo
{
    /// \tparam ImageLoader An image loader concept
    /// The ImageLoader concept requires these methods:
    /// - bool load(image_data&, const std::string& path)
    /// - bool save(const image_data&, const std::string& path) const
    template <class ImageLoader = detail::default_image_loader>
    class image
    {
    public:

        // TODO: make this more generic?
        // i.e. let the user define the pixel type?
        typedef ImageLoader loader;
        typedef image_data::pixel pixel;
        typedef image_data::pixel_array pixel_array;

        struct grid
        {
            grid(std::size_t x, image_data& info)
                : m_x{x}, m_image_data{info}
            {
            }

            pixel& operator[](const std::size_t y) { return m_image_data.pixels[m_image_data.width * m_x + y]; }
            const pixel& operator[](const std::size y) const { return m_image_data.pixels[m_image_data.width * m_x + y]; }

        private:

            image_data& m_image_data;
            std::size_t m_x;
        };

        image() {}
        image(const image_data& info) : m_data{info} {}
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

        bool load(const std::string& path) { return m_loader.load(m_data, path); }
        bool save(const std::string& path) const { return m_loader.save(m_data, path); }

        pixel& pixel(const std::size_t index) { return m_data.pixel[index]; }
        const pixel& pixel(const std::size_t index) const { return m_data.pixels[index]; }

        pixel& pixel(const std::size_t x, const std::size_t y) { return pixel(x * m_data.width + y); }
        const pixel& pixel(const std::size_t x, const std::size_t y) const { return pixel(x * m_data.width + y); }

        const pixel_array& pixels() const { return m_data.pixels.get(); }

        pixel_array release() { m_data.width = m_data.height = m_data.bpp = 0; return std::move(m_data.pixels); }

        grid grid(const std::size_t x) { return grid{x, m_data}; }
        const grid grid(const std::size_t x) const { return grid{x, m_data}; } 

        grid operator[](const std::size_t x) { return grid(x); }
        const grid operator[](const std::size_t x) const { return grid(x); }

        const image_data& data() const { return m_data; }
        inline operator const image_data&() const { return data(); }

        inline operator bool() const
        { return m_data.pixels.get(); }

    private:

        /// The information associated with the image
        image_data m_data;
        
        /// The loader, used to load/save the image
        loader m_loader;
    };
}

#endif // ROJO_GRAPHICS_IMAGE_HPP
