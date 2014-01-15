#ifndef ROJO_GRAPHICS_GRAPHICS_DEVICE_HPP
#define ROJO_GRAPHICS_GRAPHICS_DEVICE_HPP

#include <rojo/graphics/graphics_types.hpp>

#include <rojo/graphics/resource/texture_resource.hpp>
#include <rojo/graphics/resource/shader_resource.hpp>
#include <rojo/graphics/resource/program_resource.hpp>
#include <rojo/graphics/resource/vertex_buffer_resource.hpp>
#include <rojo/graphics/resource/index_buffer_resource.hpp>

namespace rojo
{
    template <class GraphicBackend>
    class graphics_device
    {
        typedef graphics_device<GraphicBackend> this_type;
        
    public:
        
        typedef GraphicsBackend graphics_backend;

        // resources
        typedef texture_resource<GraphicBackend> texture;
        typedef shader_resource<GraphicsBackend> shader;
        typedef program_resource<GraphicsBackend> program;
        typedef vertex_buffer_resource<GraphicsBackend> vertex_buffer;
        typedef index_buffer_resource<GraphicsBackend> index_buffer;

        template <class... Args>
        texture create_texture(Args&&... args);
        
        template <class... Args>
        shader create_shader(Args&&... args);

        template <class... Args>
        program create_program(Args&&... args);

        template <class... Args>
        vertex_buffer create_vertex_buffer(Args&&... args);

        template <class... Args>
        index_buffer create_index_buffer(Args&&... args); 

        template <class Resource, class... Args>
        Resource create(Args&&... args);
       

        /// enables a feature
        /// \param f the feature you wish to enable (or disable)
        /// \param enable true to enable the feature; false to disable it 
        void enable(feature f, bool enable = true);

        /// determines whether the feature is enabled
        /// \param f the feture you wish to check
        /// \return true if the feature is enabled, false otherwise
        bool is_enabled(feature f);

        /// sets the scissor rect
        /// \param r The scissor rect
        /// \note If scissor testing is diabled, the scissor rect
        /// will still be set.
        void scissor(const rect& r);

        /// \return the scissor rect
        const rect& scissor() const;

        /// sets the blend equation to be used for blending
        /// \param equation The blend equation you wish to set it to
        /// \note If blending is disabled 
        void blend_equation(const blend_equation& equation);

        /// \return the blend equation this graphics device is using for blending
        const blend_equation& blend_equation() const; 

    private:
        
        blend_equation m_blend_equation;

        rect m_scissor_rect;

        graphics_backend m_backend;
    };
}

#endif // ROJO_GRAPHICS_GRAPHICS_DEVICE_HPP
