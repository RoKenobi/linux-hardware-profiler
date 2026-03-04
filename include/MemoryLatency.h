#ifndef MEMORY_LATENCY_H
#define MEMORY_LATENCY_H

#include <cstdint>
#include <cstddef>

class MemoryLatency {
public:
    MemoryLatency(size_t array_size_mb = 64);
    ~MemoryLatency();
    
    double measureLatencyNs();
    void print() const;

private:
    size_t size_bytes;
    uint8_t* buffer;
    uint8_t** ptr_array;
    double last_result_ns;
    
    void setupPointerChain();
};

#endif
