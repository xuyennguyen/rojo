#ifndef __ROJO_GRAPHICSTYPES_HPP__
#define __ROJO_GRAPHICSTYPES_HPP__

#include <rojo/math/types.hpp>

namespace rojo
{
    enum class feature
    {
        blending,
        scissor_test,
        depth_test,
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
}

#endif // __ROJO_GRAPHICSTYPES_HPP__
