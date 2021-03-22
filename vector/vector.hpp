#include <utility>
#include <exception>
#include <iterator>
#include <type_traits>

namespace my
{
    template <typename T>
    class vector
    {
    public:
        //////////////////////
        //   MEMBER TYPES   //
        //////////////////////

        using value_type = T;
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;
        using reference = value_type&;
        using const_reference = const value_type&;
        using iterator = value_type*;
        using const_iterator = const value_type*;
        using reverse_iterator = value_type*;
        using const_reverse_iterator = const value_type*;

    public:
        //////////////////////
        //   CONSTRUCTORS   //
        //////////////////////

        constexpr vector();
        constexpr vector(std::size_t count, const T& value);

        template <typename InputIt>
        vector(InputIt first, InputIt last);

        constexpr vector(const vector& other);
        constexpr vector(vector&& other) noexcept;

        constexpr vector(std::initializer_list<T> init);

        ////////////////////
        //   DESTRUCTOR   //
        ////////////////////

        ~vector();

        //////////////////////////////
        //   ASSIGNMENT OPERATORS   //
        //////////////////////////////

        constexpr vector& operator = (const vector& other);
        constexpr vector& operator = (vector&& other) noexcept;
        constexpr vector& operator = (std::initializer_list<T> init);

        ////////////////////////
        //   ELEMENT ACCESS   //
        ////////////////////////

        constexpr reference at(size_type pos);
        constexpr const_reference at(size_type pos) const;

        constexpr reference operator [] (size_type pos);
        constexpr const_reference operator [] (size_type pos) const;

        constexpr reference front();
        constexpr const_reference front() const;

        constexpr reference back();
        constexpr const_reference back() const;

        constexpr T* data() noexcept;
        constexpr const T* data() const noexcept;

        ///////////////////
        //   ITERATORS   //
        ///////////////////

        constexpr iterator begin() noexcept;
        constexpr const_iterator begin() const noexcept;
        constexpr const_iterator cbegin() const noexcept;

        constexpr iterator end() noexcept;
        constexpr const_iterator end() const noexcept;
        constexpr const_iterator cend() const noexcept;

        //////////////////
        //   CAPACITY   //
        //////////////////

        [[nodiscard]] constexpr bool empty() const noexcept;

        [[nodiscard]] constexpr size_type size() const noexcept;

        constexpr void reserve(size_type new_cap);

        [[nodiscard]] constexpr size_type capacity() const noexcept;

        constexpr void shrink_to_fit();

        ///////////////////
        //   MODIFIERS   //
        ///////////////////

        constexpr void clear() noexcept;

        constexpr void push_back(const T& value);
        constexpr void push_back(T&& value);

        constexpr void pop_back();

        constexpr void resize(size_type count, const T& value = T{ });

        constexpr void swap( vector& other ) noexcept;

    private:
        size_type m_size;
        size_type m_capacity;
        T* m_data;
    };
}

#include "vector.tpp"