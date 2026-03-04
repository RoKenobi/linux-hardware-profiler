#ifndef CPU_INFO_H
#define CPU_INFO_H

#include <string>

struct CPUData {
    std::string model_name;
    int core_count;
    int thread_count;
    std::string cache_size;
};

class CpuInfo {
public:
    CpuInfo();
    CPUData getData() const;
    void print() const;

private:
    CPUData data;
    void parseProcCpuInfo();
};

#endif
