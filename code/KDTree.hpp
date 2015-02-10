#ifndef KDTREE_HPP_
#define KDTREE_HPP_

#include <algorithm>
#include <random>
#include <vector>
#include <functional>
#include <cstdint>
#include "Point.hpp"

struct Region {
    Point ll; // lower left
    Point ur; // upper right
};

enum class SIDE { LEFT, RIGHT, UP, DOWN};

inline std::ostream& operator << (std::ostream& os, const Region& reg) {
    os << "{ ";
    os << reg.ll;
    os << " => ";
    os << reg.ur;
    os << " }";
    return os;
}

class KDTree {

    public: 
        KDTree(int amount);
        void build();
        void buildTree(int start, int end, int level);
        void createRegion();
        std::vector<Point> makeRegion(std::vector<Point> reg, Point p);
        std::vector<Point> search(Point lowerleft, Point upperright);
        bool overlap(Region r1, Region r2);
        std::vector<Point> search(Region query);
        Region limitRegion(Region reg, Point p, SIDE side);
        std::vector<Point> search(Region region, Region query);

    private:
        std::vector<Point> points;
        Region region;
};




#endif
