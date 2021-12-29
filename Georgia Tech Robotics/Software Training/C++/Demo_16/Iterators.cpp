#include <iostream>
#include <vector>

int main(){
    std::vector<int> v = {0,1,2,3,4};

    auto current_iter = v.begin();
    while(current_iter != v.end()){
        *current_iter += 10;
        std::cout << (*current_iter) << ", ";
        ++current_iter;
    }

    std::cout << std::endl;
    std::vector<int> v2;
    
    auto v_iter = std::back_inserter(v2);
    for(auto i=0; i<10; ++i) {
        *v_iter = i;
        ++v_iter;
    }
    for(const auto& e : v2){
        std::cout << e << ", "; 
    }

    return 0;
}