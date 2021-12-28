#include <iostream>

int main(){
    //auto f = [](){
    //    std::cout << "Lambdas!\n";
    //};
    int x=10;
    
    //auto f = [x](){
    auto f = [&x](){
        std::cout << "Lambdas! x = " << x << "\n";
    };

    x++;
    std::cout << "x = " << x << "\n";

    f();
    return 0;
}