#include <iostream>

class A {
    int data;
};

struct B {
    int data;
};

int main()
{
    A a;
    //std::cout << a.data << "\n";

    B b;
    std::cout << b.data << "\n";

    return 0;
}