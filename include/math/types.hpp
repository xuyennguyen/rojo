#ifndef ROJO_MATH_TYPES_HPP
#define ROJO_MATH_TYPES_HPP

#include <glm/glm.hpp>

namespace rojo
{
    using glm::vec3;
    using glm::vec2;
    using glm::mat3;
    using glm::mat4;
   
    typedef glm::vec4 colour4;

    struct rect
    {
        vec2 position;
        vec2 size;
    };
}

#endif // ROJO_MATH_TYPES_HPP
