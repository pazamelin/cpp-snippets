#include <iostream>
#include <memory>
#include <cassert>
 
using std::cout;
using std::endl;

// has foobar?

struct foo { using foobar = int; };
struct bar {};

template <typename T, typename = void>
struct has_foobar : std::false_type {};

template <typename T>
struct has_foobar<T, std::void_t<typename T::foobar>>
 : std::true_type {};

 // or decltype(T::foobar) for a member

int main()
{
    cout << has_foobar<foo>::value << endl;
    cout << has_foobar<bar>::value << endl;
    return 0;
}
