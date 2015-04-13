#ifndef TESTER_HPP_
#define TESTER_HPP_

#include "Ort.hpp"
#include "KDTree.hpp"
#include <string>
#include "Timer.hpp"
#include <tuple>

class Tester {
    public:
        Tester();
        //TODO: GIV DEM ORDENTLIGE NAVNE
        //TODO: LAV EN RANDOM FINDER - DEN TJEKKER TILFÆLDIGE SETTINGS OG SER OM ORT PERFORMER BEDRE
        //TODO: IMPLEMENTER CACHE STUFF FOR AT SE OM DET ER DET DER GIVER TILFÆLDIGE SHIT-RESULTATER
        void Test1(std::string name);
        void Test2(std::string name);
        void Test3(std::string name);
        void Test4(std::string name);
        void Test5(std::string name);
        void Test6(std::string name);
        void Test7(std::string name);
        void Test8(std::string name);
        void Test9(std::string name);
        void Test10(std::string name);
        std::tuple<Ort, KDTree> buildtrees(int n);
        void report(const std::vector<int>& vec, std::string name, std::string timename);

};

#endif
