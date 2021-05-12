#include <iostream>

// printer with needed output
template <bool is_needed>
struct printer
{
    template<typename T, typename... Args>
    static void print(T first, Args... args)
    {
        print(first);
        print(args...);
    }

    template<typename T>
    static void print(T v)
    {
        std::cerr << v;
    }
};

// printer with no needed output
template <>
struct printer<false>
{
    template<typename T, typename... Args>
    static void print(T first, Args... args) { }
};

// registration
#define REG_PRINTER(name, is_needed)                           \
    template<typename T, typename... Args>                     \
    void name(T first, Args... args)                           \
    {                                                          \
        printer<is_needed>::print<T, Args...>(first, args...); \
    }

// usage
REG_PRINTER(debug_output_1, true);
REG_PRINTER(debug_output_2, false);

int main()
{
    debug_output_1("val1:", 1, ", val2:", 2);
    debug_output_2("val1:", 1, ", val2:", 2);

    return 0;
}
