#include <iostream>
#include <thread>
#include <future>

int JobA(int x) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return 10 * x;
}

int JobB(int x) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return 5 + x;
}

//void AllJobs1() {
//    std::cout << "a = " << JobA(2) << "\n";
//    std::cout << "b = " << JobB(2) << "\n";
//}

void AllJobs2() {
    std::future<int> f_a =std::async(JobA, 2);
    std::future<int> f_b =std::async(JobB, 2);

    while (f_a.wait_for(std::chrono::milliseconds(100)) == std::future_status::timeout) {
        std::cout << "Waiting for JobA...\n";
    }

    std::cout << "a = " << f_a.get() << "\n";
    std::cout << "b = " << f_b.get() << "\n";
}

// -lpthread
int main() {
    const auto start_time = std::chrono::steady_clock::now();
    //AllJobs1();
    AllJobs2();
    const auto end_time = std::chrono::steady_clock::now();
    const auto elapsed_time = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);
    std::cout << elapsed_time.count() << " seconds\n";
    return 0;
}