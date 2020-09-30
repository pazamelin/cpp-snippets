#include <iostream>
#include <string>
#include <utility>

class Message
{
private:
    std::string data;
public:
    Message()
    {
        std::cout << "default constructor" << std::endl;
    }

    ~Message()
    {
        std::cout << "default destructor" << std::endl;
    }

    explicit Message(std::string  new_data) : data(std::move(new_data))
    {
        std::cout << "parametrized constructor" << std::endl;
    }

    Message(const Message& obj) : data(obj.data)
    {
        std::cout << "copy constructor" << std::endl;
    };

    Message(Message&& obj) noexcept : data(std::move(obj.data))
    {
        std::cout << "move constructor" << std::endl;
    };

    Message& operator=(const Message& other)
    {
        std::cout << "copy assignment operator" << std::endl;
        if (this != &other)
        {
            this->data = other.data;
        }
        return *this;
    }

    Message& operator=(Message&& other) noexcept
    {
        std::cout << "move assignment operator" << std::endl;
        if (this != &other)
        {
            this->data = std::move(other.data);
        }
        return *this;
    }

    /*
    Message(Message&& other) noexcept
    {
        std::cout << "move constructor using move assigment operator" << std::endl;
        *this = std::move(other);
    }
    */

    friend std::ostream& operator<<(std::ostream& os, const Message& obj);
};

std::ostream& operator<<(std::ostream& os, const Message& obj)
{
    os << obj.data;
    return os;
}

 int main()
{
    /* call to default constructor: */
    Message msg1{};
    std::cout << std::endl;

    /* call to parametrized constructor: */
    Message msg2{"msg2"};
    std::cout << msg2 << std::endl;
    std::cout << std::endl;

    /* call to copy constructor: */
    Message msg3{msg2};
    std::cout << msg3 << std::endl;
    std::cout << std::endl;

    /* call to move constructor: */
    Message msg4{std::move(Message{"msg4"})};
    std::cout << msg4 << std::endl;
    std::cout << std::endl;

    /* call to copy assignment operator: */
    Message msg5;
    msg5 = msg4;
    std::cout << msg5 << std::endl;
    std::cout << std::endl;

    /* call to move assignment operator: */
    Message msg6;
    msg6 = std::move(Message{"msg6"});
    std::cout << msg6 << std::endl;
    std::cout << std::endl;

    return 0;
}
