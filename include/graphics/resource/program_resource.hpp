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
        // todo: possibly rename this handle?
        typedef typename graphics_backend::uniform_location_type location;

        uniform(program& program, location& location)
            : m_program{program}, m_location{location}
        {
        }

        graphics_backend& backend() const
        { return program.backend(); }

        const location& location() const
        { return m_location; }

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

        location m_location;

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

        /// \note Must be called before link
        void bind_attribute(unsigned location, const std::string& name)
        {
            backend().bind_attribute(m_handle, location, name);
        }
        
        void use()
        {
            backend().use(m_handle);
        }

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
            return uniform<T>{m_handle, backend().uniform_location(name)};
        }

    private:

        handle m_handle;

        graphics_backend& m_backend;
    };
}

#endif // ROJO_GRAPHICS_PROGRAM_RESOURCE_HPP
