#ifndef MY_UNIQUE_PTR_HPP
#define MY_UNIQUE_PTR_HPP

#include <utility>
#include <cstddef>

namespace my
{
    template <typename T>
    class unique_ptr
    {
    public:
        using element_type = T;

        explicit unique_ptr(T* data = nullptr)
            : m_data{data}
        { }

        unique_ptr(const unique_ptr& other) = delete;

        unique_ptr(unique_ptr&& other) noexcept
        {
            this->m_data = other.m_data;
            other.m_data = nullptr;
        }

        unique_ptr& operator = (const unique_ptr& other) = delete;

        unique_ptr& operator = (unique_ptr&& other) noexcept
        {
            if (this != &other)
            {
                delete m_data;

                m_data = other.m_data;
                other.m_data = nullptr;
            }
        }

        T& operator * ()
        {
            return *m_data;
        }

        const T& operator * () const
        {
            return *m_data;
        }

        T* operator -> ()
        {
            return m_data;
        }

        const T* operator -> () const
        {
            return m_data;
        }

        operator bool() const
        {
            return (m_data != nullptr);
        }

        ~unique_ptr()
        {
            delete m_data;
        }

    private:
        T* m_data = nullptr;
    };

    template <typename T, class... Args>
    unique_ptr<T> make_unique(Args&&... args)
    {
        return unique_ptr<T>{new T(std::forward<Args>(args)...)};
    }

} // namespace my

#endif // MY_UNIQUE_PTR_HPP