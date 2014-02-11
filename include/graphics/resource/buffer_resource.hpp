#ifndef ROJO_GRAPHICS_BUFFER_RESOURCE_HPP
#define ROJO_GRAPHICS_BUFFER_RESOURCE_HPP

#include <array>
#include <vector>

//#include <rojo/util/array_reference.hpp>
#include <rojo/graphics/types.hpp>

namespace rojo
{
    template <class T, buffer_type BufferType, class GraphicsBackend>
    class buffer_resource
    {
    public:

        static constexpr const buffer_type type = BufferType;

        typedef T data_type;
        typedef GraphicsBackend graphics_backend;
        typedef typename graphics_backend::buffer_handle_type handle;

        buffer_resource(graphics_backend& backend, const buffer_usage& usage)
            : m_backend{backend}, m_usage{usage}
        {
        }

        buffer_resource(graphics_backend& backend, const buffer_usage& usage)
            : m_backend{backend}, m_usage{usage}
        {
        }

        ~buffer_resource()
        {
            destroy();
        }

        void destroy()
        {
            if(valid())
            {
                backend().destroy(m_handle);
            }
        }

        void data(const T* ptr, std::size_t count, const buffer_usage& usage)
        { usage(usage); data(ptr, count); }
        void data(const T* ptr, std::size_t count)
        {
            backend().data(m_handle, reinterpret_cast<void*>(ptr), count * sizeof(T), usage()); 
        }

        void data(const std::vector<T>& vec, const buffer_usage& usage)
        { usage(usage); data(vec); }
        void data(const std::vector<T>& vec)
        {
            data(&vec[0], vec.size());
        }

        template <std::size size>
        void data(const std::array<T, size>& arr, const buffer_usage& usage)
        { usage(usage); data(arr); }
        template <std::size_t size>
        void data(const std::array<T, size>& arr)
        {
            data(&arr[0], arr.size());
        }

        std::unique_ptr<T[]> data()
        {
            return {backend().data(m_handle)};
        }

        void sub_data(std::size_t offset, const T* ptr, std::size_t count)
        {
            backend().sub_data(m_handle, offset, reinterpret_cast<void*>(ptr), count);
        }

        void sub_data(std::size_t offset, const std::vector<T>& vec)
        {
            sub_data(offset, &vec[0], vec.size());
        }

        template <std::size_t size>
        void sub_data(std::size_t offset, std::array<T, size> arr) 
        { sub_data(offset, &arr[0], arr.size()); }
    
        graphics_backend& backend() const
        { return m_backend; }

        const handle& handle() const
        { return m_handle; }

        void usage(const buffer_usage& usage)
        { m_usage = usage; }

        const buffer_usage& usage() const
        { return m_usage; }

        bool valid() const
        { return backend().valid(m_handle); }

        inline bool operator bool() const
        { return valid(); }
         
    private:

        buffer_usage m_usage;

        handle m_handle;

        graphics_backend& m_backend;
    };
}

#endif // ROJO_GRAPHICS_VERTEX_BUFFER_RESOURCE_HPP
