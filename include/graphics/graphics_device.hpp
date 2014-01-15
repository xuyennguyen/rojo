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
        bool is_enabled(feature f) const;

        /// sets the scissor rect
        /// \param r The scissor rect
        /// \note If scissor testing is diabled, the scissor rect
        /// will still be set.
        void scissor(const rect& r);

        /// \return the scissor rect
        const rect& scissor() const;

        /// sets the blend function to be used for blending
        /// \param fn The function you wish to use
        /// \note This sets the factors used by the blend equation
        /// \see blend_equation To set/get the blend equation
        void blend_function(const blend::function& fn);

        /// \return the blend function this graphics device is using for blending
        const blend::function& blend_function() const;

        /// sets the blend equation to be used for blending
        /// \param equation The blend equation you wish to set it to
        /// \note By defualt, the blend equation is blend::equation::add, as this
        ///       is the most commonly used value.
        /// \see blend_function To get/set the blend function
        void blend_equation(const blend::equation& equation);

        /// \return the blend equation this graphics device is using for blending
        const blend::equation& blend_equation() const; 

        /// sets the blend object used by this graphics device
        /// \param blend What you wish to set it to
        void blend(const blend& blend);
      
        /// \return the blend object used by this graphics device
        const blend& blend() const;

    private:

        /// Describes the enabled features
        std::array<bool, feature::count> m_features; 

        /// Used to describe how blending is done
        blend m_blend;

        /// The rect that describes the scissor rect
        rect m_scissor_rect;

        /// The backend used by the device
        graphics_backend m_backend;
    };
}

#endif // ROJO_GRAPHICS_GRAPHICS_DEVICE_HPP
