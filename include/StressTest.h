#ifndef STRESS_TEST_H
#define STRESS_TEST_H

#include <vector>
#include <thread>

class StressTest {
public:
    StressTest(int duration_sec, int thread_count);
    void run();
    void print() const;

private:
    int duration;
    int threads;
    void workerFunction();
};

#endif
