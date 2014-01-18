#ifndef ROJO_GRAPHICS_VIEW_HPP
#define ROJO_GRAPHICS_VIEW_HPP

namespace rojo
{
    struct view
    {
        rect rect = rect{0, 0, 100, 100};
        colour4 clear_colour;

        unsigned clear_flags;
    };
}

#endif // ROJO_GRAPHICS_VIEW_HPP
