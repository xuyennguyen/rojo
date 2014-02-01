#ifndef ROJO_GRAPHICS_BACKENDS_BASE_BACKEND_HPP
#define ROJO_GRAPHICS_BACKENDS_BASE_BACKEND_HPP

#include <cassert>

#include <rojo/graphics/types.hpp>

#include <rojo/graphics/resource/texture_resource.hpp>
#include <rojo/graphics/resource/shader_resource.hpp>
#include <rojo/graphics/resource/program_resource.hpp>
#include <rojo/graphics/resource/vertex_buffer_resource.hpp>
#include <rojo/graphics/resource/index_buffer_resource.hpp>

namespace rojo
{
    template <class BackendTypes>
    class base_backend
    {    
    public:
        
        typedef BackendTypes backend_types;

        typedef typename backend_types::texture_handle_type texture_handle_type;
        typedef typename backend_types::index_buffer_handle_type index_buffer_handle_type;
        typedef typename backend_types::vertex_buffer_handle_type vertex_buffer_handle_type;
        typedef typename backend_types::shader_handle_type shader_handle_type;
        typedef typename backend_types::program_handle_type program_handle_type;
        typedef typename backend_types::uniform_handle_type uniform_handle_type;

    protected:
        
        base_backend() {}
        ~base_backend() {}

        // resource related functions

        // texture
        void destroy(const texture_handle_type&) { unimplemented(); }
        void upload(texture_handle_type&, const image_data&) { unimplemented(); }
        void wrap(texture_handle_type&, const texture_wrap&) { unimplemented(); }
        void filter(texture_handle_type&, const texture_filter&) { unimplemented(); }
        image_data data(const texture_handle_type&) { unimplemented(); return {}; }
        bool valid(const texture_handle_type&) { unimplemented(); return false; }

        // shader
        void destroy(const shader_handle_type&) { unimplemented(); }
        bool compile(shader_handle_type&, const shader_type&, const std::string& source) { unimplemented(); return false; } 
        bool valid(const shader_handle_type&) { unimplemented(); return false;

        // program
        void destroy(const program_handle_type&) { unimplemented(); }
        void attach_shader(program_handle_type&, const shader_type&, const shader_handle_type&) { unimplementated(); return false; } 
        bool link(program_handle_type&) { unimplementated(); return false; }
        uniform_handle_type& uniform_handle(const std::string& name) { unimplementated(); return {}; }
        void uniform(program_handle_type&, uniform_handle_type&, const void* data, const unsigned size) { unimplemented(); }
        bool valid(const program_handle_type&) { unimplemented(); return false; }
        bool valid(const uniform_handle_type&) { unimplemented(); return false; }

        // vertex_buffer


        // index_buffer

        

        // operations
        void enable(feature f, bool enable) { unimplemented(); }
        void scissor(const rect& r) { unimplemented(); }
        void blend_function(const blend::function& fn)  { unimplemented(); }
        void blend_equation(const blend::equation& eq) { unimplemented(); }
        void viewport(const rect& vp) { unimplemented(); }
        void clear_colour(const colour& c) { unimplemented(); }
        void clear() { unimplemented(); }

    private:

        typedef base_backend<HandleTypes> this_type;

        base_backend(const this_type&) = delete;
        base_backend(this_type&&) = delete;
        base_backend& operator=(const this_type&) = delete;
        base_backend& operator=(this_type&&) = delete;

        void unimplemented();
    };


    // dilleberate assertions in order to ensure that these functions 
    // are not called on accident (i.e. accidently did not override [hide] them)

    template <class HandleTypes> 
    base_backend<HandleTypes>::unimplemented() { assert(0); }
}

#endif // ROJO_GRAPHICS_BACKENDS_BASE_BACKEND_HPP
