#include <iostream>
#include <functional>

class Worker {
public:
    Worker(std::function<void(const double)> callback)
        : callback_(callback) {}

    void DoWork() {
        callback_(10);
    }

private:
    std::function<void(const double)> callback_;
};

int main(){
    double multiplier = 2.0;
    auto result_callback = [multiplier](const double result){
        std::cout << (multiplier * result) << "\n";
    };

    Worker w(result_callback);

    w.DoWork();

    return 0;
}