//function pointers don't point to objects
#include <iostream>

class Worker {
public:
    Worker(void(*callback)(const double))
        : callback_(callback) {}

    void DoWork() {
        callback_(10);
    }

private:
    void(*callback_)(const double);
};

int main(){
    auto result_callback = [](const double result){
        std::cout << result << "\n";
    };

    Worker w(result_callback);

    w.DoWork();

    return 0;
}