#include <iostream>
#include <vector>

void swap(double& x, double& y)
{
    double tmp = x;
    x = y;
    y = tmp;
}

class Printer
{
public:
    Printer(){
        std::cout << "New Printer created\n";
    }

    Printer(const Printer&){
        std::cout << "Printer copied\n";
    }

    ~Printer(){
        std::cout << "Printer destroyed\n";
    }
};

int main()
{
    double a = 50;
    double b = 100;
    swap(a, b);

    std::cout << "a = " << a << "\n";
    std::cout << "b = " << b << "\n";

    std::vector<Printer> v(5);
    for(const auto& p : v) {
        std::cout << "Loop iteration\n";
    }
    return 0;
}