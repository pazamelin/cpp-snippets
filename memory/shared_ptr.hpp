#ifndef MY_SHARED_PTR_HPP
#define MY_SHARED_PTR_HPP

#include <utility>
#include <cstddef>

namespace my
{
    struct control_block
    {
        std::size_t ref_counter = 0;
    };

    template <typename T>
    class shared_ptr
    {
    public:
        using element_type = T;

        explicit shared_ptr(T* data)
            : m_data{data}
            , m_cb{new control_block}
        {
            m_cb->ref_counter++;
        }

        explicit shared_ptr(std::nullptr_t ptr = nullptr)
            : m_data{ptr}
            , m_cb{ptr}
        { }

        shared_ptr(const shared_ptr& other)
            : m_data{other.m_data}
            , m_cb{other.m_cb}
        {
            m_cb->ref_counter++;
        }

        shared_ptr(shared_ptr&& other) noexcept
            : m_data{other.m_data}
            , m_cb{other.m_cb}
        {
            other.m_data = nullptr;
            other.m_cb = nullptr;
        }

        shared_ptr& operator = (const shared_ptr& other)
        {
            if (this != &other)
            {
                try_delete();

                m_cb->ref_counter++;

                this->m_cb = other->m_cb;
                this->m_data = other.m_data;
            }
        }

        shared_ptr& operator = (shared_ptr&& other) noexcept
        {
            if (this != &other)
            {
                try_delete();

                m_cb = other->m_cb;
                m_data = other.m_data;

                other.m_cb = nullptr;
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

        std::size_t use_count() const noexcept
        {
            return m_cb->ref_counter;
        }

        void try_delete()
        {
            if (m_cb && m_cb->ref_counter == 0)
            {
                delete m_data;
                delete m_cb;
            }
        }

        ~shared_ptr()
        {
            try_delete();
        }

    private:
        T* m_data = nullptr;
        control_block* m_cb = nullptr;
    };

    template <typename T, class... Args>
    shared_ptr<T> make_shared(Args&&... args)
    {
        return shared_ptr<T>{new T(std::forward<Args>(args)...)};
    }

} // namespace my

#endif // MY_SHARED_PTR_HPP