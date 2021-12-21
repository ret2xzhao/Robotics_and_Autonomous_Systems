#include <iostream>
#include <functional>

int Add(int a, int b)
{
    return a + b;
}

int Add5(int x)
{
    return Add(5, x);
}

class A
{
public:
    int F(int x)
    {
        return 2 * x;
    }
};

int main()
{
    auto bound_func = std::bind(Add, 3, 4);
    std::cout << bound_func() << "\n";

    auto bound_func1 = std::bind(Add, 5, std::placeholders::_1);
    std::cout << bound_func1(10) << "\n";

    A a;

    std::cout << a.F(7) << "\n";
    auto bound_func2 = std::bind(&A::F, a, std::placeholders::_1);
    std::cout << bound_func2(10) << "\n";

    return 0;
}