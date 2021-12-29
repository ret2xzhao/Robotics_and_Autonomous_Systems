#include <iostream>
#include <array>

template<typename T>
T average(const T& a, const T& b)
{
    return (a + b) / 2;
}

template<typename T>
struct Holder{
    T data;
};

template<typename T, int PrintCount>
struct Holder2
{
    T data;
    void Print() const {
        for(auto i=0; i<PrintCount; i++) {
            std::cout << data << "\n";
        }
    }
};

int main(){
    double a = 0.0;
    double b = 5.0;
    std::cout << average<double>(a, b) << "\n";
    std::cout << average<int>(a, b) << "\n";

    Holder<int> h;
    h.data = 10.5;
    std::cout << h.data << "\n";

    Holder2<int, 10> h2;
    h2.data = 10.5;
    h2.Print();

    std::array<float, 5> arr;
    return 0;
}