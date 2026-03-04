# 🐧 Linux Hardware Profiler
A low-level system diagnostic tool written in C++17 for Linux. Designed to extract CPU topology, measure raw memory latency using pointer-chasing algorithms, and perform controlled multi-threaded stress tests.

## 🎯 Project Overview

This tool bridges the gap between hardware capabilities and software observation. It is useful for:
- **System Validation:** Verifying CPU model and core count reported by the OS.
- **Performance Benchmarking:** Measuring memory subsystem latency without prefetcher interference.
- **Thermal/Power Testing:** Generating controlled load to test cooling solutions or power limits.

## 🚀 Key Features

- **CPU Topology Parsing:** Reads `/proc/cpuinfo` to extract Model Name, Cache Sizes, and Core Count.
- **Memory Latency Measurement:** Uses **pointer-chasing** on a large shuffled array to bypass hardware prefetchers.
- **Multi-threaded Stress Test:** Spawns worker threads pinned to specific cores (via `pthread_setaffinity_np`).
- **Structured Logging:** Outputs metrics to `metrics.csv` for external analysis.
- **Safety Controls:** Includes a `--safe-mode` flag to limit resource consumption.

## 🏗️ System Architecture

```text
+----------------+      +-------------------+      +----------------+
|    main.cpp    | ---> |  HardwareModules  | ---> |  Logger/CSV    |
+----------------+      +-------------------+      +----------------+
                                |
          +---------------------+---------------------+
          |                     |                     |
   +-------------+       +-------------+       +-------------+
   |  CpuInfo    |       | MemLatency  |       | StressTest  |
   | (/proc/*)   |       | (Pointer    |       | (pthread    |
   |             |       |  Chasing)   |       |  affinity)  |
   +-------------+       +-------------+       +-------------+

## ⚠️ Safety & Permissions

**IMPORTANT:** This tool performs stress tests that utilize 100% CPU capacity.
- **Run as Standard User:** Most features work without `sudo`.
- **Safe Mode:** Use `--safe-mode` to limit thread count and duration.
- **Thermal Warning:** Monitor system temperatures when running stress tests on laptops or confined systems.

See `SAFETY_WARNING.md` for detailed risk assessment.

## 🛠️ Build Instructions

Requires CMake, g++, and pthreads.

```bash
mkdir build && cd build
cmake ..
make
```

## 📖 Usage

### 1. System Info & Latency (Safe)
```bash
./profiler --info --latency
```

### 2. Full Stress Test (Advanced)
```bash
./profiler --stress --duration 10 --threads 4
```

### 3. Safe Mode (Recommended)
```bash
./profiler --safe-mode --all
```

## 📊 Sample Output

```text
=== Linux Hardware Profiler ===
[CPU] Model: AMD Ryzen 7 5800X
[CPU] Cores: 8 | Threads: 16
[MEM] Latency Test (64MB Array): 45.2 ns avg
[STRESS] Starting 4 threads for 10s...
[STRESS] Complete. Load generated.
[LOG] Results saved to metrics.csv
```

## 📈 Post-Processing

Use the included Python script to visualize latency results:

```bash
cd scripts
python3 plot_results.py ../metrics.csv
```

## 📄 License
Distributed under the MIT License. See `LICENSE` for more information.
