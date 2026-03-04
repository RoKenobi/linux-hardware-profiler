#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include "CpuInfo.h"
#include "MemoryLatency.h"
#include "StressTest.h"

void logMetrics(const std::string& filename, double latency) {
    std::ofstream file(filename, std::ios::app);
    std::time_t now = std::time(nullptr);
    file << std::ctime(&now) << "," << latency << "ns" << std::endl;
    std::cout << "[LOG] Results saved to " << filename << std::endl;
}

int main(int argc, char** argv) {
    bool runInfo = false;
    bool runLatency = false;
    bool runStress = false;
    bool safeMode = true;

    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "--info") runInfo = true;
        else if (arg == "--latency") runLatency = true;
        else if (arg == "--stress") runStress = true;
        else if (arg == "--safe-mode") safeMode = true;
        else if (arg == "--all") { runInfo = true; runLatency = true; runStress = true; }
    }

    if (argc == 1) { runInfo = true; runLatency = true; }

    std::cout << "=== Linux Hardware Profiler ===" << std::endl;

    if (runInfo) {
        CpuInfo cpu;
        cpu.print();
    }

    if (runLatency) {
        MemoryLatency mem(safeMode ? 16 : 64);
        double latency = mem.measureLatencyNs();
        mem.print();
        logMetrics("metrics.csv", latency);
    }

    if (runStress) {
        if (safeMode) {
            std::cout << "[WARN] Stress test limited to 2 threads / 5s in Safe Mode." << std::endl;
            StressTest stress(5, 2);
            stress.run();
        } else {
            StressTest stress(10, 4);
            stress.run();
        }
    }

    return 0;
}
