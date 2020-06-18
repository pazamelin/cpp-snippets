#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <iterator>
#include <utility>
#include <chrono>

template <class T>
void swap_copy(T &lhs, T &rhs)
{
    T temp = lhs;
    lhs = rhs;
    rhs = temp;
}

template <class T>
void swap_move(T &lhs, T &rhs)
{
    T temp = std::move(lhs);
    lhs = std::move(rhs);
    rhs = std::move(temp);
}

template <class T>
void randomVector(std::vector<T> &obj, size_t size)
{
    std::random_device rdev{};
    std::default_random_engine generator{rdev()};
    std::uniform_int_distribution<int> ud(0, 1024);
    for(size_t i = 0; i < size; i++)
    {
        obj.emplace_back(ud(generator));
    }
}

 int main()
{
    std::vector<int> lhs;
    randomVector(lhs, 1048576);

    std::vector<int> rhs;
    randomVector(rhs, 1048576);

    auto start = std::chrono::high_resolution_clock::now();
    swap_copy(lhs, rhs);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "copying swap: " << duration.count() << " microseconds" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    swap_move(lhs, rhs);
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "moving swap: " << duration.count() << " microseconds" << std::endl;

    return 0;
}
