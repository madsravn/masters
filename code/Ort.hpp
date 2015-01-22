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
        void setBit(int level, int pos, int value);
        void outputLevels();
        void populateList();
        uint rank(uint number);
        uint findRank(int level, int nodepos, int pos);
        uint makemask(uint range);
        Point followball(int level, int nodepos, int pos, int amount);

    private:
        std::vector<std::vector<uint>> levels;
        std::vector<uint> bits;
        std::vector<Point> balls;
        std::vector<std::vector<uint>> ranks;
        std::vector<uint> inttobin;



};

#endif
