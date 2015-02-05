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
        KDTree(int amount);
        void build();
        void buildTree(int start, int end, int level);

    private:
        std::vector<Point> points;
};




#endif
