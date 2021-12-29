#include <iostream>
#include <algorithm>
#include <vector>

int main(){
    std::vector<int> v = {0,1,2,3,4};
    auto print_int = [](const int& e){
        std::cout << e << ", ";
    };

    std::for_each(v.begin(), v.end(), print_int);
    
    return 0;
}