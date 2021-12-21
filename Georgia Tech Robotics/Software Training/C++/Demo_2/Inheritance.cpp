#include <iostream>

class Base
{
public:
    Base(int x, int y) : a(x), b(y) {}

    virtual ~Base(){
        // Always mark base class destructors "virtual".
    }

    virtual void PrintAll()
    {
        std::cout << "a = " << a << "\n";
        std::cout << "b = " << b << "\n";
    }

    void Func1() {}

    int a = 0;
    int b = 1;

protected:
    int e = 5;
};

class Derived : public Base
{
public:
    Derived(): Base(10, 20){}

    void PrintAll() override
    {
        Base::PrintAll();
        std::cout << "c = " << c << "\n";
        std::cout << "d = " << d << "\n";
    }

    void Func2() {
        std::cout << e << "\n";
    }
    int c = 3;
    int d = 4;
};

int main()
{
    Derived d;
    std::cout << d.b << "\n";

    d.Func1();
    d.Func2();

    d.PrintAll();
    //std::cout << d.e << "\n";

    return 0;
}