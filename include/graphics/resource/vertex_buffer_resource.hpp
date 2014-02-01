#ifndef ROJO_GRAPHICS_VERTEX_BUFFER_RESOURCE_HPP
#define ROJO_GRAPHICS_VERTEX_BUFFER_RESOURCE_HPP

namespace rojo
{
    template <class GraphicsBackend>
    class vertex_buffer_resource
    {
    public:

        typedef GraphicsBackend graphics_backend;
        typedef typename graphics_backend::vertex_buffer_handle_type handle;

        vertex_buffer_resource(graphics_backend& backend)
        {
        }
    
    private:

        graphics_backend& m_backend;
    };
}

#endif // ROJO_GRAPHICS_VERTEX_BUFFER_RESOURCE_HPP
