#ifndef ORTHOGONAL_RANGE_SEARCH_
#define ORTHOGONAL_RANGE_SEARCH_

#include <algorithm>
#include <random>
#include <vector>
#include <tuple>
#include <functional>
#include <cstdint>
#include "Point.hpp"


enum DIRECTION { LEFT, RIGHT };

using uint = std::uint32_t;


class Ort {
    public:
        Ort(int amount, std::vector<Point> input);
        void divide(int level, int pos, std::vector<Point> points);
        void setBit(int level, int pos, int value);
        void outputLevels();
        void intIntegerToBinary();
        uint rank(uint number);
        uint findRank(int level, int nodepos, int pos);
        uint makemask(uint range);
        Point followball(int level, int nodepos, int pos, int amount);
        void intMasks();
        void initializeStuff();
        std::vector<Point> FindPoints(int leftchild, int rightchild, int ly_index, int uy_index, int bit, int nodepos, int amount, int level);
        std::vector<Point> followPoint(int child, int lyrank, int uyrank, int bit, int nodepos, int amount, DIRECTION d, int level);
        void initializeBinarySearches();
        std::vector<Point> addAll(int nodepos, int lrank, int urank, int level, int amount);
        std::vector<Point> easyQuery(Point lowerleft, Point upperright); 
        std::vector<Point> actualQuery(Point lowerleft, Point upperright);
        std::tuple<bool, int, int> bigJump(int level, int pos);

    private:
        Point search;
        int count;
        std::vector<std::vector<uint>> levels;
        std::vector<uint> bits;
        std::vector<Point> balls;
        std::vector<std::vector<uint>> ranks;
        std::vector<uint> inttobin;
        // Goes from 0 -> 31. ranks will find the sum if it includes all 32 bits
        std::vector<uint> masks;
        std::vector<int> xb, yb;



};

#endif
