#include <iostream>
#include <string>

///////////////////
//   IS CLASS   //
///////////////////

/*
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

template <typename T>
struct is_class
{
private:
    template <typename Class>
    static int f(int Class::* ptr_to_member) { return 0; };

    template <typename ...>
    static char f(...) { return 0; };
public:
    static constexpr bool value = are_same<decltype(f<T>(nullptr)), int>::value;
};
*/

template <typename T>
struct is_class
{
private:
    template <typename C>
    static constexpr bool f(int C::* ptr_to_member) noexcept
    {
        return true;
    };

    template <typename ...>
    static constexpr bool f(...) noexcept
    {
        return false;
    };

public:

    static constexpr bool value{f<T>(nullptr)};
};

struct foo { };

int main()
{
    std::cout << is_class<int>::value << "\n";
    std::cout << is_class<std::string>::value << "\n";

    return 0;
}
