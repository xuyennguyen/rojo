#ifndef ROJO_GRAPHICS_TEXTURERESOURCE_HPP
#define ROJO_GRAPHICS_TEXTURERESOURCE_HPP

namespace rojo
{
    template <class GraphicsBackend>
    class texture_resource
    {
    public:

        typedef GraphicsBackend graphics_backend;
        typedef typename graphics_backend::texture_handle_type handle;

        texture_resource(graphics_backend& backend);

        const handle& handle() const;

        graphics_backend& backend() const;

    private:

        handle m_handle;

        graphics_backend& m_backend;
    };
}

#endif // ROJO_GRAPHICS_TEXTURERESOURCE_HPP
