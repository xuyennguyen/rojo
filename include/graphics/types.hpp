#ifndef ROJO_GRAPHICS_TYPES_HPP
#define ROJO_GRAPHICS_TYPES_HPP

#include <rojo/math/types.hpp>

#include <rojo/graphics/view.hpp>

namespace rojo
{
    enum class feature
    {
        depth_test,
        blending,
        scissor_test,
        texture_mapping,

        count
    };

    struct blend
    {
        enum class factor
        {
            zero,
            one,
            src_colour,
            inv_src_colour,
            src_alpha,
            inv_src_alpha,
            dst_colour,
            inv_dst_colour,
            dst_alpha,
            inv_dst_alpha,
            constant_colour,
            inv_constant_colour,
            constant_alpha,
            inv_constant_alpha
        };

        struct function
        {
            factor src;
            factor dst;
        };

        enum class equation
        {
            add,
            subtract,
            reverse_subtract,
            min,
            max
        };

        function fn;
        equation equation;
    };


    struct clear_flag
    {
        enum
        {
            colour = 1 << 1,
            depth = 1 << 2,

            all = colour | depth
        };
    };

    typedef unsigned clear_flags;

    enum class texture_wrap
    {
        repeat,
        inv_repeat,
        clamp_to_edge,
        clamp_to_border
    };

    enum class texture_filter
    {
        linear,
        nearest
        /*
            // http://www.opengl.org/sdk/docs/man/xhtml/glTexParameter.xml 
         nearest_mipmap_nearest,
         linear_mipmap_nearest,
         linear_mipmap_linear
         */
    };

    enum class shader_type
    {
        vertex,
        fragment
    };

    enum class buffer_type
    {
        array,
        element_array
    };

    enum class buffer_usage
    {
        stream_draw,
        stream_read,
        static_draw,
        static_read,
        dynamic_draw,
        dynamic_read
    };
}

#endif // ROJO_GRAPHICS_GRAPHICSTYPES_HPP
