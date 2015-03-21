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
        KDTree(int amount, std::vector<Point> input);
        void build();
        void buildTree(int start, int end, int level);
        void createRegion();
        std::vector<Point> makeRegion(std::vector<Point> reg, Point p);
        std::vector<Point> search(Point lowerleft, Point upperright);
        bool overlap(Region r1, Region r2);
        std::vector<Point> search(Region query);
        Region limitRegion(Region reg, Point p, SIDE side);
        void search(Region reg, Region query, int from, int to, int level);
        std::vector<Point> actualSearch(Region query);
        void saveState(Region query);
        void loadState(std::string filename);
        int size() const { return 2*points.size(); }


    private:
        std::vector<Point> points;
        Region region;
        bool debug;
        std::vector<Point> results;
};




#endif
