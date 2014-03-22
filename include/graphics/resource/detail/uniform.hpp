#ifndef ROJO_GRAPHICS_RESOURCES_DETAIL_UNIFORM_HPP
#define ROJO_GRAPHICS_RESOURCES_DETAIL_UNIFORM_HPP 

namespace rojo
{
    template <class Program, class T>
    class uniform 
    { 
    public:

        typedef uniform<Program, T> this_type;
        typedef T data_type;
        typedef Program program;
        typedef typename program::graphics_backend graphics_backend;
        // todo: possibly rename this handle?
        typedef typename graphics_backend::uniform_location_type location;

        uniform(program& program, const location& location)
            : m_program{program}, m_location{location}
        {
        }

        graphics_backend& backend() const
        { return program.backend(); }

        const location& location() const
        { return m_location; }

        bool valid() const
        { return backend().valid(m_backend); }

        inline operator bool() const
        { return valid(); }

        const T& value() const
        { return m_value; }

        void value(const T& val)
        {
            m_value = val;
            // todo: fix; this wont work :(
            backend().uniform(program().handle(), m_location, val);
        }

        this_type& operator=(const T& val)
        { 
            value(val);
            return *this;
        }

        program& program() const
        { return m_program; }

    private:

        program& m_program;

        location m_location;

        T m_value;
    };
}

#endif // ROJO_GRAPHICS_RESOURCES_DETAIL_UNIFORM_HPP 
