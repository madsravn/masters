#ifndef ORTHOGONAL_RANGE_SEARCH_
#define ORTHOGONAL_RANGE_SEARCH_

#include <algorithm>
#include <random>
#include <vector>
#include <functional>
#include <cstdint>

struct Point {
    int x, y;
};

struct {
    bool operator()(Point a, Point b) {   
        return a.y < b.y;
    }   
} sortpointy;

struct {
    bool operator()(Point a, Point b) {
        return a.x < b.x;
    }
} sortpointx;

using uint = std::uint32_t;


class Ort {
    public:
        Ort(int amount);
        void divide(int level, int pos, std::vector<Point> points);


    private:
        std::vector<std::vector<uint>> levels;
        std::vector<uint> bits;



};

#endif
