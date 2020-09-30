#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <iterator>
#include <utility>
#include <chrono>

template <class T>
std::remove_reference_t<T>&& move_implementation(T&& obj)
{   /* r-value static cast */
    /* nothing is being moved */
    return static_cast<std::remove_reference_t<T>&&>(obj);
}

template <class T>
void swap_move(T &lhs, T &rhs)
{
    T temp = move_implementation(lhs);
    lhs = move_implementation(rhs);
    rhs = move_implementation(temp);
}

template <class T>
void print(const std::vector<T> &obj)
{
    for(const auto &unit : obj)
    {
        std::cout << unit << " ";
    }
    std::cout << std::endl;
}

 int main()
{
    std::vector<int> lhs{0, 2, 4, 8, 16, 32, 64, 128};
    std::vector<int> rhs{128, 64, 32, 16, 8, 4, 2, 0};

    print(lhs);
    print(rhs);

    auto start = std::chrono::high_resolution_clock::now();
    swap_move(lhs, rhs);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "moving swap: " << duration.count() << " microseconds" << std::endl;

    print(lhs);
    print(rhs);

    return 0;
}
