#ifndef ROJO_GRAPHICS_BACKENDS_BASE_BACKEND_HPP
#define ROJO_GRAPHICS_BACKENDS_BASE_BACKEND_HPP

#include <cassert>

#include <rojo/graphics/types.hpp>

namespace rojo
{
    template <class Backend>
    class base_backend
    {
    public:

        typedef Backend backend_type;

        typedef typename backend_type::texture_handle_type texture_handle_type;
        typedef typename backend_type::buffer_handle_type buffer_handle_type;
        typedef typename backend_type::shader_handle_type shader_handle_type;
        typedef typename backend_type::program_handle_type program_handle_type;
        typedef typename backend_type::uniform_location_type uniform_location_type;

        // resource related functions

        // texture
        void destroy(const texture_handle_type& handle) 
        { backend().destroy(handle); }

        bool valid(const texture_handle_type& handle) const 
        { return backend().valid(handle); }

        void upload(texture_handle_type& handle, const image_data& data) 
        { check_if_bound(handle); backend().upload(handle, data); }

        void wrap(texture_handle_type& handle, const texture_wrap& wrap) 
        { check_if_bound(handle); backend().wrap(handle, data); }

        void filter(texture_handle_type& handle, const texture_filter& filter) 
        { check_if_bound(handle); backend().filter(handle, filter); }

        image_data data(const texture_handle_type& handle) 
        { return backend().data(handle); }

        void bind(const texture_handle_type& handle) 
        { backend().bind(handle); }

        bool bound(const texture_handle_type& handle) const 
        { return backend().bound(handle); }


        // shader

        void destroy(const shader_handle_type& handle) 
        { backend().destroy(handle); }

        bool valid(const shader_handle_type& handle) const
        { return backend().valid(handle); }

        bool compile(shader_handle_type& handle, const shader_type& type, const std::string& source) 
        { return backend().compile(handle, type, source); } 


        // program
        void destroy(const program_handle_type& handle) 
        { backend().destroy(handle); }

        bool valid(const program_handle_type& handle) const
        { return backend().valid(handle); }

        bool valid(const uniform_location_type& uniform) const
        { return backend().valid(uniform); }

        void attach_shader(program_handle_type& handle, const shader_type& type, const shader_handle_type& handle) 
        { backend().attach_shader(handle, type, handle); } 

        bool link(program_handle_type& handle) 
        { return backend().link(handle); }

        uniform_location_type& uniform_location(const std::string& name) const
        { return backend().uniform_location(name); }

        // todo: this wont work with OpenGL
        void uniform(program_handle_type& handle, uniform_location_type& uniform_location, const void* data, const unsigned size) 
        { check_if_bound(handle); backend().uniform(handle, uniform_location, data, size); }

        void bind(program_handle_type& handle) 
        { backend().bind(handle); }

        bool bound(program_handle_type& handle) const 
        { return backend().bound(handle); }


        // buffer
        void destroy(const buffer_handle_type& handle) 
        { backend().destroy(handle); }

        bool valid(const buffer_handle_type& handle) const
        { return backend().valid(handle); }

        void data(buffer_handle_type& handle, void* data, std::size_t size, const buffer_usage& usage)
        { check_if_bound(handle); backend().data(handle, data, size, usage); }

        void sub_data(buffer_handle_type& handle, std::size_t offset, void* data, std::size_t size)
        { check_if_bound(handle); backend().sub_data(handle, offset, data, size); }

        void bind(const buffer_handle_type& handle) 
        { backend().bind(handle); }

        bool bound(const buffer_handle_type& handle) const 
        { return backend().bound(handle); }


        // operations
        void enable(feature f, bool enable) 
        { backend().enable(f, enable); }

        void scissor(const rect& r) 
        { backend().scissor(r); }

        void blend_function(const blend::function& fn) 
        { backend().blend_function(fn); }

        void blend_equation(const blend::equation& eq) 
        { backend().blend_equation(eq); }

        void viewport(const rect& vp) 
        { backend().viewport(vp); }

        void clear_colour(const colour& c) 
        { backend().clear_colour(c); }

        void clear() 
        { backend().clear(); }
        //void render(const mesh& mesh) { unimplemented(); }

    protected:

        base_backend() {}
        ~base_backend() {}

    private:

        // utility fns
        template <class HandleType>
        void check_if_bound(const HandleType& handle) { if(!bound(handle)) { bind(handle); } }


        typedef base_backend<Backend> this_type;

        base_backend(const this_type&) = delete;
        base_backend(this_type&&) = delete;
        base_backend& operator=(const this_type&) = delete;
        base_backend& operator=(this_type&&) = delete;

        Backend& backend()
        { return *static_cast<Backend*>(this); }
        const Backend& backend() const
        { return *static_cast<const Backend*>(this); }
    };
}

#endif // ROJO_GRAPHICS_BACKENDS_BASE_BACKEND_HPP
