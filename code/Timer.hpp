#ifndef TIMER_HPP_
#define TIMER_HPP_
#include <chrono>
#include <string>


template<typename T>
struct ttime {
	enum {value = 1};
};

template<>
struct ttime<std::chrono::milliseconds> {
	enum {value = 2};
};

template<>
struct ttime<std::chrono::microseconds> {
    enum {value = 3};
};

template<>
struct ttime<std::chrono::nanoseconds> {
    enum {value = 4};
};

inline std::string conv(int i) {
    if(i == 2) {
        return "milliseconds";
    } 
    if(i == 3) {
        return "microseconds";
    }
    if(i == 4) {
        return "nanoseconds";
    }
    return "N/A";
}

template<typename T>
class Timer {
    private:
        std::chrono::high_resolution_clock::time_point t1, t2;
        T elapsed;
    public:
        Timer() { elapsed = T(0); }
        void start() { t1 = std::chrono::high_resolution_clock::now(); }
        void stop() { t2 = std::chrono::high_resolution_clock::now(); elapsed += std::chrono::duration_cast<T>(t2-t1); };
        T duration() { return elapsed;  }
        void reset() { elapsed = T(0); }
        void startover() { reset(); start();}
        std::string type() { return conv(ttime<T>::value);}

};


#endif
