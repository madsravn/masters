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
        //TODO: LAV EN RANDOM FINDER - DEN TJEKKER TILFÆLDIGE SETTINGS OG SER OM ORT PERFORMER BEDRE
        //TODO: IMPLEMENTER CACHE STUFF FOR AT SE OM DET ER DET DER GIVER TILFÆLDIGE SHIT-RESULTATER
        void Test1(std::string name);
        void slices_of_100_vertical_independent_of_n(std::string name);
        void slices_of_100_horizontal_independent_of_n(std::string name);
        //void slices_of_100_horizontal_on_kdtree(std::string name);
        //void slices_of_100_vertical_on_kdtree(std::string name);

        void cacheimportance(std::string name);
        void CACHE_only_create_ort_trees(std::string name);
        void CACHE_create_and_search_ort_type_three_different(std::string name);
        void CACHE_create_and_search_ort_type_three_same(std::string name);

        void CACHE_create_and_search_ort_type_four_different(std::string name);
        void CACHE_create_and_search_ort_type_four_same(std::string name);





        void compare_vertical_slices_times_between_ort_and_kdtree(std::string name);
        void compare_horizontal_slices_times_between_ort_and_kdtree(std::string name);
        void Test6(std::string name);
        void Test7(std::string name);
        void Test8(std::string name);
        void ten_vertical_slices_have_same_performance(std::string name);
        void ten_horizontal_slices_have_same_performance(std::string name);
        void ten_vertical_slices_kdtree(std::string name);
        void ten_horizontal_slices_kdtree(std::string name);
        std::tuple<Ort, KDTree> buildtrees(int n);
        void report(const std::vector<int>& vec, std::string name, std::string timename);
        void report2(const std::vector<std::vector<int>>& vec, std::string name, std::string timename);

};

#endif
