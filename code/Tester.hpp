#ifndef TESTER_HPP_
#define TESTER_HPP_

#include "Ort.hpp"
#include "KDTree.hpp"
#include <string>
#include "Timer.hpp"

class Tester {
    public:
        Tester();
        void Test1(std::string name);
        void Test2(std::string name);
        Ort BuildOrt(int n);

};

#endif
