#ifndef TIMER_HPP_
#define TIMER_HPP_
#include <chrono>
using unitofmeassure = std::chrono::microseconds;

class Timer {
    private:
        std::chrono::high_resolution_clock::time_point t1, t2;
        unitofmeassure elapsed;
    public:
        Timer() { elapsed = unitofmeassure(0); }
        void start() { t1 = std::chrono::high_resolution_clock::now(); }
        void stop() { t2 = std::chrono::high_resolution_clock::now(); elapsed += std::chrono::duration_cast<unitofmeassure>(t2-t1); };
        unitofmeassure duration() { return elapsed; /*std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1);*/ }
        void reset() { elapsed = unitofmeassure(0); }

};
#endif
