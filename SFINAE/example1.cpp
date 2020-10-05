#include <type_traits> // for enable_if

#include <iostream>
#include <vector>
#include <string>
#include <utility>

/////////////////////////
//   META - << CHECK   //
/////////////////////////

template <typename T>
class has_output_operator
{
private:

    template <typename U, typename = decltype(std::cout << std::declval<U>())>
    static constexpr bool
    check(nullptr_t) noexcept
    {
        return true;
    }

    template <typename ...>
    static constexpr bool check(...) noexcept
    {
        return false;
    }

public:
    static constexpr bool value{check<T>(nullptr)};
};

///////////////////////////////////
//   META - CHECK IS ITERATABLE  //
///////////////////////////////////

template <typename T>
class is_iteratable
{
private:

    template <typename U>
    static constexpr decltype(std::begin(std::declval<U>()),
                              std::end(std::declval<U>()),
                              bool())
    check(nullptr_t) noexcept
    {
        return true;
    }

    template <typename ...>
    static constexpr bool check(...) noexcept
    {
        return false;
    }

public:
    static constexpr bool value{check<T>(nullptr)};
};

/////////////////////////
//   ITERATABLE TYPE   //
/////////////////////////

template <typename T>
typename std::enable_if<is_iteratable<T>::value && has_output_operator<T>::value, void>::type
print(const T& obj)
{
    std::cout << "iteratable object with operator <<" << std::endl;
}

template <typename T>
typename std::enable_if<is_iteratable<T>::value && !has_output_operator<T>::value, void>::type
print(const T& obj)
{
    std::cout << "iteratable object w/o operator <<" << std::endl;
}

//////////////
//   PAIR   //
//////////////

template <typename LHS, typename RHS>
typename std::enable_if<has_output_operator<std::pair<LHS, RHS>>::value, void>::type
print(const std::pair<LHS, RHS>& obj)
{
    std::cout << "pair with operator <<" << std::endl;
}

template <typename LHS, typename RHS>
typename std::enable_if<!has_output_operator<std::pair<LHS, RHS>>::value, void>::type
print(const std::pair<LHS, RHS>& obj)
{
    std::cout << "pair w/o operator <<" << std::endl;
}

/////////////////////////////
//   NON-ITERATABLE TYPE   //
/////////////////////////////

template <typename T>
typename std::enable_if<!is_iteratable<T>::value && has_output_operator<T>::value, void>::type
print(const T& value)
{
    std::cout << "non-iteratable object with operator <<" << std::endl;
}

template <typename T>
typename std::enable_if<!is_iteratable<T>::value && !has_output_operator<T>::value, void>::type
print(const T& value)
{
    std::cout << "non-iteratable object w/o operator <<" << std::endl;
}

//////////////////////
//   DEFAULT CASE   //
//////////////////////

template <typename ...>
[[maybe_unused]] void print(...)
{
    std::cout << "default case" << std::endl;
}

////////////////////
//   TEST TYPES   //
////////////////////

std::ostream& operator << (std::ostream& os, const std::vector<std::string>& obj)
{
    return os;
}

std::ostream& operator << (std::ostream& os, const std::pair<std::size_t, std::string>& obj)
{
    return os;
}

struct class_printable
{
    int value{0};
};

std::ostream& operator << (std::ostream& os, const class_printable& obj)
{
    return os;
}

struct class_not_printable{};

template <typename T>
void print_meta_info(std::ostream& os = std::cout)
{
    os << "is iteratable: " << is_iteratable<T>::value << std::endl;
    os << "has output operator: " << has_output_operator<T>::value << std::endl;
    os << std::endl;

    // TODO: check type deduction
}

int main()
{
    // testing meta check functions:

    std::cout << "std::vector<std::string>" << std::endl;  // iteratable, with operator <<
    print_meta_info<std::vector<std::string>>();  // 1, 1

    std::cout << "std::vector<int>" << std::endl;  // iteratable, w/o operator <<
    print_meta_info<std::vector<int>>();  // 1, 0

    std::cout << "std::pair<std::size_t, std::string>" << std::endl;  // pair, non-iteratable, with operator <<
    print_meta_info<std::pair<std::size_t, std::string>>();  // 0, 1

    std::cout << "std::pair<int, int>" << std::endl;  // pair, non-iteratable, w/o operator <<
    print_meta_info<std::pair<int, int>>();  // 0, 0

    std::cout << "class_printable" << std::endl;  // non-iteratable, with operator <<
    print_meta_info<class_printable>();  // 0, 1

    std::cout << "class_not_printable" << std::endl;  // non-iteratable, w/o operator <<
    print_meta_info<class_not_printable>();  // 0, 0

    {
        std::vector<std::string> vector_printable{"sfinae", "is", "dope"};
        print(vector_printable);

        std::vector<int> vector_not_printable{1, 2 ,3};
        print(vector_not_printable);

        std::pair<std::size_t, std::string> pair_printable{1u, "pair"};
        print(pair_printable);

        std::pair<int, int> pair_not_printable{1, 1};
        print(pair_not_printable);

        class_printable obj_printable{1};
        print(obj_printable);

        class_not_printable obj_not_printable{};
        print(obj_not_printable);
    }

    return 0;
}

