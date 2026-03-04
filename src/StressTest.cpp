#include "StressTest.h"
#include <iostream>
#include <chrono>
#include <cmath>

StressTest::StressTest(int duration_sec, int thread_count) 
    : duration(duration_sec), threads(thread_count) {}

void StressTest::workerFunction() {
    auto end = std::chrono::steady_clock::now() + std::chrono::seconds(duration);
    volatile double x = 0.0;
    while (std::chrono::steady_clock::now() < end) {
        for (int i = 0; i < 1000; i++) {
            x += std::sin(i) * 0.5;
        }
    }
}

void StressTest::run() {
    std::cout << "[STRESS] Starting " << threads << " threads for " << duration << "s..." << std::endl;
    std::vector<std::thread> workers;
    
    for (int i = 0; i < threads; i++) {
        workers.emplace_back(&StressTest::workerFunction, this);
    }
    
    for (auto& t : workers) {
        t.join();
    }
    std::cout << "[STRESS] Complete. Load generated." << std::endl;
}

void StressTest::print() const {
    std::cout << "[STRESS] Config: " << threads << " threads, " << duration << "s" << std::endl;
}
