#include "Tester.hpp"
#include <chrono>
#include <functional>
#include <ratio>
#include <functional>

//using unitofmeassure = std::chrono::microseconds;
using unitofmeassure = std::chrono::nanoseconds;


template<typename T>
std::vector<T> numbers(std::vector<int> input, bool reverse = false) {
    std::vector<T> ret;
    if(reverse) {
        std::sort(std::begin(input), std::end(input), std::greater<T>());
    } else {
        std::sort(std::begin(input), std::end(input), std::less<T>());
    }

    ret.push_back(input.at(0)); // 0
    ret.push_back(input.at(0.05*(input.size()-1))); // 1
    ret.push_back(input.at(0.25*(input.size()-1))); // 2
    ret.push_back(input.at(0.5*(input.size()-1))); // 3
    ret.push_back(input.at(0.75*(input.size()-1))); // 4
    ret.push_back(input.at(0.95*(input.size()-1))); // 5
    ret.push_back(input.at(input.size()-1)); // 6

    float res = 0.0;
    for(const auto& e : input) {
        res += float(e)/input.size();
    }
    ret.push_back(res); // 7
    return ret;
}


template<typename T>
std::vector<std::vector<T>> numbers2(std::vector<std::vector<int>> vecs, bool reverse = false) {
    std::vector<std::vector<T>> rret;
    for(auto& input : vecs) {
        std::vector<T> ret;
        if(reverse) {
            std::sort(std::begin(input), std::end(input), std::greater<T>());
        } else {
            std::sort(std::begin(input), std::end(input), std::less<T>());
        }

        ret.push_back(input.at(0)); // 0
        ret.push_back(input.at(0.05*(input.size()-1))); // 1
        ret.push_back(input.at(0.25*(input.size()-1))); // 2
        ret.push_back(input.at(0.5*(input.size()-1))); // 3
        ret.push_back(input.at(0.75*(input.size()-1))); // 4
        ret.push_back(input.at(0.95*(input.size()-1))); // 5
        ret.push_back(input.at(input.size()-1)); // 6

        float res = 0.0;
        for(const auto& e : input) {
            res += float(e)/input.size();
        }
        ret.push_back(res); // 7
        rret.push_back(ret);
    }
    return rret;
}



Tester::Tester(int k) {

    size_of_trees = k;
    
    auto now = std::chrono::system_clock::now();
    std::random_device rd;
    std::mt19937 gen(rd());
    auto secs = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch());


    std::string filename = "tests4/" + std::to_string(secs.count());
    std::uniform_int_distribution<> dis(7652, 8761238);
    int random = dis(gen);
    filename += "_" + std::to_string(random);
    output.open(filename);
    std::cout << "Saving testing data to: " << filename << std::endl;
    
}

Tester::~Tester() {
    output.flush();
    output.close();

}

std::tuple<Ort, KDTree>
Tester::buildtrees(int n, int B, int hybrid) {
    int amount = pow(2,n);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::vector<Point> points = Data::generate(amount);

    Ort ort(amount, points, B, hybrid);
    KDTree kdtree(amount, points);

    return std::make_tuple(ort, kdtree);
}

//TODO: REWRITE DET HELE TIL MERE SIMPLE FUNKTIONER
//TODO: REWRITE SIZE OG A
//TODO: REWRITE TIL AT FINDE MELLEM A OG B HVOR ORT ER BEDRE END KD I STEDET FOR BARE OP TIL

template<typename T>
void
Tester::report(const std::vector<T>& vec, std::string name, std::string timename) {
    std::cout << std::endl << std::endl << "TESTING " << name << std::endl;
    std::cout << "Best = " << vec.at(0) << " " << timename << std::endl;
    std::cout << "5% percentile = " << vec.at(1) << " " << timename << std::endl;
    std::cout << "25% percentile = " << vec.at(2) << " " << timename << std::endl;
    std::cout << "50% percentile = " << vec.at(3) << " " << timename << std::endl;
    std::cout << "75% percentile = " << vec.at(4) << " " << timename << std::endl;
    std::cout << "95% percentile = " << vec.at(5) << " " << timename << std::endl;
    std::cout << "Worst = " << vec.at(6) << "  " << timename << std::endl;
    std::cout << "Average = " << vec.at(7) << " " << timename << std::endl;
    std::cout << "<=== === === === === === === === ===>" << std::endl;

    output << std::endl << std::endl << "TESTING " << name << std::endl;
    output << "Best = " << vec.at(0) << " " << timename << std::endl;
    output << "5% percentile = " << vec.at(1) << " " << timename << std::endl;
    output << "25% percentile = " << vec.at(2) << " " << timename << std::endl;
    output << "50% percentile = " << vec.at(3) << " " << timename << std::endl;
    output << "75% percentile = " << vec.at(4) << " " << timename << std::endl;
    output << "95% percentile = " << vec.at(5) << " " << timename << std::endl;
    output << "Worst = " << vec.at(6) << "  " << timename << std::endl;
    output << "Average = " << vec.at(7) << " " << timename << std::endl;
    output << "<=== === === === === === === === ===>" << std::endl;

}

template<typename T>
void
Tester::report(const std::vector<T>& vec, std::string name, std::string timename, std::ofstream& writetome) {
    std::cout << std::endl << std::endl << "TESTING " << name << std::endl;
    std::cout << "Best = " << vec.at(0) << " " << timename << std::endl;
    std::cout << "5% percentile = " << vec.at(1) << " " << timename << std::endl;
    std::cout << "25% percentile = " << vec.at(2) << " " << timename << std::endl;
    std::cout << "50% percentile = " << vec.at(3) << " " << timename << std::endl;
    std::cout << "75% percentile = " << vec.at(4) << " " << timename << std::endl;
    std::cout << "95% percentile = " << vec.at(5) << " " << timename << std::endl;
    std::cout << "Worst = " << vec.at(6) << "  " << timename << std::endl;
    std::cout << "Average = " << vec.at(7) << " " << timename << std::endl;
    std::cout << "<=== === === === === === === === ===>" << std::endl;

    writetome << std::endl << std::endl << "TESTING " << name << std::endl;
    writetome << "Best = " << vec.at(0) << " " << timename << std::endl;
    writetome << "5% percentile = " << vec.at(1) << " " << timename << std::endl;
    writetome << "25% percentile = " << vec.at(2) << " " << timename << std::endl;
    writetome << "50% percentile = " << vec.at(3) << " " << timename << std::endl;
    writetome << "75% percentile = " << vec.at(4) << " " << timename << std::endl;
    writetome << "95% percentile = " << vec.at(5) << " " << timename << std::endl;
    writetome << "Worst = " << vec.at(6) << "  " << timename << std::endl;
    writetome << "Average = " << vec.at(7) << " " << timename << std::endl;
    writetome << "<=== === === === === === === === ===>" << std::endl;

}



template<typename T>
void
Tester::report2(const std::vector<std::vector<T>>& vec, std::string name, std::string timename) {
    std::cout << std::endl << std::endl << "TESTING " << name << std::endl;
    output << std::endl << std::endl << "TESTING " << name << std::endl;
    std::cout << "< 5%, 50%, 95%, average >" << std::endl;
    output << "< 5%, 50%, 95%, average >" << std::endl;
    for(const auto& e : vec) {
        std::cout << "< " << e.at(1) << ", " << e.at(3) << ", " << e.at(5) << ", " << e.at(7) << " >" << std::endl;
        
        output << "< " << e.at(1) << ", " << e.at(3) << ", " << e.at(5) << ", " << e.at(7) << " >" << std::endl;
    }
}

void
Tester::run2() {

    Timer<std::chrono::seconds> t2;
    
    auto now = std::chrono::system_clock::now();
    std::random_device rd;
    std::mt19937 gen(rd());
    auto secs = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch());


    std::string filename = "tests4/kdtree_vs_ort_hori_nofuss_" + std::to_string(secs.count());
    std::uniform_int_distribution<> dis(7652, 8761238);
    int random = dis(gen);
    filename += "_" + std::to_string(random);
    std::ofstream kdtreeorthori(filename);

    filename = "tests4/kdtree_vs_ort_vert_nofuss_" + std::to_string(secs.count());
    filename += "_" + std::to_string(random);
    std::ofstream kdtreeortvert(filename);

 


    for(int k = 17; k < size_of_trees; ++k) {
        t2.reset();
        t2.start();
        int testSize = k;
        int amount = pow(2,testSize);
        int how_many = std::sqrt(amount)*1.5;
        int interval = 5;
        int jumps = how_many/interval;

        // TEST1
        std::vector<std::vector<int>> timevector(jumps, std::vector<int> {});
        std::vector<std::vector<int>> timevector2(jumps, std::vector<int> {});
        std::string T1name = "How much faster is Ort than KDTree horizontal";

        // TEST2
        std::vector<std::vector<int>> timevector_vert(jumps, std::vector<int> {});
        std::vector<std::vector<int>> timevector2_vert(jumps, std::vector<int> {});
        std::string T2name = "How much faster is Ort than KDTree vertical";


        for(int i = 0; i < 10; ++i) {
            std::tuple<Ort, KDTree> trees = buildtrees(testSize);
            Ort ort = std::get<0>(trees);
            KDTree kdtree = std::get<1>(trees);

            // TEST1 
            how_much_faster_is_ort_horizontal<unitofmeassure>(T1name, ort, kdtree, timevector, timevector2, k);

            // TEST2
            how_much_faster_is_ort_vertical<unitofmeassure>(T2name, ort, kdtree, timevector_vert, timevector2_vert, k);


        }

        
        
        // For TEST1
        for(int i = 0; i < timevector.size(); ++i) {
            Timer<unitofmeassure> t1;
            std::vector<int> rep = numbers<int>(timevector.at(i));
            report(rep, std::to_string(k) + " and " + std::to_string((i+1)*interval) + " = (ORT) " + T1name, t1.type(), kdtreeorthori);
            std::vector<int> rep2 = numbers<int>(timevector2.at(i));
            report(rep2, std::to_string(k) + " and " + std::to_string((i+1)*interval) + " = (KDTREE) " + T1name, t1.type(), kdtreeorthori);
        }

        // For TEST2
        for(int i = 0; i < timevector.size(); ++i) {
            Timer<unitofmeassure> t1;
            std::vector<int> rep = numbers<int>(timevector_vert.at(i));
            report(rep, std::to_string(k) + " and " + std::to_string((i+1)*interval) + " = (ORT) " + T2name, t1.type(), kdtreeortvert);
            std::vector<int> rep2 = numbers<int>(timevector2_vert.at(i));
            report(rep2, std::to_string(k) + " and " + std::to_string((i+1)*interval) + " = (KDTREE) " + T2name, t1.type(), kdtreeortvert);
        }


        t2.stop();
        kdtreeorthori.flush();

        kdtreeortvert.flush();

        std::cout << "Round " << k << " took " << t2.duration().count() << " seconds." << std::endl;
    }

    kdtreeorthori.close();
    kdtreeortvert.close();

}


void
Tester::report_run_sqrtn(const std::vector<std::vector<int>>& timevector, const std::vector<std::vector<int>>& timevector2, const std::vector<std::vector<int>>& jump_vector, const std::vector<std::vector<int>>& max_jumps, const std::vector<std::vector<int>>& startlevels, const std::vector<std::vector<int>>& result_sizes, int k, std::ofstream& treeconf, std::string T1name, int interval) {
    for(int i = 0; i < timevector.size(); ++i) {
        Timer<unitofmeassure> t1;

        std::vector<int> rep = numbers<int>(timevector.at(i));
        report(rep, std::to_string(k) + " and " + std::to_string((i+1)*interval) + " = (ORT) " + T1name, t1.type(), treeconf);


        std::vector<float> jumprep  = numbers<float>(jump_vector.at(i));
        report(jumprep, std::to_string(k) + " and " + std::to_string((i+1)*interval) + " = (JUMPS) " + T1name, "jumps", treeconf);
        std::cout << "That is " << float(jumprep.at(7))/(1+(i+1)*interval) << " jumps per result." << std::endl;

        treeconf << "That is " << float(jumprep.at(7))/(1+(i+1)*interval) << " jumps per result." << std::endl;



        std::vector<float> max_jumps_rep = numbers<float>(max_jumps.at(i));
        std::cout << "With a max jump of " << max_jumps_rep.at(6) << " and a average of " << max_jumps_rep.at(7) << std::endl;
        
        treeconf << "With a max jump of " << max_jumps_rep.at(6) << " and a average of " << max_jumps_rep.at(7) << std::endl;




        std::vector<float> startlevels_rep = numbers<float>(startlevels.at(i));

        std::cout << "startlevel max of " << startlevels_rep.at(6) << " and a average of " << startlevels_rep.at(7) << " and a minimum of " << startlevels_rep.at(0) << std::endl;

        treeconf << "startlevel max of " << startlevels_rep.at(6) << " and a average of " << startlevels_rep.at(7) << " and a minimum of " << startlevels_rep.at(0) << std::endl;
        
        
        std::vector<int> rep2 = numbers<int>(timevector2.at(i));
        report(rep2, std::to_string(k) + " and " + std::to_string((i+1)*interval) + " = (KDTREE) " + T1name, t1.type(), treeconf);

        std::vector<int> sizes = numbers<int>(result_sizes.at(i));
        std::cout << "Resultsize average of: " << sizes.at(7) << std::endl;

        treeconf << "Resultsize average of: " << sizes.at(7) << std::endl;
    }
}




void
Tester::report_run(const std::vector<std::vector<int>>& timevector, const std::vector<std::vector<int>>& timevector2, const std::vector<std::vector<int>>& jump_vector, const std::vector<std::vector<int>>& max_jumps, const std::vector<std::vector<int>>& startlevels, int k, std::ofstream& treeconf, std::string T1name, int interval) {
    for(int i = 0; i < timevector.size(); ++i) {
        Timer<unitofmeassure> t1;

        std::vector<int> rep = numbers<int>(timevector.at(i));
        report(rep, std::to_string(k) + " and " + std::to_string((i+1)*interval) + " = (ORT) " + T1name, t1.type(), treeconf);


        std::vector<float> jumprep  = numbers<float>(jump_vector.at(i));
        report(jumprep, std::to_string(k) + " and " + std::to_string((i+1)*interval) + " = (JUMPS) " + T1name, "jumps", treeconf);
        std::cout << "That is " << float(jumprep.at(7))/(1+(i+1)*interval) << " jumps per result." << std::endl;

        treeconf << "That is " << float(jumprep.at(7))/(1+(i+1)*interval) << " jumps per result." << std::endl;



        std::vector<float> max_jumps_rep = numbers<float>(max_jumps.at(i));
        std::cout << "With a max jump of " << max_jumps_rep.at(6) << " and a average of " << max_jumps_rep.at(7) << std::endl;
        
        treeconf << "With a max jump of " << max_jumps_rep.at(6) << " and a average of " << max_jumps_rep.at(7) << std::endl;




        std::vector<float> startlevels_rep = numbers<float>(startlevels.at(i));

        std::cout << "startlevel max of " << startlevels_rep.at(6) << " and a average of " << startlevels_rep.at(7) << " and a minimum of " << startlevels_rep.at(0) << std::endl;

        treeconf << "startlevel max of " << startlevels_rep.at(6) << " and a average of " << startlevels_rep.at(7) << " and a minimum of " << startlevels_rep.at(0) << std::endl;
        
        
        std::vector<int> rep2 = numbers<int>(timevector2.at(i));
        report(rep2, std::to_string(k) + " and " + std::to_string((i+1)*interval) + " = (KDTREE) " + T1name, t1.type(), treeconf);
    }
}


void
Tester::run(int B, int hybrid) {

    //TODO: 8 TESTS NATTEN OVER
    //B = {2,3}, hybrid = {true, false} og ekstra_information = {true, false}.
    //
    // Vi er interesserede i, at se om indsamling af ekstra information giver anledning til langsommere kørsel.
    // Det gør ikke noget hvis det er, de ekstra informationer skal bare hjælpe med at beskrive hvad der sker. 
    // Kørselstiden skal bare give gode resultater.


    Timer<std::chrono::seconds> t2;
    
    auto now = std::chrono::system_clock::now();
    std::random_device rd;
    std::mt19937 gen(rd());
    auto secs = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch());


    std::string filename = "tests4/kdtree_vs_ort_hori_" + std::to_string(B) + "_" + std::to_string(hybrid) + "_" + std::to_string(secs.count());
    std::uniform_int_distribution<> dis(7652, 8761238);
    int random = dis(gen);
    filename += "_" + std::to_string(random);
    std::ofstream kdtreeorthori(filename);

    filename = "tests4/kdtree_vs_ort_vert_" + std::to_string(B) + "_" + std::to_string(hybrid) + "_"+ std::to_string(secs.count());
    filename += "_" + std::to_string(random);
    std::ofstream kdtreeortvert(filename);

    /*filename = "tests4/compare_times_vert_" + std::to_string(B) + "_" + std::to_string(hybrid) + "_"+ std::to_string(secs.count());
    filename += "_" + std::to_string(random);
    std::ofstream compare_vert_stream(filename);

    filename = "tests4/compare_times_hori_" + std::to_string(B) + "_" + std::to_string(hybrid) + "_"+ std::to_string(secs.count());
    filename += "_" + std::to_string(random);
    std::ofstream compare_hori_stream(filename);
    */


    filename = "tests4/small_kdtree_vs_ort_vert_" + std::to_string(B) + "_" + std::to_string(hybrid) + "_" + std::to_string(secs.count());
    filename += "_" + std::to_string(random);
    std::ofstream smallkdtreeortvert(filename);

    filename = "tests4/small_kdtree_vs_ort_hori_" + std::to_string(B) + "_" + std::to_string(hybrid) + "_" + std::to_string(secs.count());
    filename += "_" + std::to_string(random);
    std::ofstream smallkdtreeorthori(filename);

     filename = "tests4/small_kdtree_vs_ort_sqrt_" + std::to_string(B) + "_" + std::to_string(hybrid) + "_" + std::to_string(secs.count());
    filename += "_" + std::to_string(random);
    std::ofstream kdtreeortsqrtn(filename);




 


    for(int k = 17; k < size_of_trees; ++k) {
        t2.reset();
        t2.start();
        int testSize = k;
        int amount = pow(2,testSize);
        int how_many = std::sqrt(amount)*1.5;
        int how_many_sqrtn = std::sqrt(amount)*0.5;
        int interval_sqrtn = 5;
        int sqrtn_jumps = how_many_sqrtn/interval_sqrtn;
        int interval = 5;
        int jumps = how_many/interval;
        int smalljumps = 200;

        // TEST1
        std::vector<std::vector<int>> timevector(jumps, std::vector<int> {});
        std::vector<std::vector<int>> timevector2(jumps, std::vector<int> {});
        std::vector<std::vector<int>> jumps_hori(jumps, std::vector<int> {});
        std::vector<std::vector<int>> max_jumps_hori(jumps, std::vector<int> {});
        std::vector<std::vector<int>> startlevels_hori(jumps, std::vector<int> {});
        std::string T1name = "How much faster is Ort than KDTree horizontal";

        // TEST2
        std::vector<std::vector<int>> timevector_vert(jumps, std::vector<int> {});
        std::vector<std::vector<int>> timevector2_vert(jumps, std::vector<int> {});
        std::vector<std::vector<int>> jumps_vert(jumps, std::vector<int> {});
        std::vector<std::vector<int>> max_jumps_vert(jumps, std::vector<int> {});
        std::vector<std::vector<int>> startlevels_vert(jumps, std::vector<int> {});
        std::string T2name = "How much faster is Ort than KDTree vertical";

        // TEST3
        std::vector<int> times_compare_vert;
        std::vector<int> jumps_compare_vert;
        std::vector<int> max_jumps_compare_vert;
        std::string T3name = "When is KDTree just as fast as Ort vertical";

        // TEST4
        std::vector<int> times_compare_hori;
        std::vector<int> jumps_compare_hori;
        std::vector<int> max_jumps_compare_hori;
        std::string T4name = "When is KDTree just as fast as Ort horizontal";

        // TEST5
        std::vector<std::vector<int>> smalltimevector(smalljumps, std::vector<int> {});
        std::vector<std::vector<int>> smalltimevector2(smalljumps, std::vector<int> {});
        std::vector<std::vector<int>> smalljumps_hori(smalljumps, std::vector<int> {});
        std::vector<std::vector<int>> smallmax_jumps_hori(smalljumps, std::vector<int> {});
        std::vector<std::vector<int>> smallstartlevels_hori(smalljumps, std::vector<int> {});
        std::string T5name = "How much faster is Ort than KDTree horizontal small";

        // TEST6
        std::vector<std::vector<int>> smalltimevector_vert(smalljumps, std::vector<int> {});
        std::vector<std::vector<int>> smalltimevector2_vert(smalljumps, std::vector<int> {});
        std::vector<std::vector<int>> smalljumps_vert(smalljumps, std::vector<int> {});
        std::vector<std::vector<int>> smallmax_jumps_vert(smalljumps, std::vector<int> {});
        std::vector<std::vector<int>> smallstartlevels_vert(smalljumps, std::vector<int> {});
        std::string T6name = "How much faster is Ort than KDTree vertical small";


        // TEST7
        std::vector<std::vector<int>> timevector_sqrtn(sqrtn_jumps, std::vector<int> {});
        std::vector<std::vector<int>> timevector2_sqrtn(sqrtn_jumps, std::vector<int> {});
        std::vector<std::vector<int>> jumps_sqrtn(sqrtn_jumps, std::vector<int> {});
        std::vector<std::vector<int>> max_jumps_sqrtn(sqrtn_jumps, std::vector<int> {});
        std::vector<std::vector<int>> startlevels_sqrtn(sqrtn_jumps, std::vector<int> {});
        std::vector<std::vector<int>> result_size_sqrtn(sqrtn_jumps, std::vector<int> {});
        std::string T7name = "How much faster is Ort than KDTree sqrtn";

        // TEST8
        std::vector<float> kdsizes, ortsizes;




        for(int i = 0; i < 10; ++i) {
            std::tuple<Ort, KDTree> trees = buildtrees(testSize, B, hybrid);
            Ort ort = std::get<0>(trees);
            KDTree kdtree = std::get<1>(trees);

            // TEST1 
            //how_much_faster_is_ort_horizontal<unitofmeassure>(T1name, ort, kdtree, timevector, timevector2, jumps_hori, max_jumps_hori, startlevels_hori, k);

            // TEST2
            //how_much_faster_is_ort_vertical<unitofmeassure>(T2name, ort, kdtree, timevector_vert, timevector2_vert, jumps_vert, max_jumps_vert, startlevels_vert, k);

            // TEST5 
            //how_much_faster_is_ort_horizontal_small<unitofmeassure>(T5name, ort, kdtree, smalltimevector, smalltimevector2, smalljumps_hori, smallmax_jumps_hori, smallstartlevels_hori, k);

            // TEST6
            //how_much_faster_is_ort_vertical_small<unitofmeassure>(T6name, ort, kdtree, smalltimevector_vert, smalltimevector2_vert, smalljumps_vert, smallmax_jumps_vert, smallstartlevels_vert, k);


            // TEST7
            //how_much_faster_is_ort_sqrtn<unitofmeassure>(T7name, ort, kdtree, timevector_sqrtn, timevector2_sqrtn, jumps_sqrtn, max_jumps_sqrtn, startlevels_sqrtn, result_size_sqrtn, k);

            kdsizes.push_back(float(kdtree.size())/amount);
            ortsizes.push_back(float(ort.size(3))/amount);



        }

        report(kdsizes, "KDTREE B = " + std::to_string(B) + std::to_string(testSize), "32 bits");
        report(ortsizes, "ORT  = " + std::to_string(B) + std::to_string(testSize), "32 bits");

        /*report_run(timevector, timevector2, jumps_hori, max_jumps_hori, startlevels_hori, k, kdtreeorthori, T1name, interval);

        report_run(timevector_vert, timevector2_vert, jumps_vert, max_jumps_vert, startlevels_vert, k, kdtreeortvert, T2name, interval);


        report_run(smalltimevector, smalltimevector2, smalljumps_hori, smallmax_jumps_hori, smallstartlevels_hori, k, smallkdtreeorthori, T5name, 1);


        report_run(smalltimevector_vert, smalltimevector2_vert, smalljumps_vert, smallmax_jumps_vert, smallstartlevels_vert, k, smallkdtreeortvert, T6name, 1);*/
        
        
        //report_run_sqrtn(timevector_sqrtn, timevector2_sqrtn, jumps_sqrtn, max_jumps_sqrtn, startlevels_sqrtn, result_size_sqrtn, k, kdtreeortsqrtn, T7name, interval_sqrtn);
        /*
        // For TEST1
        for(int i = 0; i < timevector.size(); ++i) {
            Timer<unitofmeassure> t1;
            std::vector<int> rep = numbers<int>(timevector.at(i));
            report(rep, std::to_string(k) + " and " + std::to_string((i+1)*interval) + " = (ORT) " + T1name, t1.type(), kdtreeorthori);
            std::vector<float> jumprep  = numbers<float>(jumps_hori.at(i));
            report(jumprep, std::to_string(k) + " and " + std::to_string((i+1)*interval) + " = (JUMPS) " + T1name, "jumps", kdtreeorthori);
            std::cout << "That is " << float(jumprep.at(7))/(1+(i+1)*interval) << " jumps per result." << std::endl;

            kdtreeorthori << "That is " << float(jumprep.at(7))/(1+(i+1)*interval) << " jumps per result." << std::endl;
            std::vector<float> max_jumps_rep = numbers<float>(max_jumps_hori.at(i));
            std::cout << "With a max jump of " << max_jumps_rep.at(6) << " and a average of " << max_jumps_rep.at(7) << std::endl;
            
            kdtreeorthori << "With a max jump of " << max_jumps_rep.at(6) << " and a average of " << max_jumps_rep.at(7) << std::endl;

            std::vector<float> startlevels_rep = numbers<float>(startlevels_hori.at(i));
            std::cout << "startlevel max of " << startlevels_rep.at(6) << " and a average of " << startlevels_rep.at(7) << " and a minimum of " << startlevels_rep.at(0) << std::endl;

            kdtreeorthori << "startlevel max of " << startlevels_rep.at(6) << " and a average of " << startlevels_rep.at(7) << " and a minimum of " << startlevels_rep.at(0) << std::endl;
            
            
            std::vector<int> rep2 = numbers<int>(timevector2.at(i));
            report(rep2, std::to_string(k) + " and " + std::to_string((i+1)*interval) + " = (KDTREE) " + T1name, t1.type(), kdtreeorthori);
        }

        // For TEST2
        for(int i = 0; i < timevector.size(); ++i) {
            Timer<unitofmeassure> t1;
            std::vector<int> rep = numbers<int>(timevector_vert.at(i));
            report(rep, std::to_string(k) + " and " + std::to_string((i+1)*interval) + " = (ORT) " + T2name, t1.type(), kdtreeortvert);
            std::vector<float> jumprep  = numbers<float>(jumps_vert.at(i));
            report(jumprep, std::to_string(k) + " and " + std::to_string((i+1)*interval) + " = (JUMPS) " + T2name, "jumps", kdtreeortvert);
            std::cout << "That is " << float(jumprep.at(7))/(1+(i+1)*interval) << " jumps per result." << std::endl;
            kdtreeortvert << "That is " << float(jumprep.at(7))/(1+(i+1)*interval) << " jumps per result." << std::endl;

            std::vector<float> max_jumps_rep = numbers<float>(max_jumps_vert.at(i));
            std::cout << "With a max jump of " << max_jumps_rep.at(6) << " and a average of " << max_jumps_rep.at(7) << std::endl;
            
            kdtreeortvert << "With a max jump of " << max_jumps_rep.at(6) << " and a average of " << max_jumps_rep.at(7) << std::endl;

            std::vector<float> startlevels_rep = numbers<float>(startlevels_vert.at(i));
            std::cout << "startlevel max of " << startlevels_rep.at(6) << " and a average of " << startlevels_rep.at(7) << " and a minimum of " << startlevels_rep.at(0) << std::endl;

            kdtreeortvert << "startlevel max of " << startlevels_rep.at(6) << " and a average of " << startlevels_rep.at(7) << " and a minimum of " << startlevels_rep.at(0) << std::endl;

            
            std::vector<int> rep2 = numbers<int>(timevector2_vert.at(i));
            report(rep2, std::to_string(k) + " and " + std::to_string((i+1)*interval) + " = (KDTREE) " + T2name, t1.type(), kdtreeortvert);
        }
        {
            std::vector<int> rep = numbers<int>(times_compare_vert, true);
            report(rep, std::to_string(k) + " = " + T3name, "times", compare_vert_stream);

            std::vector<int> jumprep = numbers<int>(jumps_compare_vert);
            report(jumprep, std::to_string(k) + " (JUMPS) " + T3name, "jumps", compare_vert_stream);
            std::cout << "That is " << float(jumprep.at(7))/rep.at(7) << " jumps per result." << std::endl;
            compare_vert_stream << "That is " << float(jumprep.at(7))/rep.at(7) << " jumps per result." << std::endl;
            std::vector<int> max_jumps_rep = numbers<int>(max_jumps_compare_vert);
            std::cout << "With a max jump of " << max_jumps_rep.at(6) << " and an average of " << max_jumps_rep.at(7) << std::endl;

            compare_vert_stream << "With a max jump of " << max_jumps_rep.at(6) << " and an average of " << max_jumps_rep.at(7) << std::endl;
        }

        {
            std::vector<int> rep = numbers<int>(times_compare_hori, true);
            report(rep, std::to_string(k) + " = " + T4name, "times", compare_hori_stream);

            std::vector<int> jumprep = numbers<int>(jumps_compare_hori);
            report(jumprep, std::to_string(k) + " (JUMPS) " + T3name, "jumps", compare_hori_stream);
            std::cout << "That is " << float(jumprep.at(7))/rep.at(7) << " jumps per result." << std::endl;
            compare_hori_stream << "That is " << float(jumprep.at(7))/rep.at(7) << " jumps per result." << std::endl;
            std::vector<int> max_jumps_rep = numbers<int>(max_jumps_compare_hori);
            std::cout << "With a max jump of " << max_jumps_rep.at(6) << " and an average of " << max_jumps_rep.at(7) << std::endl;

            compare_hori_stream << "With a max jump of " << max_jumps_rep.at(6) << " and an average of " << max_jumps_rep.at(7) << std::endl;


        }

        // For TEST5
        for(int i = 0; i < smalltimevector.size(); ++i) {
            Timer<unitofmeassure> t1;
            std::vector<int> rep = numbers<int>(smalltimevector.at(i));
            report(rep, std::to_string(k) + " and " + std::to_string((i+1)) + " = (ORT) " + T5name, t1.type(), smallkdtreeorthori);
            std::vector<int> jumprep  = numbers<int>(smalljumps_hori.at(i));
            report(jumprep, std::to_string(k) + " and " + std::to_string((i+1)) + " = (JUMPS) " + T5name, "jumps", smallkdtreeorthori);
            std::cout << "That is " << float(jumprep.at(7))/(1+(i+1)) << " jumps per result." << std::endl;
            smallkdtreeorthori << "That is " << float(jumprep.at(7))/(1+(i+1)) << " jumps per result." << std::endl;

            std::vector<int> max_jumps_rep = numbers<int>(smallmax_jumps_hori.at(i));
            std::cout << "With a max jump of " << max_jumps_rep.at(6) << " and a average of " << max_jumps_rep.at(7) << std::endl;
            
            smallkdtreeorthori << "With a max jump of " << max_jumps_rep.at(6) << " and a average of " << max_jumps_rep.at(7) << std::endl;

            std::vector<int> startlevels_rep = numbers<int>(smallstartlevels_hori.at(i));
            std::cout << "startlevel max of " << startlevels_rep.at(6) << " and a average of " << startlevels_rep.at(7) << std::endl;

            smallkdtreeorthori << "startlevel max of " << startlevels_rep.at(6) << " and a average of " << startlevels_rep.at(7) << std::endl;
            

            
            std::vector<int> rep2 = numbers<int>(smalltimevector2.at(i));
            report(rep2, std::to_string(k) + " and " + std::to_string((i+1)) + " = (KDTREE) " + T5name, t1.type(), smallkdtreeorthori);
        }

        // For TEST6
        for(int i = 0; i < smalltimevector.size(); ++i) {
            Timer<unitofmeassure> t1;
            std::vector<int> rep = numbers<int>(smalltimevector_vert.at(i));
            report(rep, std::to_string(k) + " and " + std::to_string((i+1)) + " = (ORT) " + T6name, t1.type(), smallkdtreeortvert);
            std::vector<int> jumprep  = numbers<int>(smalljumps_vert.at(i));
            report(jumprep, std::to_string(k) + " and " + std::to_string((i+1)) + " = (JUMPS) " + T6name, "jumps", smallkdtreeortvert);
            std::cout << "That is " << float(jumprep.at(7))/(1+(i+1)) << " jumps per result." << std::endl;
            smallkdtreeortvert << "That is " << float(jumprep.at(7))/(1+(i+1)) << " jumps per result." << std::endl;

            std::vector<int> max_jumps_rep = numbers<int>(smallmax_jumps_vert.at(i));
            std::cout << "With a max jump of " << max_jumps_rep.at(6) << " and a average of " << max_jumps_rep.at(7) << std::endl;
            
            smallkdtreeortvert << "With a max jump of " << max_jumps_rep.at(6) << " and a average of " << max_jumps_rep.at(7) << std::endl;

            std::vector<int> startlevels_rep = numbers<int>(smallstartlevels_vert.at(i));
            std::cout << "startlevel max of " << startlevels_rep.at(6) << " and a average of " << startlevels_rep.at(7) << std::endl;

            smallkdtreeortvert << "startlevel max of " << startlevels_rep.at(6) << " and a average of " << startlevels_rep.at(7) << std::endl;
            
            std::vector<int> rep2 = numbers<int>(smalltimevector2_vert.at(i));
            report(rep2, std::to_string(k) + " and " + std::to_string((i+1)) + " = (KDTREE) " + T6name, t1.type(), smallkdtreeortvert);
        }
        */


        t2.stop();
        kdtreeorthori.flush();
        smallkdtreeorthori.flush();

        kdtreeortvert.flush();
        smallkdtreeortvert.flush();
        kdtreeortsqrtn.flush();

        //compare_hori_stream.flush();
        //compare_vert_stream.flush();
        std::cout << "Round " << k << " took " << t2.duration().count() << " seconds." << std::endl;
    }

    kdtreeorthori.close();
    kdtreeortvert.close();

    kdtreeortsqrtn.close();
    smallkdtreeorthori.close();
    smallkdtreeortvert.close();


    //compare_hori_stream.close();
    //compare_hori_stream.close();

}


template<typename T>
void
Tester::how_much_faster_is_ort_vertical_small(std::string name, Ort& ort, KDTree& kdtree, std::vector<std::vector<int>>& timevector, std::vector<std::vector<int>>& timevector2, std::vector<std::vector<int>>& jump_vector, std::vector<std::vector<int>>& max_jumps, std::vector<std::vector<int>>& startlevels,  int k) {
    
    
    int testSize = k;
    int amount = pow(2,testSize);
    int how_many = 200;
    int interval = 1;
    int jumps = how_many/interval;
    int jumpcount = 0;
    int max_jump = 0;
    int startlevel = 0;



    Timer<T> t1;
    for(int size = 1; size < timevector.size()+1; ++size) {
        for(int h = 0; h < 10; ++h) {
            for(int j = 0; j < 100; ++j) {
                jumpcount = 0;
                max_jump = 0;
                startlevel = 0;
                Region reg {{(amount/100)*j, 0},{(amount/100)*j + size*interval, amount}};
                //std::cout << reg << std::endl;
                //std::cout << size*interval << std::endl << std::endl;
                
                t1.reset();
                t1.start();
                ort.search(reg);
                t1.stop();

                ort.Depthsearch(reg, jumpcount, max_jump, startlevel);

                timevector.at(size-1).push_back(t1.duration().count());
                jump_vector.at(size-1).push_back(jumpcount);
                max_jumps.at(size-1).push_back(max_jump);
                startlevels.at(size-1).push_back(startlevel);



                t1.reset();
                t1.start();
                kdtree.search(reg);
                t1.stop();

                timevector2.at(size-1).push_back(t1.duration().count());
                
            }
        }
    }
}




template<typename T>
void
Tester::how_much_faster_is_ort_horizontal_small(std::string name, Ort& ort, KDTree& kdtree, std::vector<std::vector<int>>& timevector, std::vector<std::vector<int>>& timevector2, std::vector<std::vector<int>>& jump_vector, std::vector<std::vector<int>>& max_jumps, std::vector<std::vector<int>>& startlevels, int k) {
    
    
    int testSize = k;
    int amount = pow(2,testSize);
    int how_many = 200;
    int interval = 1;
    int jumps = how_many/interval;
    int jumpcount = 0;
    int max_jump = 0;
    int startlevel = 0;



    Timer<T> t1;
    for(int size = 1; size < timevector.size()+1; ++size) {
        for(int h = 0; h < 10; ++h) {
            for(int j = 0; j < 100; ++j) {
                jumpcount = 0;
                max_jump = 0;
                startlevel = 0;
                Region reg {{0, (amount/100)*j},{amount, (amount/100)*j + size*interval}};
                
                t1.reset();
                t1.start();
                ort.search(reg);
                t1.stop();

                ort.Depthsearch(reg, jumpcount, max_jump, startlevel);
                timevector.at(size-1).push_back(t1.duration().count());
                startlevels.at(size-1).push_back(startlevel);
                jump_vector.at(size-1).push_back(jumpcount);
                max_jumps.at(size-1).push_back(max_jump);



                t1.reset();
                t1.start();
                kdtree.search(reg);
                t1.stop();

                timevector2.at(size-1).push_back(t1.duration().count());
                
            }
        }
    }
}

template<typename T>
void
Tester::how_much_faster_is_ort_vertical(std::string name, Ort& ort, KDTree& kdtree, std::vector<std::vector<int>>& timevector, std::vector<std::vector<int>>& timevector2, int k) {
    
    
    int testSize = k;
    int amount = pow(2,testSize);
    int how_many = std::sqrt(amount)*1.5;
    int interval = 5;
    int jumps = how_many/interval;



    Timer<T> t1;
    for(int size = 1; size < timevector.size()+1; ++size) {
        for(int h = 0; h < 10; ++h) {
            for(int j = 0; j < 100; ++j) {
                Region reg {{(amount/100)*j, 0},{(amount/100)*j + size*interval, amount}};
                
                t1.reset();
                t1.start();
                ort.search(reg);
                t1.stop();


                timevector.at(size-1).push_back(t1.duration().count());


                t1.reset();
                t1.start();
                kdtree.search(reg);
                t1.stop();

                timevector2.at(size-1).push_back(t1.duration().count());
                
            }
        }
    }
}




template<typename T>
void
Tester::how_much_faster_is_ort_horizontal(std::string name, Ort& ort, KDTree& kdtree, std::vector<std::vector<int>>& timevector, std::vector<std::vector<int>>& timevector2, int k) {
    
    
    int testSize = k;
    int amount = pow(2,testSize);
    int how_many = std::sqrt(amount)*1.5;
    int interval = 5;
    int jumps = how_many/interval;



    Timer<T> t1;
    for(int size = 1; size < timevector.size()+1; ++size) {
        for(int h = 0; h < 10; ++h) {
            for(int j = 0; j < 100; ++j) {
                Region reg {{0, (amount/100)*j},{amount, (amount/100)*j + size*interval}};
                
                t1.reset();
                t1.start();
                ort.search(reg);
                t1.stop();

                timevector.at(size-1).push_back(t1.duration().count());

                t1.reset();
                t1.start();
                kdtree.search(reg);
                t1.stop();

                timevector2.at(size-1).push_back(t1.duration().count());
                
            }
        }
    }
}





template<typename T>
void
Tester::how_much_faster_is_ort_vertical(std::string name, Ort& ort, KDTree& kdtree, std::vector<std::vector<int>>& timevector, std::vector<std::vector<int>>& timevector2, std::vector<std::vector<int>>& jump_vector, std::vector<std::vector<int>>& max_jumps, std::vector<std::vector<int>>& startlevels,  int k) {
    
    
    int testSize = k;
    int amount = pow(2,testSize);
    int how_many = std::sqrt(amount)*1.5;
    int interval = 5;
    int jumps = how_many/interval;
    int jumpcount = 0;
    int max_jump = 0;
    int startlevel = 0;



    Timer<T> t1;
    for(int size = 1; size < timevector.size()+1; ++size) {
        for(int h = 0; h < 10; ++h) {
            for(int j = 0; j < 100; ++j) {
                jumpcount = 0;
                max_jump = 0;
                startlevel = 0;
                Region reg {{(amount/100)*j, 0},{(amount/100)*j + size*interval, amount}};
                
                t1.reset();
                t1.start();
                ort.search(reg);
                t1.stop();

                ort.Depthsearch(reg, jumpcount, max_jump, startlevel);

                timevector.at(size-1).push_back(t1.duration().count());
                jump_vector.at(size-1).push_back(jumpcount);
                max_jumps.at(size-1).push_back(max_jump);
                startlevels.at(size-1).push_back(startlevel);



                t1.reset();
                t1.start();
                kdtree.search(reg);
                t1.stop();

                timevector2.at(size-1).push_back(t1.duration().count());
                
            }
        }
    }
}

template<typename T>
void
Tester::how_much_faster_is_ort_sqrtn(std::string name, Ort& ort, KDTree& kdtree, std::vector<std::vector<int>>& timevector, std::vector<std::vector<int>>& timevector2, std::vector<std::vector<int>>& jump_vector, std::vector<std::vector<int>>& max_jumps, std::vector<std::vector<int>>& startlevels, std::vector<std::vector<int>>& result_size, int k) {
    
    
    int testSize = k;
    int amount = pow(2,testSize);
    int how_many = std::sqrt(amount)*0.5;
    int interval = 5;
    int jumps = how_many/interval;
    int jumpcount = 0;
    int max_jump = 0;
    int startlevel = 0;
    int results = 0;
    std::random_device rd;
    std::mt19937 gen(rd());



    Timer<T> t1;
    for(int size = 1; size < timevector.size()+1; ++size) {


        int area = std::sqrt(amount)*std::sqrt(size*interval);
        std::uniform_int_distribution<> dis(0, amount-1-area);
        for(int h = 0; h < 10; ++h) {
            for(int j = 0; j < 100; ++j) {
                jumpcount = 0;
                max_jump = 0;
                startlevel = 0;
                int xdisplacement = dis(gen);
                int ydisplacement = dis(gen);
                Region reg {{xdisplacement, ydisplacement}, {xdisplacement+area, ydisplacement+area}};
                
                t1.reset();
                t1.start();
                ort.search(reg);
                t1.stop();
                results = ort.search(reg).size();

                ort.Depthsearch(reg, jumpcount, max_jump, startlevel);
                timevector.at(size-1).push_back(t1.duration().count());
                startlevels.at(size-1).push_back(startlevel);
                jump_vector.at(size-1).push_back(jumpcount);
                max_jumps.at(size-1).push_back(max_jump);
                result_size.at(size-1).push_back(results);



                t1.reset();
                t1.start();
                kdtree.search(reg);
                t1.stop();

                timevector2.at(size-1).push_back(t1.duration().count());
                
            }
        }
    }
}




template<typename T>
void
Tester::how_much_faster_is_ort_horizontal(std::string name, Ort& ort, KDTree& kdtree, std::vector<std::vector<int>>& timevector, std::vector<std::vector<int>>& timevector2, std::vector<std::vector<int>>& jump_vector, std::vector<std::vector<int>>& max_jumps, std::vector<std::vector<int>>& startlevels, int k) {
    
    
    int testSize = k;
    int amount = pow(2,testSize);
    int how_many = std::sqrt(amount)*1.5;
    int interval = 5;
    int jumps = how_many/interval;
    int jumpcount = 0;
    int max_jump = 0;
    int startlevel = 0;



    Timer<T> t1;
    for(int size = 1; size < timevector.size()+1; ++size) {
        for(int h = 0; h < 10; ++h) {
            for(int j = 0; j < 100; ++j) {
                jumpcount = 0;
                max_jump = 0;
                startlevel = 0;
                Region reg {{0, (amount/100)*j},{amount, (amount/100)*j + size*interval}};
                
                t1.reset();
                t1.start();
                ort.search(reg);
                t1.stop();

                ort.Depthsearch(reg, jumpcount, max_jump, startlevel);
                timevector.at(size-1).push_back(t1.duration().count());
                startlevels.at(size-1).push_back(startlevel);
                jump_vector.at(size-1).push_back(jumpcount);
                max_jumps.at(size-1).push_back(max_jump);



                t1.reset();
                t1.start();
                kdtree.search(reg);
                t1.stop();

                timevector2.at(size-1).push_back(t1.duration().count());
                
            }
        }
    }
}


void
Tester::how_much_faster_is_ort_horizontal(std::string name) {
    for(int k = 17; k < size_of_trees; ++k) {
        int testSize = k;
        Timer<unitofmeassure> t1;
        int amount = pow(2,testSize);
        int how_many = std::sqrt(amount)*1.5;
        int interval = 5;
        int jumps = how_many/interval;
        int jumpcount = 0;
        int max_jump = 0;
        int startlevel = 0;
        std::vector<std::vector<int>> jump_vector(jumps, std::vector<int> {});
        std::vector<std::vector<int>> max_jumps(jumps, std::vector<int> {});
        std::vector<std::vector<int>> startlevels(jumps, std::vector<int> {});
        std::vector<std::vector<int>> timevector(jumps, std::vector<int> {});
        std::vector<std::vector<int>> timevector2(jumps, std::vector<int> {});
        for(int i = 0; i < 10; ++i) {
            std::tuple<Ort, KDTree> trees = buildtrees(testSize);
            Ort ort = std::get<0>(trees);
            KDTree kdtree = std::get<1>(trees);
            for(int size = 1; size < jumps+1; ++size) {
                for(int h = 0; h < 10; ++h) {
                    for(int j = 0; j < 100; ++j) {
                        Region reg {{0, (amount/100)*j},{amount, (amount/100)*j + size*interval}};
                        jumpcount = 0;
                        max_jump = 0 ;
                        startlevel = 0;
                        t1.reset();
                        t1.start();
                        ort.search(reg);
                        t1.stop();

                        ort.Depthsearch(reg, jumpcount, max_jump, startlevel);

                        jump_vector.at(size-1).push_back(jumpcount);
                        max_jumps.at(size-1).push_back(max_jump);
                        startlevels.at(size-1).push_back(startlevel);

                        timevector.at(size-1).push_back(t1.duration().count());

                        t1.reset();
                        t1.start();
                        kdtree.search(reg);
                        t1.stop();

                        timevector2.at(size-1).push_back(t1.duration().count());
                        
                    }
                }
            }
        }
        for(int i = 0; i < timevector.size(); ++i) {
            std::vector<int> rep = numbers<int>(timevector.at(i));
            report(rep, std::to_string(k) + " and " + std::to_string((i+1)*interval) + " = (ORT) " + name, t1.type());
            
            
            std::vector<int> jumprep  = numbers<int>(jump_vector.at(i));
            report(jumprep, std::to_string(k) + " and " + std::to_string((i+1)*interval) + " = (JUMPS) " + name, "jumps");

            std::cout << "That is " << float(jumprep.at(7))/(1+(i+1)*interval) << " jumps per result." << std::endl;
            output << "That is " << float(jumprep.at(7))/(1+(i+1)*interval) << " jumps per result." << std::endl;

            std::vector<int> max_jumps_rep = numbers<int>(max_jumps.at(i));
            std::cout << "With a max jump of " << max_jumps_rep.at(6) << " and a average of " << max_jumps_rep.at(7) << std::endl;
            
            output << "With a max jump of " << max_jumps_rep.at(6) << " and a average of " << max_jumps_rep.at(7) << std::endl;
            


            std::vector<int> rep2 = numbers<int>(timevector2.at(i));
            report(rep2, std::to_string(k) + " and " + std::to_string((i+1)*interval) + " = (KDTREE) " + name, t1.type());
        }


    }
}



void
Tester::how_much_faster_is_ort_vertical(std::string name) {
    for(int k = 17; k < size_of_trees; ++k) {
        int testSize = k;
        Timer<unitofmeassure> t1;
        int amount = pow(2,testSize);
        int how_many = std::sqrt(amount)*1.5;
        int interval = 5;
        int jumps = how_many/interval;
        std::vector<std::vector<int>> timevector(jumps, std::vector<int> {});
        std::vector<std::vector<int>> timevector2(jumps, std::vector<int> {});
        for(int i = 0; i < 10; ++i) {
            std::tuple<Ort, KDTree> trees = buildtrees(testSize);
            Ort ort = std::get<0>(trees);
            KDTree kdtree = std::get<1>(trees);
            for(int size = 1; size < jumps+1; ++size) {
                for(int h = 0; h < 10; ++h) {
                    for(int j = 0; j < 100; ++j) {
                        Region reg {{(amount/100)*j, 0},{(amount/100)*j + size*interval, amount}};
                        t1.reset();
                        t1.start();
                        ort.search(reg);
                        t1.stop();

                        timevector.at(size-1).push_back(t1.duration().count());


                        t1.reset();
                        t1.start();
                        kdtree.search(reg);
                        t1.stop();

                        timevector2.at(size-1).push_back(t1.duration().count());
                        
                    }
                }
            }
        }
        for(int i = 0; i < timevector.size(); ++i) {
            std::vector<int> rep = numbers<int>(timevector.at(i));
            report(rep, std::to_string(k) + " and " + std::to_string((i+1)*interval) + " = (ORT) " + name, t1.type());


            std::vector<int> rep2 = numbers<int>(timevector2.at(i));
            report(rep2, std::to_string(k) + " and " + std::to_string((i+1)*interval) + " = (KDTREE) " + name, t1.type());
        }


    }
}

void
Tester::CACHE_only_create_ort_trees(std::string name) {
    for(int k = 17; k < size_of_trees; ++k) {
        Timer<unitofmeassure> t1;
        int testSize = k;
        int amount = pow(2,testSize);
        std::vector<int> times;
        for(int i = 0; i < 1; ++i) {
            t1.reset();
            t1.start();
            Ort ort = std::get<0>(buildtrees(testSize));
            t1.stop();
            times.push_back(t1.duration().count());
        }
    }
}

void
Tester::CACHE_create_and_search_ort_type_four_same(std::string name) {
 for(int k = 17; k < size_of_trees; ++k) {
        Timer<unitofmeassure> t1;
        int testSize = k;
        int amount = pow(2,testSize);
        std::vector<int> times;
        Ort ort = std::get<0>(buildtrees(testSize));
        for(int h = 0; h < 10; ++h) {
            for(int j = 0; j < 100; ++j) {
                t1.reset();
                t1.start();
                ort.search({{0, (amount/100)*h},{amount, (amount/100)*h + 100}});
                t1.stop();

                times.push_back(t1.duration().count());
                
            }
        }
        std::vector<int> rep = numbers<int>(times);
        report(rep, std::to_string(k) + " = " + name, t1.type());
    }
}


void
Tester::CACHE_create_and_search_ort_type_four_different(std::string name) {
 for(int k = 17; k < size_of_trees; ++k) {
        Timer<unitofmeassure> t1;
        int testSize = k;
        int amount = pow(2,testSize);
        std::vector<int> times;
        Ort ort = std::get<0>(buildtrees(testSize));
        for(int h = 0; h < 10; ++h) {
            for(int j = 0; j < 100; ++j) {
                t1.reset();
                t1.start();
                ort.search({{0, (amount/100)*j},{amount, (amount/100)*j + 100}});
                t1.stop();

                times.push_back(t1.duration().count());
                
            }
        }
        std::vector<int> rep = numbers<int>(times);
        report(rep, std::to_string(k) + " = " + name, t1.type());
    }
}


void
Tester::CACHE_create_and_search_ort_type_three_same(std::string name) {
 for(int k = 17; k < size_of_trees; ++k) {
        Timer<unitofmeassure> t1;
        int testSize = k;
        int amount = pow(2,testSize);
        std::vector<int> times;
        Ort ort = std::get<0>(buildtrees(testSize));
        for(int h = 0; h < 10; ++h) {
            for(int j = 0; j < 100; ++j) {
                t1.reset();
                t1.start();
                ort.search({{0, (amount/100)*h},{amount, (amount/100)*h + 100}});
                t1.stop();

                times.push_back(t1.duration().count());
                
            }
        }
        std::vector<int> rep = numbers<int>(times);
        report(rep, std::to_string(k) + " = " + name, t1.type());
    }
}


void
Tester::CACHE_create_and_search_ort_type_three_different(std::string name) {
 for(int k = 17; k < size_of_trees; ++k) {
        Timer<unitofmeassure> t1;
        int testSize = k;
        int amount = pow(2,testSize);
        std::vector<int> times;
        Ort ort = std::get<0>(buildtrees(testSize));
        for(int h = 0; h < 10; ++h) {
            for(int j = 0; j < 100; ++j) {
                t1.reset();
                t1.start();
                ort.search({{0, (amount/100)*j},{amount, (amount/100)*j + 100}});
                t1.stop();

                times.push_back(t1.duration().count());
                
            }
        }
        std::vector<int> rep = numbers<int>(times);
        report(rep, std::to_string(k) + " = " + name, t1.type());
    }
}

void
Tester::test_two_different_findints(std::string name) {
    CACHE_create_and_search_ort_type_three_different("Type three different");

    CACHE_create_and_search_ort_type_four_different("Type four different");

    CACHE_create_and_search_ort_type_three_same("Type three same");
    CACHE_create_and_search_ort_type_four_same("Type four same");
}


void
Tester::slices_of_100_horizontal_independent_of_n(std::string name) {
    for(int k = 17; k < size_of_trees; ++k) {
        int testSize = k;
        Timer<unitofmeassure> t1;
        int amount = pow(2,testSize);
        std::vector<int> times;
        for(int i = 0; i < 10; ++i) {
            Ort ort = std::get<0>(buildtrees(testSize));
            for(int h = 0; h < 10; ++h) {
                for(int j = 0; j < 100; ++j) {
                    t1.reset();
                    t1.start();
                    ort.search({{0, (amount/100)*j},{amount, (amount/100)*j + 100}});
                    t1.stop();

                    times.push_back(t1.duration().count());
                    
                }
            }
        }
        std::vector<int> rep = numbers<int>(times);
        report(rep, std::to_string(k) + " = " + name, t1.type());
    }

}




void
Tester::slices_of_100_vertical_independent_of_n(std::string name) {
    for(int k = 17; k < size_of_trees; ++k) {
        int testSize = k;
        Timer<unitofmeassure> t1;
        int amount = pow(2,testSize);
        std::vector<int> times;
        for(int i = 0; i < 10; ++i) {
            Ort ort = std::get<0>(buildtrees(testSize));
            for(int h = 0; h < 10; ++h) {
                for(int j = 0; j < 100; ++j) {
                    t1.reset();
                    t1.start();
                    ort.search({{(amount/100)*j, 0},{(amount/100)*j + 100, amount}});
                    t1.stop();

                    times.push_back(t1.duration().count());
                    
                }
            }
        }
        std::vector<int> rep = numbers<int>(times);
        report(rep, std::to_string(k) + " = " + name, t1.type());
    }

}

void Tester::cacheimportance(std::string name) { 
    for(int k = 17; k < size_of_trees; ++k) {
        int testSize = k;
        Timer<std::chrono::nanoseconds> t1;
        int amount = pow(2, testSize);
        std::vector<int> times;
        for(int i = 0; i < 10; ++i) {
            Ort ort = std::get<0>(buildtrees(testSize));
            for(int j = 0; j < 100; ++j) {
                for(int h = 0; h < 100; ++h) {
                    t1.reset();
                    t1.start();
                    ort.search({{(amount/100)*j, 0},{(amount/100)*j + 20, amount}});
                    t1.stop();

                    times.push_back(t1.duration().count());

                }
            }
        }
        std::vector<int> rep = numbers<int>(times);
        report(rep, std::to_string(k) + " = " + name, t1.type());
        

        std::vector<int> times2;
        for(int i = 0; i < 10; ++i) {
            Ort ort = std::get<0>(buildtrees(testSize));
            for(int j = 0; j < 100; ++j) {
                for(int h = 0; h < 100; ++h) {
                    t1.reset();
                    t1.start();
                    ort.search({{(amount/100)*h, 0},{(amount/100)*h + 20, amount}});
                    t1.stop();

                    times2.push_back(t1.duration().count());

                }
            }
        }

        std::vector<int> rep2 = numbers<int>(times2);
        report(rep2, std::to_string(k) + " = " + name, t1.type());
    }

}

void
Tester::ten_vertical_slices_have_same_performance(std::string name) {
    for(int k = 17; k < size_of_trees; ++k) {
        int testSize = k;
        Timer<std::chrono::nanoseconds> t1;
        int amount = pow(2, testSize);
        std::vector<std::vector<int>> times(10, std::vector<int> {});
        for(int i = 0; i < 10; ++i) {
            Ort ort = std::get<0>(buildtrees(testSize));
            for(int j = 0; j < 1000; ++j) {
                for(int h = 0; h < 10; ++h) {
                    t1.reset();
                    t1.start();
                    ort.search({{(amount/10)*h, 0},{(amount/10)*h + 50, amount}});
                    t1.stop();
                    times.at(h).push_back(t1.duration().count());

                }
            }
        }
        std::vector<std::vector<int>> rep = numbers2<int>(times);
        report2(rep, std::to_string(k) + " = " + name, t1.type());
    }
}

void
Tester::ten_vertical_slices_kdtree(std::string name) {
    for(int k = 17; k < size_of_trees; ++k) {
        int testSize = k;
        Timer<std::chrono::nanoseconds> t1;
        int amount = pow(2, testSize);
        std::vector<std::vector<int>> times(10, std::vector<int> {});
        for(int i = 0; i < 10; ++i) {
            KDTree kdtree = std::get<1>(buildtrees(testSize));
            for(int j = 0; j < 1000; ++j) {
                for(int h = 0; h < 10; ++h) {
                    t1.reset();
                    t1.start();
                    kdtree.search({{(amount/10)*h, 0},{(amount/10)*h + 50, amount}});
                    t1.stop();
                    times.at(h).push_back(t1.duration().count());

                }
            }
        }
        std::vector<std::vector<int>> rep = numbers2<int>(times);
        report2(rep, std::to_string(k) + " = " + name, t1.type());
    }
}



void
Tester::ten_horizontal_slices_have_same_performance(std::string name) {
    for(int k = 17; k < size_of_trees; ++k) {
        int testSize = k;
        Timer<std::chrono::nanoseconds> t1;
        int amount = pow(2, testSize);
        std::vector<std::vector<int>> times(10, std::vector<int> {});
        for(int i = 0; i < 10; ++i) {
            Ort ort = std::get<0>(buildtrees(testSize));
            for(int j = 0; j < 1000; ++j) {
                for(int h = 0; h < 10; ++h) {
                    t1.reset();
                    t1.start();
                    ort.search({{0, (amount/10)*h},{amount, (amount/10)*h + 50}});
                    t1.stop();
                    times.at(h).push_back(t1.duration().count());

                }
            }
        }
        std::vector<std::vector<int>> rep = numbers2<int>(times);
        report2(rep, std::to_string(k) + " = " + name, t1.type());
    }
}

void
Tester::ten_horizontal_slices_kdtree(std::string name) {
    for(int k = 17; k < size_of_trees; ++k) {
        int testSize = k;
        Timer<std::chrono::nanoseconds> t1;
        int amount = pow(2, testSize);
        std::vector<std::vector<int>> times(10, std::vector<int> {});
        for(int i = 0; i < 10; ++i) {
            KDTree kdtree = std::get<1>(buildtrees(testSize));
            for(int j = 0; j < 1000; ++j) {
                for(int h = 0; h < 10; ++h) {
                    t1.reset();
                    t1.start();
                    kdtree.search({{0, (amount/10)*h},{amount, (amount/10)*h + 50}});
                    t1.stop();
                    times.at(h).push_back(t1.duration().count());

                }
            }
        }
        std::vector<std::vector<int>> rep = numbers2<int>(times);
        report2(rep, std::to_string(k) + " = " + name, t1.type());
    }
}


void
Tester::compare_horizontal_slices_times_between_ort_and_kdtree(std::string name, Ort& ort, KDTree& kdtree, std::vector<int>& times, std::vector<int>& jumps_vector, std::vector<int>& max_jumps, int k) {
    int testSize = k;
    Timer<unitofmeassure> t1;
    Timer<unitofmeassure> t2;
    int amount = pow(2, testSize);
    int jumpcount = 0;
    int maxdepth = 0;
    int startlevel = 0;
    for(int h = 0; h < 100; ++h) {
        for(int j = 0; j < 10; ++j) {
            int a = 0;
            int size = 10;
            Region reg {{0, (amount/10)*j},{amount, (amount/10)*j + size}};
            jumpcount = 0;
            maxdepth = 0;
            startlevel = 0;

            t1.reset();
            t1.start();
            ort.search(reg);
            t1.stop();

            ort.Depthsearch(reg, jumpcount, maxdepth, startlevel);
            jumps_vector.push_back(jumpcount);
            max_jumps.push_back(maxdepth);

            t2.reset();
            t2.start();
            kdtree.search(reg);
            t2.stop();


            while(t1.duration().count() < t2.duration().count()) {
                a += 5;
                size += 5;
                reg = {{0, (amount/10)*j},{amount, (amount/10)*j + size}};
                jumpcount = 0;
                maxdepth = 0;



                t1.reset();
                t1.start();
                ort.search(reg);
                t1.stop();

                ort.Depthsearch(reg, jumpcount, maxdepth, startlevel);
                jumps_vector.push_back(jumpcount);
                max_jumps.push_back(maxdepth);

                t2.reset();
                t2.start();
                kdtree.search(reg);
                t2.stop();

            }
            if(a == 0) {
                times.push_back(a);
            } else {
                times.push_back(size);
            }
        }
    }
    
}


void
Tester::compare_vertical_slices_times_between_ort_and_kdtree(std::string name, Ort& ort, KDTree& kdtree, std::vector<int>& times, std::vector<int>& jumps_vector, std::vector<int>& max_jumps, int k) {
    int testSize = k;
    Timer<unitofmeassure> t1;
    Timer<unitofmeassure> t2;
    int amount = pow(2, testSize);
    int jumpcount = 0;
    int maxdepth = 0;
    int startlevel = 0;
    for(int i = 0; i < 10; ++i) {
        std::tuple<Ort, KDTree> trees = buildtrees(testSize);
        Ort ort = std::get<0>(trees);
        KDTree kdtree = std::get<1>(trees);
        for(int h = 0; h < 100; ++h) {
            for(int j = 0; j < 10; ++j) {
                int a = 0;
                int size = 10;
                jumpcount = 0;
                maxdepth = 0;
                startlevel = 0;
                Region reg {{0, (amount/10)*j},{amount, (amount/10)*j + size}};

                t1.reset();
                t1.start();
                ort.search(reg);
                t1.stop();

                ort.Depthsearch(reg, jumpcount, maxdepth, startlevel);
                jumps_vector.push_back(jumpcount);
                max_jumps.push_back(maxdepth);

                t2.reset();
                t2.start();
                kdtree.search(reg);
                t2.stop();


                while(t1.duration().count() < t2.duration().count()) {
                    a += 5;
                    size += 5;
                    reg = {{0, (amount/10)*j},{amount, (amount/10)*j + size}};
                    jumpcount = 0;
                    maxdepth = 0;
                    startlevel = 0;



                    t1.reset();
                    t1.start();
                    ort.search(reg);
                    t1.stop();

                    ort.Depthsearch(reg, jumpcount, maxdepth, startlevel);
                    jumps_vector.push_back(jumpcount);
                    max_jumps.push_back(maxdepth);



                    t2.reset();
                    t2.start();
                    kdtree.search(reg);
                    t2.stop();

                }
                if(a == 0) {
                    times.push_back(a);
                } else {
                    times.push_back(size);
                }
            }
        }
    }

}

void
Tester::compare_horizontal_slices_times_between_ort_and_kdtree(std::string name) {
    for(int k = 17; k < size_of_trees; ++k) {
        int testSize = k;
        Timer<unitofmeassure> t1;
        Timer<unitofmeassure> t2;
        int amount = pow(2, testSize);
        std::vector<int> times;
        for(int i = 0; i < 10; ++i) {
            std::tuple<Ort, KDTree> trees = buildtrees(testSize);
            Ort ort = std::get<0>(trees);
            KDTree kdtree = std::get<1>(trees);
            for(int h = 0; h < 100; ++h) {
                for(int j = 0; j < 10; ++j) {
                    int a = 0;
                    int size = 10;
                    Region reg {{0, (amount/10)*j},{amount, (amount/10)*j + size}};

                    t1.reset();
                    t1.start();
                    ort.search(reg);
                    t1.stop();

                    t2.reset();
                    t2.start();
                    kdtree.search(reg);
                    t2.stop();


                    while(t1.duration().count() < t2.duration().count()) {
                        a += 5;
                        size += 5;
                        reg = {{0, (amount/10)*j},{amount, (amount/10)*j + size}};


                        t1.reset();
                        t1.start();
                        ort.search(reg);
                        t1.stop();

                        t2.reset();
                        t2.start();
                        kdtree.search(reg);
                        t2.stop();

                    }
                    if(a == 0) {
                        times.push_back(a);
                    } else {
                        times.push_back(size);
                    }
                }
            }
        }
        std::vector<int> rep = numbers<int>(times, true);
        report(rep, std::to_string(k) + " = " + name, "times");
    }

}

void
Tester::compare_vertical_slices_times_between_ort_and_kdtree(std::string name) {
    for(int k = 17; k < size_of_trees; ++k) {
        int testSize = k;
        Timer<unitofmeassure> t1;
        Timer<unitofmeassure> t2;
        int amount = pow(2, testSize);
        std::vector<int> times;
        for(int i = 0; i < 10; ++i) {
            std::tuple<Ort, KDTree> trees = buildtrees(testSize);
            Ort ort = std::get<0>(trees);
            KDTree kdtree = std::get<1>(trees);
            for(int h = 0; h < 100; ++h) {
                for(int j = 0; j < 10; ++j) {
                    int a = 0;
                    int size = 10;
                    Region reg {{(amount/10)*j, 0},{(amount/10)*j + size, amount}};

                    t1.reset();
                    t1.start();
                    ort.search(reg);
                    t1.stop();

                    t2.reset();
                    t2.start();
                    kdtree.search(reg);
                    t2.stop();


                    while(t1.duration().count() < t2.duration().count()) {
                        a += 5;
                        size += 5;
                        reg = {{(amount/10)*j, 0},{(amount/10)*j + size, amount}};


                        t1.reset();
                        t1.start();
                        ort.search(reg);
                        t1.stop();

                        t2.reset();
                        t2.start();
                        kdtree.search(reg);
                        t2.stop();

                    }
                    if(a == 0) {
                        times.push_back(a);
                    } else {
                        times.push_back(size);
                    }
                }
            }
        }
        std::vector<int> rep = numbers<int>(times, true);
        report(rep, std::to_string(k) + " = " + name, "times");
    }

}
