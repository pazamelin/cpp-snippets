#include <iostream>
#include <sstream>
#include <string>
#include <exception>
using namespace std;

void EnsureEqual(const string& left, const string& right)
{
    if(left != right)
    {
        stringstream ss;
        ss << left << " != " << right;
        throw runtime_error(ss.str());
    }
}
int main() {
    try {
        EnsureEqual("C++", "C++");
        EnsureEqual("C++", "C");
    } catch (runtime_error& e) {
        cout << e.what() << endl;
    }
    return 0;
}
