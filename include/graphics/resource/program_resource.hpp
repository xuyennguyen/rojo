#ifndef ROJO_GRAPHICS_PROGRAM_RESOURCE_HPP
#define ROJO_GRAPHICS_PROGRAM_RESOURCE_HPP

#include <rojo/graphics/resource/shader.hpp>

#include <rojo/graphics/resource/detail/uniform.hpp>
//#include <rojo/graphics/resource/detail/attribute.hpp>

namespace rojo
{
    template <class GraphicsBackend>
    class program_resource
    {
    public:

        typedef GraphicsBackend graphics_backend;
        typedef typename graphics_backend::program_handle_type handle;
        
        typedef shader_resource<graphics_backend> shader;

        template <class T> using uniform = uniform<graphics_backend, T>;

        program_resource(graphics_backend& backend)
            : m_backend{backend}
        {
        }

        ~program_resource()
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

        void attach(const shader& sh)
        { backend().attach_shader(m_handle, sh.type(), sh.handle()); } 
        bool link()
        { 
            return backend().link(m_handle); 
        }

        /// \note Must be called before link
        void bind_attribute(std::size_t location, const std::string& name)
        {
            backend().bind_attribute(m_handle, location, name);
        }
        
        void bind()
        { assert(valid() && "Program is not valid"); backend().bind(m_handle); }

        bool bound() const
        { return backend().bound(m_backend); }

        graphics_backend& backend() const
        { return m_backend; }

        const handle& handle() const
        { return m_handle; }

        bool valid() const
        { return backend().valid(m_handle); }

        inline bool operator bool() const
        { return valid(); }

        template <typename T>
        uniform<T> uniform(const std::string& name) const
        { return uniform<T>{m_handle, backend().uniform_location(name)}; }

    private:

        handle m_handle;

        graphics_backend& m_backend;
    };
}

#endif // ROJO_GRAPHICS_PROGRAM_RESOURCE_HPP
