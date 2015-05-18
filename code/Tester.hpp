#ifndef TESTER_HPP_
#define TESTER_HPP_

#include "Ort.hpp"
#include "KDTree.hpp"
#include <string>
#include "Timer.hpp"
#include <tuple>
#include <fstream>

class Tester {
    public:
        Tester(int k);
        ~Tester();
        //TODO: LAV EN RANDOM FINDER - DEN TJEKKER TILFÆLDIGE SETTINGS OG SER OM ORT PERFORMER BEDRE
        //TODO: IMPLEMENTER CACHE STUFF FOR AT SE OM DET ER DET DER GIVER TILFÆLDIGE SHIT-RESULTATER
        
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

        void test_two_different_findints(std::string name);

        void how_much_faster_is_ort_vertical(std::string name);
        void how_much_faster_is_ort_horizontal(std::string name);


        void report_run_sqrtn(const std::vector<std::vector<int>>& timevector, const std::vector<std::vector<int>>& timevector2, const std::vector<std::vector<int>>& jump_vector, const std::vector<std::vector<int>>& max_jumps, const std::vector<std::vector<int>>& startlevels, const std::vector<std::vector<int>>& result_sizes, int k, std::ofstream& treeconf, std::string T1name, int interval);
        
        void report_run(const std::vector<std::vector<int>>& timevector, const std::vector<std::vector<int>>& timevector2, const std::vector<std::vector<int>>& jump_vector, const std::vector<std::vector<int>>& max_jumps, const std::vector<std::vector<int>>& startlevels, int k, std::ofstream& treeconf, std::string T1name, int interval);

        template<typename T>
        void how_much_faster_is_ort_sqrtn(std::string name, Ort& ort, KDTree& kdtree, std::vector<std::vector<int>>& timevector, std::vector<std::vector<int>>& timevector2, std::vector<std::vector<int>>& jump_vector, std::vector<std::vector<int>>& max_jumps, std::vector<std::vector<int>>& startlevels, std::vector<std::vector<int>>& result_size, int k);
        
        template<typename T>
        void how_much_faster_is_ort_horizontal(std::string name, Ort& ort, KDTree& kdtree, std::vector<std::vector<int>>& timevector, std::vector<std::vector<int>>& timevector2, std::vector<std::vector<int>>& jump_vector, std::vector<std::vector<int>>& max_jumps, std::vector<std::vector<int>>& startlevels, int k);
        template<typename T>
        void how_much_faster_is_ort_vertical(std::string name, Ort& ort, KDTree& kdtree, std::vector<std::vector<int>>& timevector, std::vector<std::vector<int>>& timevector2, std::vector<std::vector<int>>& jump_vector, std::vector<std::vector<int>>& max_jumps, std::vector<std::vector<int>>& startlevels, int k);

        template<typename T>
        void how_much_faster_is_ort_horizontal(std::string name, Ort& ort, KDTree& kdtree, std::vector<std::vector<int>>& timevector, std::vector<std::vector<int>>& timevector2, int k);
        template<typename T>
        void how_much_faster_is_ort_vertical(std::string name, Ort& ort, KDTree& kdtree, std::vector<std::vector<int>>& timevector, std::vector<std::vector<int>>& timevector2, int k);



        template<typename T>
        void how_much_faster_is_ort_horizontal_small(std::string name, Ort& ort, KDTree& kdtree, std::vector<std::vector<int>>& timevector, std::vector<std::vector<int>>& timevector2, std::vector<std::vector<int>>& jump_vector, std::vector<std::vector<int>>& max_jumps, std::vector<std::vector<int>>& startlevels, int k);
        template<typename T>
        void how_much_faster_is_ort_vertical_small(std::string name, Ort& ort, KDTree& kdtree, std::vector<std::vector<int>>& timevector, std::vector<std::vector<int>>& timevector2, std::vector<std::vector<int>>& jump_vector, std::vector<std::vector<int>>& max_jumps, std::vector<std::vector<int>>& startlevels, int k);




        void compare_vertical_slices_times_between_ort_and_kdtree(std::string name, Ort& ort, KDTree& kdtree, std::vector<int>& times, std::vector<int>& jumps_vector, std::vector<int>& max_jumps, int k);
        void compare_horizontal_slices_times_between_ort_and_kdtree(std::string name, Ort& ort, KDTree& kdtree, std::vector<int>& times, std::vector<int>& jumps_vector, std::vector<int>& max_jumps, int k);



        void compare_vertical_slices_times_between_ort_and_kdtree(std::string name);
        void compare_horizontal_slices_times_between_ort_and_kdtree(std::string name);

        void ten_vertical_slices_have_same_performance(std::string name);
        void ten_horizontal_slices_have_same_performance(std::string name);
        void ten_vertical_slices_kdtree(std::string name);
        void ten_horizontal_slices_kdtree(std::string name);

        std::tuple<Ort, KDTree> buildtrees(int n, int B = 2, int hybrid = 1);

        template<typename T>
        void report(const std::vector<T>& vec, std::string name, std::string timename);

        template<typename T>
        void report(const std::vector<T>& vec, std::string name, std::string timename, std::ofstream& writetome);
        template<typename T>
        void report2(const std::vector<std::vector<T>>& vec, std::string name, std::string timename);

        void run(int B, int hybrid);
        void run2();

    private:
        std::ofstream output;
        int size_of_trees;

};

#endif
