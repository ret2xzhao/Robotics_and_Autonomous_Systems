#include <iostream>

struct ParametricQuadratic {
    double a;
    double b;
    double c;

    //const - It tells us that the body of this operator is not allowed to change the object that it was called on.
    double operator() (const double x) const {
        return (a * x * x) + (b * x) + c;
    }
};

int main(){
    ParametricQuadratic f{1.0, 1.0, 0.0};
    std::cout << f(5) << "\n";
    return 0;
}