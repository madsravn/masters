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

using uint = std::uint32_t;


class Ort {
    public:
        Ort(int amount);


    private:
        std::vector<std::vector<uint>> levels;



};

#endif
