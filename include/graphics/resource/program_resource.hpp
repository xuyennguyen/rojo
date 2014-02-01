#ifndef ROJO_GRAPHICS_PROGRAM_RESOURCE_HPP
#define ROJO_GRAPHICS_PROGRAM_RESOURCE_HPP

#include <rojo/graphics/resource/shader.hpp>

namespace rojo
{
    typedef unsigned Uniform;
    typedef unsigned Attribute;

    template <class GraphicsBackend>
    class program_resource
    {
    public:

        typedef GraphicsBackend graphics_backend;
        typedef typename graphics_backend::program_handle_type handle;
        

        program_resource(graphics_backend& backend)
            : m_backend(backend)
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

        template <shader_type ShaderType>
        void attach_shader(const shader_resource<graphics_backend, ShaderType>& shader)
        { backend().attach_shader(m_handle, shader.type(), shader.handle()); }

        bool link()
        { return backend().link(m_handle); }

        graphics_backend& backend() const
        { return m_backend; }

        const handle& handle() const
        { return m_handle; }

        bool valid() const
        { return backend().valid(m_handle); }

        inline bool operator bool() const
        { return valid(); }


        // todo:
        // uniform and attributes

    private:

        handle m_handle;

        graphics_backend& m_backend;
    };
}

#endif // ROJO_GRAPHICS_PROGRAM_RESOURCE_HPP
