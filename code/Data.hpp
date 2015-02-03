#ifndef DATA_HPP_
#define DATA_HPP_

#include <vector>
#include "Ort.hpp"
#include "Point.hpp"


class Data {

    public:
        static std::vector<Point> generate(int amount);
        static std::vector<Point> generateRandom(int amount, int start, int stop);

};

#endif
