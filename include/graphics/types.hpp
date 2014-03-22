#ifndef ROJO_GRAPHICS_TYPES_HPP
#define ROJO_GRAPHICS_TYPES_HPP

#include <rojo/math/types.hpp>

#include <rojo/graphics/view.hpp>

namespace rojo
{
    enum class feature
    {
        DEPTH_TEST,
        BLENDING,
        SCISSOR_TEST,
        TEXTURE_MAPPING,

        COUNT
    };

    struct blend
    {
        enum class factor
        {
            ZERO,
            ONE,
            SRC_COLOUR,
            INV_SRC_COLOUR,
            SRC_ALPHA,
            INV_SRC_ALPHA,
            DST_COLOUR,
            INV_DST_COLOUR,
            DST_ALPHA,
            INV_DST_ALPHA,
            CONSTANT_COLOUR,
            INV_CONSTANT_COLOUR,
            CONSTANT_ALPHA,
            INV_CONSTANT_ALPHA
        };

        struct function
        {
            factor src;
            factor dst;
        };

        enum class equation
        {
            ADD,
            SUBTRACT,
            REVERSE_SUBTRACT,
            MIN,
            MAX
        };

        function fn;
        equation equation;
    };


    struct clear_flag
    {
        enum
        {
            COLOUR = 1 << 1,
            DEPTH = 1 << 2,

            ALL = COLOUR | DEPTH
        };
    };

    typedef unsigned clear_flags;

    enum class texture_wrap
    {
        REPEAT,
        INV_REPEAT,
        CLAM_TO_EDGE,
        CLAM_TO_BORDER
    };

    enum class texture_filter
    {
        LINEAR,
        NEAREST
            /*
            // http://www.opengl.org/sdk/docs/man/xhtml/glTexParameter.xml 
            nearest_mipmap_nearest,
            linear_mipmap_nearest,
            linear_mipmap_linear
            */
    };

    enum class shader_type
    {
        VERTEX,
        FRAGMENT
    };

    enum class buffer_type
    {
        ARRAY,
        ELEMENT_ARRAY
    };

    enum class buffer_usage
    {
        STREAM_DRAW,
        STREAM_READ,
        STATIC_DRAW,
        STATIC_READ,
        DYNAMIC_DRAW,
        DYNAMIC_READ
    };

    enum class attribute_data_type
    {
        UNSIGNED_BYTE = 0,
        SIGNED_BYTE,
        UNSIGNED_SHORT,
        SIGNED_SHORT,
        UNSIGNED_INT,
        INT,
        FLOAT,
        DOUBLE,

        DEFAULT = FLOAT
    };

    enum class attribute_vector_count
    {
        ONE = 1,
        TWO,
        THREE,
        FOUR
    };

    enum class attribute_component_count
    {
        ONE = 1,
        TWO,
        THREE,
        FOUR
    };
}

#endif // ROJO_GRAPHICS_GRAPHICSTYPES_HPP
