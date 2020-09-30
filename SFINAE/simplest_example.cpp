#include <iostream>
#include <string>

////////////////////////
//   SIMPLE EXAMPLE   //
////////////////////////

template <typename T>
typename T::value_type f(T param) // absence of T::value_type in T will cause a substitution failure
{                                 // e.g, - if T is int
    std::cout << "the first one" << std::endl;
    return 0;
}

template <typename ...Args>
int f(...)
{
    std::cout << "the second one" << std::endl;
    return 0;
}

int main()
{
          // simple example:
    f(5); // the first version of f is more preferable,
          // but causes a substitution failure

    return 0;
}
