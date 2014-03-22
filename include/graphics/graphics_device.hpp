#ifndef ROJO_GRAPHICS_GRAPHICS_DEVICE_HPP
#define ROJO_GRAPHICS_GRAPHICS_DEVICE_HPP

#include <cassert>

#include <rojo/graphics/types.hpp>

#include <rojo/graphics/resource/texture_resource.hpp>
#include <rojo/graphics/resource/shader_resource.hpp>
#include <rojo/graphics/resource/program_resource.hpp>
#include <rojo/graphics/resource/buffer.hpp>

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
        template <class T, buffer_type BufferType> using buffer = buffer_resource<T, BufferType, GraphicsBackend>;
        template <class Vertex> using vertex_buffer = buffer<Vertex, buffer_type::array>;
        typedef buffer<unsigned int, buffer_type::element_array> index_buffer;
        
        /// Initializes the graphics device with
        /// it's default settings
        graphics_device()
        {
            enable(feature::depth_testing, false);
            enable(feature::blending, true);
            enable(feature::scissor_test, false);
            enable(feature::texture_mapping, true);
        }

        template <class... Args>
        texture create_texture(Args&&... args)
        { return create<texture>(args...); }
        
        template <class... Args>
        shader create_shader(Args&&... args)
        { return create<shader>(args...); }

        template <class... Args>
        program create_program(Args&&... args)
        { return create<program>(args...); }

        template <class T, buffer_type BufferType, class... Args>
        buffer<T, BufferType> create_buffer(Args&&... args)
        { return create<buffer<T, BufferType>(args...); }

        template <class Vertex, class... Args>
        vertex_buffer<Vertex> create_vertex_buffer(Args&&... args)
        { return create<vertex_buffer<Vertex>(args...); }

        template <class... Args>
        index_buffer create_index_buffer(Args&&... args) 
        { return create<index_buffer>(args...); }

        template <class Resource, class... Args>
        Resource create(Args&&... args)
        { return Resource{m_backend, std::forward(args)...} }

        /// enables a feature
        /// \param f the feature you wish to enable (or disable)
        /// \param enable true to enable the feature; false to disable it 
        void enable(feature f, bool enable = true)
        {            
            m_features[static_cast<unsigned>(f)] = enable;
            backend().enable(f, enable);
        }

        /// determines whether the feature is enabled
        /// \param f the feture you wish to check
        /// \return true if the feature is enabled, false otherwise
        bool is_enabled(feature f) const
        { return m_features[static_cast<unsigned>(f)]; }

        /// sets the scissor rect
        /// \param r The scissor rect
        /// \note 
        /// If scissor testing is diabled, the scissor rect
        /// will not be set.
        void scissor(const rect& r)
        {
            assert(is_enabled(feature::scissor_test) && "scissor testing is not enabled");

            if(!is_enabled(feature::scissor_test))
            {
                return;
            }

            m_scissor_rect = r;
            backend().scissor(r);
        }

        /// \return the scissor rect
        const rect& scissor() const
        { return m_scissor_rect; }

        /// sets the blend function to be used for blending
        /// \param fn The function you wish to use
        /// \note This sets the factors used by the blend equation
        /// \note If blending is disabled, this function does nothing
        /// \see blend_equation To set/get the blend equation
        void blend_function(const blend::function& fn)
        {
            assert(is_enabled(feature::blending) && "blending is not enabled");

            if(!is_enabled(feature::blending)) 
            {
                return;
            }

            m_blend.function = fn;
            backend().blend_function(fn);
        }

        /// \return the blend function this graphics device is using for blending
        const blend::function& blend_function() const
        { return blend().function; }

        /// sets the blend equation to be used for blending
        /// \param equation The blend equation you wish to set it to
        /// \note By defualt, the blend equation is blend::equation::add, as this
        ///       is the most commonly used value.
        /// \see blend_function To get/set the blend function
        void blend_equation(const blend::equation& equation)
        { 
            assert(is_enabled(feature::blending) && "blending is not enabled");

            if(is_enabled(feature::blending))
            {
                return;
            }

            backend().blend_equation(equation);
        }
        /// \return the blend equation this graphics device is using for blending
        const blend::equation& blend_equation() const
        { return blend().equation; }

        /// sets the blend object used by this graphics device
        /// \param blend What you wish to set it to
        void blend(const blend& blend)
        {
            blend_function(blend);
            blend_equation(equation);
        }
      
        /// \return the blend object used by this graphics device
        const blend& blend() const
        { return m_blend; }

        /// Sets the viewport
        /// \param r The value you wish to set the viewport
        void viewport(const rect& r)
        {
            m_viewport = r;
            backend().viewport(r);
        }

        /// \return The current viewport
        const rect& viewport() const
        { return m_viewport; }

        /// Sets the clear flags
        /// \param flags The buffers you wish to clear
        void clear_flags(const clear_flags& flags)
        { 
            // todo: assertions if depth buffer is not enabled
            // OR enable automagically for them huehuehuehue
            // assertions seems better IMO
            m_clear_flags = flags;
            backend().clear_flags(flags);
        }

        /// \return The clear flags
        const clear_flags& clear_flags() const
        { return m_clear_flags; }

        /// Sets the clear colour
        /// \param colour The colour you wish to set it to
        void clear_colour(const colour4& colour)
        {
            m_clear_colour = colour;
            backend().clear_colour(colour);
        }

        /// \return The clear colour
        const clear_colour& clear_colour() const
        { return m_clear_colour; }


        /// Clears the appropriate buffers
        void clear()
        { backend().clear(); }
        void clear(const colour4& colour)
        { clear_colour(colour); clear(); }
        void clear(const clear_flags& flags)
        { clear_flags(flags); clear(); }
        void clear(const colour4& colour, const clear_flags& flags)
        { clear_colour(colour); clear_flag(flags); clear(); }

    private:

        graphics_backend& backend() 
        { return m_backend; }


        /// Describes the enabled features
        std::array<bool, feature::count> m_features; 

        /// Used to describe how blending is done
        blend m_blend;

        /// The rect that describes the scissor rect
        rect m_scissor_rect;

        /// The flags used for clearing
        clear_flags m_clear_flags;

        /// The colour used for clearing
        colour4 m_clear_colour;

        /// The viewport
        rect m_viewport;

        /// The backend used by the device
        graphics_backend m_backend;
    };
}

#endif // ROJO_GRAPHICS_GRAPHICS_DEVICE_HPP
