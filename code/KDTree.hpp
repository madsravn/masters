#ifndef KDTREE_HPP_
#define KDTREE_HPP_

#include <algorithm>
#include <random>
#include <vector>
#include <functional>
#include <cstdint>
#include "Point.hpp"
#include "Data.hpp"


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
        std::vector<Point> search(Region reg, Region query, int from, int to, int level);
        std::vector<Point> actualSearch(Region query);
        void saveState(Region query);
        void loadState(std::string filename);


    private:
        std::vector<Point> points;
        std::vector<int> middles;
        std::vector<Point> splits; // x for x splits and y for y splits
        Region region;
        bool debug;
};




#endif
