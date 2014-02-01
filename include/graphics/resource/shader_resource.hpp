#ifndef ROJO_GRAPHICS_SHADER_RESOURCE_HPP
#define ROJO_GRAPHICS_SHADER_RESOURCE_HPP

#include <string>
#include <istream>
#include <iterator>

namespace rojo
{
    enum class shader_type
    {
        vertex,
        fragment
    };

    template <class GraphicsBackend, shader_type ShaderType>
    class shader_resource
    {
    public:

        typedef GraphicsBackend graphics_backend;
        typedef typename graphics_backend::shader_handle_type handle;

        shader_resource(graphics_backend& backend)
            : m_backend(backend)
        {
        }

        shader_resource(graphics_backend& backend, const std::string& source)
            : m_backend(backend), m_source(source)
        {
        }

        shader_resource(graphics_backend& backend, const std::istream& stream)
            : m_backend(backend), m_source(std::istreambuf_iterator<char>(stream), std::istreambuf_iterator<char>())
        {
        }

        ~shader_resource()
        {
            destroy();
        }

        void destroy()
        {
            if(vailid)
            {
                backend().destroy(m_handle);
            }
        }

        std::string& source()
        { return m_source; }

        const std::string& source() const
        { return m_source; }

        void append_stream(const std::istream& stream)
        { m_source.append(std::istreambuf_iterator<char>(stream), std::istreambuf_iterator<char>()); }

        bool compile()
        { return m_backend.compile(m_handle, type(), source()); }

        graphics_backend& backend() const
        { return m_backend; }

        constexpr shader_type type() const
        { return ShaderType; }

        const handle& handle() const
        { return m_handle; }

        bool valid() const
        { return backend().valid(m_handle); }

        inline bool operator bool() const
        { return valid(); } 

    private:

        std::string m_source;

        handle m_handle;

        graphics_backend& m_backend;
    };

    template <class GraphicsBackend>
    using fragment_shader_resource = shader<GraphicsBackend, shader_type::fragment>;

    template <class GraphicsBackend>
    using vertex_shader_resource = shader<GraphicsBackend, shader_type::vertex>;
}

#endif // ROJO_GRAPHICS_SHADER_RESOURCE_HPP
