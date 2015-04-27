#ifndef DATA_HPP_
#define DATA_HPP_

#include <vector>
#include "Ort.hpp"
#include "Point.hpp"
#include <tuple>
#include <fstream>

class Data {

    public:
        static std::vector<Point> generate(int amount);
        static std::vector<Point> generateRandom(int amount, int start, int stop);
        static void saveState(std::vector<Point> points, Region region);
        static std::tuple<std::vector<Point>, Region> loadState(std::string filename);
        static std::vector<Point> randomPoints(std::mt19937 gen, int amount);
        static std::vector<uint> packBits(const std::vector<uint>& input, int size);
        static std::vector<uint> packBits2(const std::vector<uint>& input, int size);
        static uint findInt(const std::vector<uint>& input, int size, int pos);
        static uint findInt2(const std::vector<uint>& input, int size, int pos);
        static uint findInt3(const std::vector<uint>& input, int size, int pos);



};

#endif
