#ifndef ORTHOGONAL_RANGE_SEARCH_
#define ORTHOGONAL_RANGE_SEARCH_

#include <algorithm>
#include <random>
#include <vector>
#include <functional>
#include <cstdint>
#include "Point.hpp"


enum DIRECTION { LEFT, RIGHT };

using uint = std::uint32_t;

struct Jumper {
    int jump; // 1, 2, 3, 4, 5 etc. Gets adjusted if we hit the bottom
    std::vector<int> ranks; // Det skal der være hver
    std::vector<int> entries;
    std::vector<int> targets;
    bool end; // True if bottom is hit
};

struct qreturn {
    int jump; // Do we jump? [0,1]
    int character; // Which character is chosen
    int rank; // What is the rank of this character at this position?
    int size; // How many levels do we jump? 
};


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
        Point buildfollowball(int level, int nodepos, int pos, int amount);
        Point whilefollowball(int level, int nodepos, int pos, int amount);
        void intMasks();
        void initializeStuff();
        void FindPoints(int leftchild, int rightchild, int ly_index, int uy_index, int bit, int nodepos, int amount, int level);
        void followPoint(int child, int lyrank, int uyrank, int bit, int nodepos, int amount, DIRECTION d, int level);
        void initializeBinarySearches();
        void addAll(int nodepos, int lrank, int urank, int level, int amount);
        std::vector<Point> easyQuery(Point lowerleft, Point upperright); 
        std::vector<Point> actualQuery(Point lowerleft, Point upperright);
        qreturn bigJump(int level, int pos);
        int convertRangeToInt(std::vector<int> vec, int start, int stop);
        void generateJumps();

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
        int current;
        std::vector<std::vector<int>> linkedlists;
        std::vector<std::vector<int>> twodarray;
        std::vector<Jumper> jumps;
        std::vector<Point> results;


};

#endif
