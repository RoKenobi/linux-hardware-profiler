#include "MemoryLatency.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <algorithm>
#include <random>

MemoryLatency::MemoryLatency(size_t array_size_mb) : size_bytes(array_size_mb * 1024 * 1024) {
    buffer = new uint8_t[size_bytes];
    ptr_array = new uint8_t*[size_bytes];
    setupPointerChain();
}

MemoryLatency::~MemoryLatency() {
    delete[] buffer;
    delete[] ptr_array;
}

void MemoryLatency::setupPointerChain() {
    for (size_t i = 0; i < size_bytes - 1; i++) {
        ptr_array[i] = &buffer[i + 1];
    }
    ptr_array[size_bytes - 1] = &buffer[0];

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(ptr_array, ptr_array + size_bytes, g);
    
    for (size_t i = 0; i < size_bytes - 1; i++) {
        *ptr_array[i] = (uint8_t*)ptr_array[i+1]; 
    }
}

double MemoryLatency::measureLatencyNs() {
    const int iterations = 1000000;
    volatile uint8_t* ptr = buffer;
    
    auto start = std::chrono::high_resolution_clock::now();
    
    for (int i = 0; i < iterations; i++) {
        ptr = (uint8_t*)*ptr;
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::nano> elapsed = end - start;
    
    last_result_ns = elapsed.count() / iterations;
    return last_result_ns;
}

void MemoryLatency::print() const {
    std::cout << "[MEM] Latency Test (" << size_bytes/1024/1024 << "MB Array): " 
              << last_result_ns << " ns avg" << std::endl;
}
