#ifndef ROJO_GRAPHICS_TEXTURERESOURCE_HPP
#define ROJO_GRAPHICS_TEXTURERESOURCE_HPP

#include <rojo/graphics/image_info.hpp>

namespace rojo
{
    enum class texture_wrap
    {
        repeat,
        inv_repeat,
        clamp_to_edge,
        clamp_to_border
    };

    enum class texture_filter
    {
        linear,
        nearest
        
        /*
            // http://www.opengl.org/sdk/docs/man/xhtml/glTexParameter.xml 

         nearest_mipmap_nearest,
         linear_mipmap_nearest,
         linear_mipmap_linear
         */
    };


    // TODO: mipmap support
    template <class GraphicsBackend>
    class texture_resource
    {
    public:

        typedef GraphicsBackend graphics_backend;
        typedef typename graphics_backend::texture_handle_type handle;

        texture_resource(graphics_backend& backend)
            : m_backend{backend}, m_src_width{0}, m_src_height{0}
        {
        }

        texture_resource(graphics_backend& backend, const image_data& data)
            : m_backend{backend}, m_src_width{0}, m_src_height{0}
        {
            upload(data);
        }

        texture_resource(graphics_backend& backend, const image_data& data, const texture_wrap& wrap)
            : texture_resource{backend, data, wrap, texture_filter::linear}
        {
        }

        texture_resource(graphics_backend& backend, const image_data& data, const texture_filter& filter)
            : texture_resource{backend, data, texture_wrap::repeat, filter}
        {
        }

        texture_resource(graphics_backend& backend, const image_data& data, const texture_wrap& wrap, const texture_filter& filter)
            : texture_resource{backend}
        {
            upload(data, wrap, filter);
        }

        ~texture_resource()
        {
            destroy();
        }

        void destroy()
        {
            if(valid())
            {
                backend().destroy(m_handle);
            } 
        }

        bool upload(const image_data& data)
        {
            return upload(data, wrap(), filter());
        }

        bool upload(const image_data& data, const texture_wrap& w)
        {
            return upload(data, w, filter());
        }

        bool upload(const image_data& data, const texture_filter& f)
        {
            return upload(data, wrap(), f);
        }

        bool upload(const image_data& data, const texture_wrap& w, const texture_filter& f)
        {
            if(backend().upload(m_handle, data))
            {
                m_src_width = data.width;
                m_src_height = data.height;
                backend().wrap(m_handle, w);
                backend().filter(m_handle, f);

                return true;
            }

            return false;
        }

        image_data data() const
        {
            return backend().data(m_handle);
        }

        void wrap(const texture_wrap& w)
        {
            m_wrap = w;

            if(valid())
            {
                backend().wrap(m_backend, w);
            }
        }

        const texture_wrap& wrap() const
        { return m_wrap; }

        void filter(const texture_filter& f)
        {
            m_filter = f;
            if(valid())
            {
                backend().filter(m_handle, f);
            }
        }

        const texture_filter& filter() const
        { return m_filter; }

        unsigned width() const
        { return m_src_width; }

        unsigned height() const
        { return m_src_height; }

        const handle& handle() const
        { return m_handle; }

        graphics_backend& backend() const
        { return m_backend; }

        bool valid() const
        { return backend().valid(m_handle); }

        inline bool operator bool() const
        { return valid(); }

    private:

        /// The source width and height
        unsigned m_src_width, m_src_height;

        texture_wrap m_wrap;

        texture_filter m_filter;

        handle m_handle;

        graphics_backend& m_backend;
    };
}

#endif // ROJO_GRAPHICS_TEXTURERESOURCE_HPP
