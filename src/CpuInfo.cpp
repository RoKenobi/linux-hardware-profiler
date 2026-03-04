#include "CpuInfo.h"
#include <fstream>
#include <iostream>
#include <sstream>

CpuInfo::CpuInfo() {
    parseProcCpuInfo();
}

void CpuInfo::parseProcCpuInfo() {
    std::ifstream file("/proc/cpuinfo");
    std::string line;
    int cores = 0;
    
    while (std::getline(file, line)) {
        if (line.find("model name") != std::string::npos) {
            data.model_name = line.substr(line.find(':') + 2);
        }
        if (line.find("cpu cores") != std::string::npos) {
            data.core_count = std::stoi(line.substr(line.find(':') + 2));
        }
        if (line.find("siblings") != std::string::npos) {
            data.thread_count = std::stoi(line.substr(line.find(':') + 2));
        }
        if (line.find("cache size") != std::string::npos) {
            data.cache_size = line.substr(line.find(':') + 2);
        }
        if (line.empty()) cores++;
    }
    if (data.core_count == 0) data.core_count = cores;
    if (data.thread_count == 0) data.thread_count = cores;
}

CPUData CpuInfo::getData() const { return data; }

void CpuInfo::print() const {
    std::cout << "[CPU] Model: " << data.model_name << std::endl;
    std::cout << "[CPU] Cores: " << data.core_count << " | Threads: " << data.thread_count << std::endl;
    std::cout << "[CPU] Cache: " << data.cache_size << std::endl;
}
