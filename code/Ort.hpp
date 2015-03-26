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
    int end;
};

struct qreturn {
    int jump; // Do we jump? [0,1]
    int character; // Which character is chosen
    int rank; // What is the rank of this character at this position?
    int size; // How many levels do we jump? 
    int end; // Do we reach the end?
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
        int convertRangeToInt(std::vector<uint> vec, int start, int stop);
        void generateJumps();
        uint size(int t) const;
        std::vector<Point> search(Region reg, int t);
        std::vector<LinearJumper> getJumps() { return linear; }
        std::vector<int> createLinkedList(int size);

    private:
        // type: 1 for no big jumps, 2 for expensive big jumps and 3 for linear big jumps
        int type;

        // Used to check if the left-most and right-most point are within the range
        Point corner;

        // Unused? 
        int count;

        // Contains the actual tree for ball-inheritance
        std::vector<std::vector<uint>> levels;

        // Used to get the x'th bit of a number, contains 100, 010, 001..
        std::vector<uint> bits;

        // Contains the balls/points
        std::vector<Point> balls;

        // Contains the accumulated sum of the ranks up to a given point.
        std::vector<std::vector<uint>> ranks;


        // Contains the 2^16 number mapping from int -> number of ones in binary
        std::vector<uint> inttobin;
        // Goes from 0 -> 31. ranks will find the sum if it includes all 32 bits
        std::vector<uint> masks;

        // In order to do binary search
        std::vector<int> xb, yb;

        // Being used to generate the big jumps
        int current;
        std::vector<std::vector<uint>> linkedlists;
        std::vector<std::vector<uint>> twodarray;

        // Three different kinds of big jumps
        std::vector<Jumper> jumps;
        std::vector<LinearJumper> notsolinear;
        std::vector<LinearJumper> linear;

        // The result set
        std::vector<Point> results;


};

#endif
