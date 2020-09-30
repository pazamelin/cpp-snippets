#include <iostream>
#include <string_view>

// https://stackoverflow.com/a/20170989/13589244
template <typename T>
constexpr auto type_name() noexcept
{
    std::string_view name, prefix, suffix;
#ifdef __clang__
    name = __PRETTY_FUNCTION__;
  prefix = "auto type_name() [T = ";
  suffix = "]";
#elif defined(__GNUC__)
    name = __PRETTY_FUNCTION__;
    prefix = "constexpr auto type_name() [with T = ";
    suffix = "]";
#elif defined(_MSC_VER)
    name = __FUNCSIG__;
  prefix = "auto __cdecl type_name<";
  suffix = ">(void) noexcept";
#endif
    name.remove_prefix(prefix.size());
    name.remove_suffix(suffix.size());
    return name;
}


//////////////////
//   ARE SAME   //
//////////////////

template <typename LHS, typename RHS>
struct are_same
{
    static constexpr bool value = false;
};

template <typename T>
struct are_same<T, T>
{
    static constexpr bool value = true;
};

/////////////////////////////
//   IS LVALUE REFERENCE   //
/////////////////////////////

template <typename T>
struct is_lvalue_reference
{
    static constexpr bool value = false;
};

template <typename T>
struct is_lvalue_reference<T&>
{
    static constexpr bool value = true;
};

/////////////////////////////
//   IS RVALUE REFERENCE   //
/////////////////////////////

template <typename T>
struct is_rvalue_reference
{
    static constexpr bool value = false;
};

template <typename T>
struct is_rvalue_reference<T&&>
{
    static constexpr bool value = true;
};

//////////////////
//   IS CONST   //
//////////////////

template <typename T>
struct is_const
{
    static constexpr bool value = false;
};

template <typename T>
struct is_const<const T>
{
    static constexpr bool value = true;
};

//////////////////////
//   REMOVE CONST   //
//////////////////////

template <typename T>
struct remove_const
{
    using type = T;
};

template <typename T>
struct remove_const<const T>
{
    using type = T;
};

///////////////////
//   ADD CONST   //
///////////////////

template <typename T>
struct add_const
{
    using type = const T;
};

template <typename T>
struct add_const<const T>
{
    using type = const T;
};

//////////////////////////
//   REMOVE REFERENCE   //
//////////////////////////

template <typename T>
struct remove_reference
{
    using type = T;
};

template <typename T>
struct remove_reference<T&>
{
    using type = T;
};

template <typename T>
struct remove_reference<T&&>
{
    using type = T;
};

int main()
{
    {
        int x{0};
        int y{0};
        const int z{0};

        std::cout << "are same:" << "\n";

        std::cout << type_name<decltype(x)>() << ", "
                  << type_name<decltype(y)>() << ": "
                  << are_same <decltype(x), decltype(y)>::value << '\n';

        std::cout << type_name<decltype(x)>() << ", "
                  << type_name<decltype(z)>() << ": "
                  << are_same <decltype(x), decltype(z)>::value << '\n';

        std::cout << "\n";
    }

    {
        int x{0};
        int& y{x};

        std::cout << "is lvalue reference:" << "\n";

        std::cout << type_name<decltype(x)>() << ": "
                  << is_lvalue_reference<decltype(x)>::value << '\n';

        std::cout << type_name<decltype(y)>() << ": "
                  << is_lvalue_reference<decltype(y)>::value << '\n';

        std::cout << "\n";
    }

    {
        int x{0};
        int&& y{0};

        std::cout << "is rvalue reference:" << "\n";

        std::cout << type_name<decltype(x)>() << ": "
                  << is_rvalue_reference<decltype(x)>::value << '\n';

        std::cout << type_name<decltype(y)>() << ": "
                  << is_rvalue_reference<decltype(y)>::value << '\n';

        std::cout << "\n";
    }

    {
        int x{0};
        const int y{0};

        std::cout << "is const:" << "\n";

        std::cout << type_name<decltype(x)>() << ": "
                  << is_const<decltype(x)>::value << '\n';

        std::cout << type_name<decltype(y)>() << ": "
                  << is_const<decltype(y)>::value << '\n';

        std::cout << "\n";
    }


    {
        const int x{0};
        int y{0};

        std::cout << "remove const:" << "\n";

        std::cout << type_name<decltype(x)>() << " -> "
                  << type_name<remove_const<decltype(x)>::type>() << '\n';

        std::cout << type_name<decltype(y)>() << " -> "
                  << type_name<remove_const<decltype(y)>::type>() << '\n';

        std::cout << "\n";
    }

    {
        int x{0};
        const int y{0};

        std::cout << "add const:" << "\n";

        std::cout << type_name<decltype(x)>() << " -> "
                  << type_name<add_const<decltype(x)>::type>() << '\n';

        std::cout << type_name<decltype(y)>() << " -> "
                  << type_name<add_const<decltype(y)>::type>() << '\n';

        std::cout << "\n";
    }


    {
        int x{0};
        int& y{x};
        int&& z{0};

        std::cout << "remove reference:" << "\n";

        std::cout << type_name<decltype(x)>() << " -> "
                  << type_name<remove_reference<decltype(x)>::type>() << '\n';

        std::cout << type_name<decltype(y)>() << " -> "
                  << type_name<remove_reference<decltype(y)>::type>() << '\n';

        std::cout << type_name<decltype(z)>() << " -> "
                  << type_name<remove_reference<decltype(z)>::type>() << '\n';

        std::cout << "\n";
    }
}
