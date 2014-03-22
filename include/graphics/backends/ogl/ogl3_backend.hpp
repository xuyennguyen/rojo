#ifndef ROJO_GRAPHICS_BACKENDS_OGL_OGL3_BACKEND_HPP
#define ROJO_GRAPHICS_BACKENDS_OGL_OGL3_BACKEND_HPP

#include <rojo/graphics/backends/base_backend.hpp>

#include <ogl_include.hpp>

namespace rojo
{
    class ogl3_backend : public base_backend<ogl3_backend>
    {
    public:

        typedef GLuint texture_handle_type;
        typedef GLuint buffer_handle_type;
        typedef GLuint shader_handle_type;
        typedef GLuint program_handle_type;
        typedef GLuint uniform_location_type;

        // resource related functions

        // texture
        void destroy(const texture_handle_type& handle);
        bool valid(const texture_handle_type& handle) const;
        void upload(texture_handle_type& handle, const image_data& data); 
        void wrap(texture_handle_type& handle, const texture_wrap& wrap); 
        void filter(texture_handle_type& handle, const texture_filter& filter);
        image_data data(const texture_handle_type& handle);
        void bind(const texture_handle_type& handle); 
        bool bound(const texture_handle_type& handle) const;

        // shader
        void destroy(const shader_handle_type& handle);
        bool valid(const shader_handle_type& handle) const;
        bool compile(shader_handle_type& handle, const shader_type& type, const std::string& source);

        // program
        void destroy(const program_handle_type& handle);
        bool valid(const program_handle_type& handle) const;
        bool valid(const uniform_location_type& uniform) const;
        void attach_shader(program_handle_type& handle, const shader_type& type, const shader_handle_type& handle);
        bool link(program_handle_type& handle);

        uniform_location_type& uniform_location(const std::string& name) const;
        
        // todo: this wont work with OpenGL
        void uniform(program_handle_type& handle, uniform_location_type& uniform_location, const void* data, const unsigned size);
        void bind(program_handle_type& handle);
        bool bound(program_handle_type& handle) const;

        // buffer
        void destroy(const buffer_handle_type& handle);
        bool valid(const buffer_handle_type& handle) const;
        void data(buffer_handle_type& handle, void* data, std::size_t size, const buffer_usage& usage);
        void sub_data(buffer_handle_type& handle, std::size_t offset, void* data, std::size_t size);
        void bind(const buffer_handle_type& handle);
        bool bound(const buffer_handle_type& handle) const;

        // operations
        void enable(feature f, bool enable); 
        void scissor(const rect& r); 
        void blend_function(const blend::function& fn);
        void blend_equation(const blend::equation& eq); 
        void viewport(const rect& vp);
        void clear_colour(const colour& c);
        void clear(); 
    };
}

#endif // ROJO_GRAPHICS_BACKENDS_OGL_OGL3_BACKEND_HPP
