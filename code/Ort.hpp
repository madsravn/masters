#ifndef ORTHOGONAL_RANGE_SEARCH_
#define ORTHOGONAL_RANGE_SEARCH_

#include <algorithm>
#include <random>
#include <vector>
#include <functional>
#include <cstdint>
#include "Point.hpp"
#include "Data.hpp"


enum DIRECTION { LEFT, RIGHT };

using uint = std::uint32_t;
using ulon = unsigned long long;

struct Jumper {
    int jump; // 1, 2, 3, 4, 5 etc. Gets adjusted if we hit the bottom
    std::vector<uint> ranks; // Currently ununsed
    std::vector<uint> entries; // Which rank does it have?
    std::vector<uint> targets; // Where does it go? 
    bool end; // True if bottom is hit
};

struct LinearJumper {
    int jump;
    int majorkey;
    int minorkey;
    int entrieskey;
    int div;
    std::vector<uint> major; // Contains the major checkpoint
    std::vector<uint> minor;
    std::vector<uint> entries;
    bool end;
};

// This do not need to contain information about jumping to end.
struct qreturn {
    int jump; // Do we jump? [0,1]
    int character; // Which character is chosen
    int rank; // What is the rank of this character at this position?
    int size; // How many levels do we jump? 
};


class Ort {
    public:
        Ort(int amount, std::vector<Point> input, int _B = 2, bool _hybrid = false);
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
        std::vector<Point> easyQuery(Point lowerleft, Point upperright); //, int& jumpcount, int& maxdepth);
        std::vector<Point> actualQuery(Point lowerleft, Point upperright);
        qreturn bigJump(int level, int pos);
        int convertRangeToInt(std::vector<uint> vec, int start, int stop);
        void generateJumps();
        uint size(int t) const;
        std::vector<Point> search(Region reg, int& jumpcount, int& maxdepth);
        
        
        // TO FIND DEPTH
        void DepthFindPoints(int leftchild, int rightchild, int ly_index, int uy_index, int bit, int nodepos, int amount, int level);
        void DepthfollowPoint(int child, int lyrank, int uyrank, int bit, int nodepos, int amount, DIRECTION d, int level);

        void DepthaddAll(int nodepos, int lrank, int urank, int level, int amount);
        std::vector<Point> DeptheasyQuery(Point lowerleft, Point upperright, int& jumpcount, int& maxdepth, int& startlevel);
        std::vector<Point> Depthsearch(Region reg, int& jumpcount, int& maxdepth, int& startlevel);
        
        Point Depthwhilefollowball(int level, int nodepos, int pos, int amount);
        
        
        std::vector<Point> search(Region reg);
        std::vector<LinearJumper> getJumps() { return linear; }
        std::vector<int> createLinkedList(int size);

    private:
        // type: 1 for no big jumps, 2 for expensive big jumps and 3 for linear big jumps
        //int type;
        int B;
        bool hybrid;
        Point corner;
        int internaljumpcount;
        int internalmaxdepth;
        int internalstartlevel;
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
        std::vector<std::vector<uint>> linkedlists;
        std::vector<std::vector<uint>> twodarray;
        //std::vector<Jumper> jumps;
        //std::vector<LinearJumper> notsolinear;
        std::vector<LinearJumper> linear;
        //std::vector<LinearJumper> lineargarb;
        std::vector<Point> results;


};

#endif
