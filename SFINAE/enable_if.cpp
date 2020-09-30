#include <iostream>

///////////////////
//   ENABLE IF   //
///////////////////

template <bool B, typename T>
struct enable_if  // is to be called with B == false,
{ };              // because otherwise partial specialization
                  // for true will be more preferable option

template <typename T>
struct enable_if<true, T>
{   // partial specialization for true
    using type = T;
};

int main()
{
    return 0;
}
