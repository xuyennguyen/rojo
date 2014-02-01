#ifndef ROJO_GRAPHICS_PROGRAM_RESOURCE_HPP
#define ROJO_GRAPHICS_PROGRAM_RESOURCE_HPP

#include <rojo/graphics/resource/shader.hpp>

namespace rojo
{
    template <class GraphicsBackend>
    class program_resource;

    template <class Program, class T>
    class uniform 
    { 
    public:


        typedef Program program;
        typedef typename program::graphics_backend graphics_backend;
        typedef typename graphics_backend::uniform_handle_type handle;

        uniform(program& program, handle& handle)
            : m_program{program}, m_handle{handle}
        {
        }

        graphics_backend& backend() const
        { return program.backend(); }

        const handle& handle() const
        { return m_handle; }

        bool valid() const
        { return backend().valid(m_backend); }

        inline operator bool() const
        { return valid(); }

        const T& value() const
        { return m_value; }

        void value(const T& val)
        {
            m_value = val;
            backend().uniform(program().handle(), m_handle, reinterperet_cast<void*>(&val), sizeof(val));
        }

        uniform& operator=(const T& val)
        { 
            value(val);
            return *this;
        }

        program& program() const
        { return m_program; }

    private:

        program& m_program;

        handle m_handle;

        T m_value;
    };

    // todo
    typedef unsigned attribute;

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
        { return backend().link(m_handle); }

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
        { 
            return uniform<T>{m_handle, backend().uniform_handle(name)};
        }

        // todo:
        // uniform and attributes

    private:

        handle m_handle;

        graphics_backend& m_backend;
    };
}

#endif // ROJO_GRAPHICS_PROGRAM_RESOURCE_HPP
