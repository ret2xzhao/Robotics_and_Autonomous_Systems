#include <iostream>
#include <thread>

void JobA() {
    std::cout << "Start JobA\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Stop JobA\n";
}

void JobB() {
    std::cout << "Start JobB\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Stop JobB\n";
}

//void AllJobs1() {
//    JobA();
//    JobB();
//}

void AllJobs2() {
    std::thread thread_a (JobA);
    std::thread thread_b (JobB);
    thread_a.join();
    thread_b.join();
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