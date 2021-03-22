#include "vector.hpp"

#include <iostream>
#include <vector>
#include <utility>
#include <functional>
#include <random>
#include <algorithm>

#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include <catch2/catch_all.hpp>

TEST_CASE("default", "[ctors]")
{
    my::vector<int> v;

    REQUIRE(v.empty());
    REQUIRE(v.data() == nullptr);
}

TEST_CASE("count-value", "[ctors]")
{
    REQUIRE(true);
}

TEST_CASE("first-last-iterators", "[ctors]")
{
    std::initializer_list<int> data = {1, 9, 1, 3};
    my::vector<int> v(data.begin(), data.end());

    REQUIRE(!v.empty());
    REQUIRE(v.size() == 4);
}

TEST_CASE("copy-ctor", "[ctors]")
{
    my::vector<int> v1 = {1, 2, 3, 4, 5};
    my::vector<int> v2 = v1;

    REQUIRE(v1.size() == v2.size());
}

TEST_CASE("move-ctor", "[ctors]")
{
    my::vector<int> v1 = {1, 2, 3, 4, 5};
    my::vector<int> v2 = std::move(v1);

    REQUIRE(v1.size() == 0);
    REQUIRE(v2.size() == 5);

    REQUIRE(v1.capacity() == 0);
    REQUIRE(v2.capacity() == 5);

    REQUIRE(v1.data() == nullptr);
    REQUIRE(v2.data() != nullptr);
}

TEST_CASE("initializer-list", "[ctors]")
{
    my::vector<int> v{1, 9, 1, 3};

    REQUIRE(!v.empty());
    REQUIRE(v.size() == 4);
}

TEST_CASE("push_back", "[modifiers]")
{
    my::vector<int> v;
    std::initializer_list<int> data = {1, 2, 3, 4, 5};
    for (auto element : data)
    {
        v.push_back(element);
    }

    REQUIRE(v.size() == data.size());
    REQUIRE(std::equal(v.begin(), v.end(), data.begin(), data.end()));
}

TEST_CASE("pop_back", "[modifiers]")
{
    std::initializer_list<int> data = {1, 2, 3, 4, 5};
    my::vector<int> v = data;

    REQUIRE(v.size() == data.size());
    REQUIRE(std::equal(v.begin(), v.end(), data.begin(), data.end()));

    auto data_end_it = data.end();
    for (std::size_t i = 0; i < data.size(); i++)
    {
        v.pop_back();
        data_end_it--;
        REQUIRE(std::equal(v.begin(), v.end(), data.begin(), data_end_it));
    }

    REQUIRE(v.empty());
    REQUIRE(v.capacity() == 0);
    REQUIRE(v.data() == nullptr);
}

TEST_CASE("resize", "[modifiers]")
{
    my::vector<int> v;
    v.resize(1024, 1);

    REQUIRE(v.size() == 1024);
    REQUIRE(std::all_of(v.cbegin(), v.cend(), [](auto value){ return value == 1; }));
}
