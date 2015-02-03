#ifndef KDTREE_HPP_
#define KDTREE_HPP_

#include <algorithm>
#include <random>
#include <vector>
#include <functional>
#include <cstdint>
#include "Point.hpp"

class KDTree {

    public: 
        KDTree(std::vector<Point> input);

    private:
        std::vector<Point> point;
};




#endif
