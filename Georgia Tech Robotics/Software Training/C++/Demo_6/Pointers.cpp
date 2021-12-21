#include <iostream>

int main()
{
    int data = 10;
    int* ptr = &data;

    std::cout << ptr << "\n";   // 0x7ffc9b211f04
    std::cout << &data << "\n"; // 0x7ffc9b211f04
    std::cout << *ptr << "\n";  // 10

    *ptr += 15;
    std::cout << data << "\n"; // 25

    std::string s = "Hello!";
    std::string* s_ptr = &s;
    std::cout << (*s_ptr).size() << "\n"; // 6
    std::cout << s_ptr->size() << "\n";   // 6

    return 0;
}