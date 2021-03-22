namespace my
{
    //////////////////////
    //   CONSTRUCTORS   //
    //////////////////////

    template <typename T>
    constexpr vector<T>::vector()
        : m_size{0}
        , m_capacity{0}
        , m_data{nullptr}
    { }

    template <typename T>
    constexpr vector<T>::vector(std::size_t count, const T& value)
        : m_size{count}
        , m_capacity{count}
        , m_data{new T[count]}
    {
        for (size_type i = 0; i < m_size; i++)
        {
            m_data[i] = value;
        }
    }

    template <typename T>
    template <typename InputIt>
    vector<T>::vector(InputIt first, InputIt last)
        : m_size{std::distance(first, last)}
        , m_capacity{m_size}
        , m_data{new T[m_size]}
    {
        size_type i = 0;
        for(; first != last; first++)
        {
            m_data[i++] = *first;
        }
    }

    template <typename T>
    constexpr vector<T>::vector(const vector<T>& other)
        : m_size{other.m_size}
        , m_capacity{m_size}
        , m_data{new T[m_size]}
    {
        for (size_type i = 0; i < m_size; i++)
        {
            m_data[i] = other.m_data[i];
        }
    }

    template <typename T>
    constexpr vector<T>::vector(vector<T>&& other) noexcept
        : m_size{other.m_size}
        , m_capacity{other.m_capacity}
        , m_data{other.m_data}
    {
        other.m_size = 0;
        other.m_capacity = 0;
        other.m_data = nullptr;
    }

    template <typename T>
    constexpr vector<T>::vector(std::initializer_list<T> init)
            : m_size{init.size()}
            , m_capacity{m_size}
            , m_data{new T[m_size]}
    {
        size_type i = 0;
        for(auto it = init.begin(); it != init.end(); it++)
        {
            m_data[i++] = std::move(*it);
        }
    }

    ////////////////////
    //   DESTRUCTOR   //
    ////////////////////

    template <typename T>
    vector<T>::~vector()
    {
        this->clear();
    }

    //////////////////////////////
    //   ASSIGNMENT OPERATORS   //
    //////////////////////////////

    template <typename T>
    constexpr vector<T>& vector<T>::operator = (const vector<T>& other)
    {
        if (this != &other)
        {
            delete[] this->m_data;
            this->m_data = new T[other.m_capacity];
            for (size_type i = 0; i < other.m_size; i++)
            {
                this->m_data[i] = other.m_data[i];
            }

            this->m_size = other.m_size;
            this->m_capacity = other.m_capacity;
        }
    }

    template <typename T>
    constexpr vector<T>& vector<T>::operator = (vector<T>&& other) noexcept
    {
        if (this != &other)
        {
            delete[] this->m_data;

            this->m_data = other.m_data;
            this->m_size = other.m_size;
            this->m_capacity = other.m_capacity;

            other.m_data = nullptr;
            other.m_data = 0;
            other.m_capacity = 0;
        }
    }

    template <typename T>
    constexpr vector<T>& vector<T>::operator = (std::initializer_list<T> init)
    {
        delete[] this->m_data;
        m_data = new T[init.size()];

        size_type i = 0;
        for (auto it = init.begin(); it != init.end(); it++)
        {
            m_data[i++] = std::move(*it);
        }
    }

    ////////////////////////
    //   ELEMENT ACCESS   //
    ////////////////////////

    template <typename T>
    constexpr T& vector<T>::at(size_type pos)
    {
        if (pos >= 0 && pos < m_size)
        {
            return m_data[pos];
        }
        else
        {
            throw std::out_of_range("");
        }
    }

    template <typename T>
    constexpr const T& vector<T>::at(size_type pos) const
    {
        if (pos >= 0 && pos < m_size)
        {
            return m_data[pos];
        }
        else
        {
            throw std::out_of_range("");
        }
    }

    template <typename T>
    constexpr T& vector<T>::operator [] (size_type pos)
    {
        return m_data[pos];
    }

    template <typename T>
    constexpr const T& vector<T>::operator [] (size_type pos) const
    {
        return m_data[pos];
    }

    template <typename T>
    constexpr T& vector<T>::front()
    {
        return m_data[0];
    }

    template <typename T>
    constexpr const T& vector<T>::front() const
    {
        return m_data[0];
    }

    template <typename T>
    constexpr T& vector<T>::back()
    {
        return m_data[m_size - 1];
    }

    template <typename T>
    constexpr const T& vector<T>::back() const
    {
        return m_data[m_size - 1];
    }

    template <typename T>
    constexpr T* vector<T>::data() noexcept
    {
        return m_data;
    }

    template <typename T>
    constexpr const T* vector<T>::data() const noexcept
    {
        return m_data;
    }

    ///////////////////
    //   ITERATORS   //
    ///////////////////

    template <typename T>
    constexpr typename vector<T>::iterator vector<T>::begin() noexcept
    {
        return m_data;
    }

    template <typename T>
    constexpr typename vector<T>::const_iterator vector<T>::begin() const noexcept
    {
        return m_data;
    }

    template <typename T>
    constexpr typename vector<T>::const_iterator vector<T>::cbegin() const noexcept
    {
        return m_data;
    }

    template <typename T>
    constexpr typename vector<T>::iterator vector<T>::end() noexcept
    {
        return m_data + m_size;
    }

    template <typename T>
    constexpr typename vector<T>::const_iterator vector<T>::end() const noexcept
    {
        return m_data + m_size;
    }

    template <typename T>
    constexpr typename vector<T>::const_iterator vector<T>::cend() const noexcept
    {
        return m_data + m_size;
    }

    //////////////////
    //   CAPACITY   //
    //////////////////

    template <typename T>
    [[nodiscard]] constexpr bool vector<T>::empty() const noexcept
    {
        return (m_size == 0);
    }

    template <typename T>
    [[nodiscard]] constexpr typename vector<T>::size_type vector<T>::size() const noexcept
    {
        return m_size;
    }

    template <typename T>
    constexpr void vector<T>::reserve(size_type new_cap)
    {
        if (m_capacity < new_cap)
        {
            T* data_tmp = new T[new_cap];
            for (size_type i = 0; i < m_size; i++)
            {
                data_tmp[i] = m_data[i];
            }

            delete[] m_data;
            m_data = data_tmp;
            m_capacity = new_cap;
        }
    }

    template <typename T>
    constexpr typename vector<T>::size_type vector<T>::capacity() const noexcept
    {
        return m_capacity;
    }

    template <typename T>
    constexpr void vector<T>::shrink_to_fit()
    {
        if (m_size == 0)
        {
            m_data = nullptr;
        }
        else if (m_size < m_capacity)
        {
            T* data_tmp = new T[m_size];
            for (size_type i = 0; i < m_size; i++)
            {
                data_tmp[i] = std::move(m_data[i]);
            }

            delete[] m_data;
            m_data = data_tmp;
        }

        m_capacity = m_size;
    }

    ///////////////////
    //   MODIFIERS   //
    ///////////////////

    template <typename T>
    constexpr void vector<T>::clear() noexcept
    {
        delete[] m_data;
        m_data = nullptr;
        m_size = 0;
        m_capacity = 0;
    }

    template <typename T>
    constexpr void vector<T>::push_back(const T& value)
    {
        if (m_size >= m_capacity)
        {
            size_type new_capacity = (m_capacity == 0) ? 1 : new_capacity * 2;
            T* data_tmp = new T[new_capacity];
            for (size_type i = 0; i < m_size; i++)
            {
                data_tmp[i] = std::move(m_data[i]);
            }

            delete[] m_data;
            m_data = data_tmp;
            m_capacity = new_capacity;
        }

        m_data[m_size] = value;
        m_size++;
    }

    template <typename T>
    constexpr void vector<T>::push_back(T&& value)
    {
        if (m_size >= m_capacity)
        {
            size_type new_capacity = (m_capacity == 0) ? 1 : new_capacity * 2;
            T* data_tmp = new T[new_capacity];
            for (size_type i = 0; i < m_size; i++)
            {
                data_tmp[i] = std::move(m_data[i]);
            }

            delete[] m_data;
            m_data = data_tmp;
            m_capacity = new_capacity;
        }

        m_data[m_size] = std::move(value);
        m_size++;
    }

    template <typename T>
    constexpr void vector<T>::pop_back()
    {
        if (m_size != 0)
        {
            if (m_size == 1)
            {
                m_size = 0;
                m_capacity = 0;
                m_data = nullptr;
            }
            else if (2 * (m_size - 1) < m_capacity)
            {

                m_capacity = m_capacity / 2;
                T* data_tmp = new T[m_capacity];

                for (size_type i = 0; i < m_size - 1; i++)
                {
                    data_tmp[i] = std::move(m_data[i]);
                }

                delete[] m_data;
                m_data = data_tmp;
                m_size--;
            }
            else
            {
                m_data[m_size - 1].~T();
                m_size--;
            }
        }
    }

    template <typename T>
    constexpr void vector<T>::resize(size_type count, const T& value)
    {
        if (m_size > count)
        {
            T* data_tmp = new T[count];

            for (size_type i = 0; i < count; i++)
            {
                data_tmp[i] = std::move(m_data[i]);
            }

            delete[] m_data;
            m_data = data_tmp;
            m_size = count;
            m_capacity = count;
        }
        else if (m_size < count)
        {
            T* data_tmp = new T[count];

            for (size_type i = 0; i < m_size; i++)
            {
                data_tmp[i] = std::move(m_data[i]);
            }

            for (size_type i = m_size; i < count; i++)
            {
                data_tmp[i] = value;
            }

            delete[] m_data;
            m_data = data_tmp;
            m_size = count;
            m_capacity = count;
        }
    }

    template <typename T>
    constexpr void vector<T>::swap(vector<T>& other) noexcept
    {
        std::swap(this->m_size, other.m_size);
        std::swap(this->m_capacity, other.m_capacity);
        std::swap(this->data, other.data);
    }

}