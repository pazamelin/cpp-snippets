#include "shared_ptr.hpp"
#include "unique_ptr.hpp"

#include <iostream>
#include <utility>
#include <functional>
#include <random>
#include <algorithm>
#include <type_traits>

#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include <catch2/catch_all.hpp>

TEST_CASE("nullptr-unique", "[ctors]")
{
    my::unique_ptr<int> ptr;
    REQUIRE(!ptr);
}

TEST_CASE("nullptr-shared", "[ctors]")
{
    my::shared_ptr<int> ptr;
    REQUIRE(!ptr);
}

TEST_CASE("new-unique", "[ctors]")
{
    my::unique_ptr<int> ptr{new int(10)};

    REQUIRE(ptr);
    REQUIRE(*ptr == 10);
}

TEST_CASE("new-shared", "[ctors]")
{
    my::shared_ptr<int> ptr{new int(10)};

    REQUIRE(ptr);
    REQUIRE(*ptr == 10);
    REQUIRE(ptr.use_count() == 1);
}

TEST_CASE("move-unique", "[ctors]")
{
    my::unique_ptr<int> ptr_1{new int(10)};
    REQUIRE(ptr_1);
    REQUIRE(*ptr_1 == 10);

    auto ptr_2{std::move(ptr_1)};
    REQUIRE(ptr_2);
    REQUIRE(*ptr_2 == 10);

    REQUIRE(!ptr_1);
}

TEST_CASE("move-shared", "[ctors]")
{
    my::shared_ptr<int> ptr_1{new int(10)};
    REQUIRE(ptr_1);
    REQUIRE(*ptr_1 == 10);
    REQUIRE(ptr_1.use_count() == 1);

    auto ptr_2{std::move(ptr_1)};
    REQUIRE(ptr_2);
    REQUIRE(*ptr_2 == 10);
    REQUIRE(ptr_2.use_count() == 1);

    REQUIRE(!ptr_1);
}

TEST_CASE("copy-shared", "[ctors]")
{
    my::shared_ptr<int> ptr_1{new int(10)};
    REQUIRE(ptr_1);
    REQUIRE(*ptr_1 == 10);
    REQUIRE(ptr_1.use_count() == 1);

    auto ptr_2{ptr_1};
    REQUIRE(ptr_2);
    REQUIRE(*ptr_2 == 10);
    REQUIRE(ptr_2.use_count() == 2);

    REQUIRE(ptr_1);
    REQUIRE(*ptr_1 == 10);
    REQUIRE(ptr_1.use_count() == 2);
}

struct foo
{
    foo(int a, double b)
        : a{a}
        , b{b}
    { }

    int a;
    double b;
};

TEST_CASE("make_unique", "[ctors]")
{
    auto ptr = my::make_unique<foo>(1, 5.0);
    REQUIRE(ptr);
    REQUIRE(ptr->a == 1);
    REQUIRE(ptr->b == 5.0);
}

TEST_CASE("make_shared", "[ctors]")
{
    auto ptr = my::make_shared<foo>(1, 5.0);

    REQUIRE(ptr);
    REQUIRE(ptr.use_count() == 1);
    REQUIRE(ptr->a == 1);
    REQUIRE(ptr->b == 5.0);
}