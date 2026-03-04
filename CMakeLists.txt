cmake_minimum_required(VERSION 3.10)
project(LinuxHardwareProfiler VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(profiler
    src/main.cpp
    src/CpuInfo.cpp
    src/MemoryLatency.cpp
    src/StressTest.cpp
)

target_link_libraries(profiler Threads::Threads)
target_compile_options(profiler PRIVATE -O2)
