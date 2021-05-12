#include <iostream>

// printer with needed output
template <bool is_needed>
class printer
{
public:

    template<typename T, typename... Args>
    printer(T first, Args... args)
    {
        print(first, args...);
    }

private:

    template<typename T>
    static void print(T v)
    {
        std::cerr << v;
    }

    template<typename T, typename... Args>
    static void print(T first, Args... args)
    {
        print(first);
        print(args...);
    }
};

// printer with no needed output
template <>
struct printer<false>
{
    template<typename T, typename... Args>
    printer(T first, Args... args) { }
};

#define REG_PRINTER(name, is_needed) \
    using name = printer<is_needed>

// usage: 

// register printer
using debug_output_1 = printer<true>;
using debug_output_2 = printer<false>;

// alternative registration
REG_PRINTER(debug_output_3, true);

int main()
{
    debug_output_1("some text\n"); 
    debug_output_2(1, "\n");        
    debug_output_3("value_1: ", 3, ", value_2: ", 5, "\n");

    return 0;
}
