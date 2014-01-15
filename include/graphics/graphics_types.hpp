#ifndef __ROJO_GRAPHICSTYPES_HPP__
#define __ROJO_GRAPHICSTYPES_HPP__

#include <rojo/math/types.hpp>

namespace rojo
{
    enum class feature
    {
        blending,
        scissor_test,
        stencil_test,
        depth_test,
        texture_mapping
    };


    struct blend_equation
    {
        
    };

    /*
    enum class blend_equation
    {
        add,
        subtract,
        reverse_subtract,
        min,
        max
    };

    enum class blend_function
    {

    };
    */
}

#endif // __ROJO_GRAPHICSTYPES_HPP__
