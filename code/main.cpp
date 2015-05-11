#include <iostream>
#include <iomanip>
#include <map>
#include <sstream>
#include "Ort.hpp"
#include "Data.hpp"
#include "KDTree.hpp"
//#include "Timer.hpp"
#include <bitset>
#include <string>
#include "Tester.hpp"

using unitofmeassure = std::chrono::microseconds;


std::vector<Point> diff(std::vector<Point> a, std::vector<Point> b) {
    std::vector<Point> result;
    std::set_difference(a.begin(), a.end(), b.begin(), b.end(), 
                        std::inserter(result, result.begin()), sortpointx);
    return result;
}


// From http://stackoverflow.com/questions/236129/splitting-a-string-in-c
std::vector<std::string>& split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

// From http://stackoverflow.com/questions/236129/splitting-a-string-in-c
std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

void repl() {
std::map<int, Ort> ortmap;
    std::map<int, KDTree> kdtreemap;
    while(1) {
        std::string command;
        std::cout << "Command>> ";
        std::getline(std::cin, command);
        std::vector<std::string> commands = split(command, ' ');

        if(commands.at(0) == "build") {
            for(int i = 1; i < commands.size(); ++i) {
                int n = std::stoi(commands.at(i));
                int amount = pow(2,n);
                std::cout << std::endl << "Building trees with size " << amount << std::endl;
                std::vector<Point> input = Data::generate(amount);
                Timer<unitofmeassure> t1;
                t1.start();
                Ort ort(amount, input);
                t1.stop();
                std::cout << "Built Ort tree with " << amount << " elements. Took " << t1.duration().count() << " " << t1.type() << std::endl;

                Timer<unitofmeassure> t2;
                t2.start();
                KDTree kdtree(amount, input);
                t2.stop();
                std::cout << "Built kd tree with " << amount << " elements. Took " << t2.duration().count() << " " << t2.type() << std::endl;

                if(ortmap.find(n) == ortmap.end()) {
                    ortmap.insert(std::make_pair(n, ort));
                }
                if(kdtreemap.find(n) == kdtreemap.end()) {
                    kdtreemap.insert(std::make_pair(n, kdtree));
                }

            }
        }
        if(commands.at(0) == "size") {
            std::cout << "Size of the Ort map: " << std::endl;
            /*std::vector<std::string> titles {"", "Size of Ort without big jumps", "Size of Ort with non-linear big jumps", "Size of Ort with linear big jumps"};
            for(int i = 1; i < 4; ++i) {
                std::cout << std::endl << std::endl << titles.at(i) << std::endl;
                for(const auto& e: ortmap) {
                    std::cout << pow(2, e.first) << " " << e.second.size(i) << std::endl;
                }
            }*/
            for(const auto& e : ortmap) {
                std::cout << int(pow(2, e.first)) << e.second.size(3) << std::endl;
            }
            std::cout << std::endl << std::endl << "size of the KDTree map: " << std::endl;
            for(const auto& e : kdtreemap) {
                std::cout << int(pow(2, e.first)) << " " << e.second.size() << std::endl;
            }
        }

        if(commands.at(0) == "list") {
            std::cout << "Ort map contains the following keys: " << std::endl;
            for(const auto& e : ortmap) {
                std::cout << e.first << " ";
            }
            std::cout << std::endl;

            std::cout << "KDtree map contains the following keys: " << std::endl;
            for(const auto& e : kdtreemap) {
                std::cout << e.first << " ";
            }
            std::cout << std::endl;
        }
        
        if(commands.at(0) == "quit") {
            return;
        }

        if(commands.at(0) == "show") {
            if(commands.size() == 2) {
                auto entry = std::stoi(commands.at(1));
                auto ort = ortmap.find(entry);
                if(ort != ortmap.end()) {
                    for(const auto& e : ort->second.getJumps()) {
                        std::cout << e.jump << " (" << e.end << ")" << " => ";
                    }
                    std::cout << std::endl;
                }
            }
            if(commands.size() == 3) {
                auto entry = std::stoi(commands.at(1));
                auto ort = ortmap.find(entry);
                if(ort != ortmap.end()) {
                    for(const auto& e : ort->second.getJumps()) {
                        std::cout << e.jump << " (" << e.end << ")" << " => " << std::endl;
                        std::cout << e.entries.size() << std::endl;
                        std::cout << e.major.size() << std::endl;
                        std::cout << e.minor.size() << std::endl;
                    }
                    std::cout << std::endl;
                }
            }

        }



        if(commands.at(0) == "search") {
            if(commands.size() != 7) {
                std::cout << "search takes 6 arguments: structure to search, number of iterations and a region x_1, y_1, x_2, y_2." << std::endl;
            } else {
                auto ort = ortmap.find(std::stoi(commands.at(1)));
                auto kdtree = kdtreemap.find(std::stoi(commands.at(1)));
                Point ll = {std::stoi(commands.at(3)), std::stoi(commands.at(4))};
                Point ur = {std::stoi(commands.at(5)), std::stoi(commands.at(6))};
                int count = std::stoi(commands.at(2));
                int resultsize = -1;
                std::vector<Point> a,b;
                
                if(ort != ortmap.end()) {
                    
                    Timer<unitofmeassure> t1;
                    t1.start();
                    for(int i = 0; i < count; ++i) {
                        ort->second.search({ll,ur});
                    }
                    t1.stop();
                    std::cout << "Ort search with linear-space big jumps took: " << t1.duration().count() << " ms." << std::endl;
                    a = ort->second.search({ll,ur});
                    resultsize = a.size();

                }
                else {
                    std::cout << "Ort structure at index " << commands.at(1) << " not found." <<std::endl;
                }

                if(kdtree != kdtreemap.end()) {
                    Timer<unitofmeassure> t2;
                    t2.start();
                    for(int i = 0; i < count; ++i) {
                        kdtree->second.search({ll,ur});
                    }
                    t2.stop();
                    //std::cout << kdtree->second.search({ll, ur}) << std::endl;
                    std::cout << "KDtree search took: " << t2.duration().count() << " ms." << std::endl;
                    b = kdtree->second.search({ll,ur});
                } else {
                    std::cout << "KDtree structure at index " << commands.at(1) << " not found." << std::endl;
                }
                std::cout << "The search gave " << resultsize << " results." << std::endl;
                std::sort(std::begin(a), std::end(a), sortpointx);
                std::sort(std::begin(b), std::end(b), sortpointx);
                std::cout << "The results are identical: " << (a == b) << std::endl;
                
            }
        }
    }
}

void testingRun() {
    for(int i = 0; i < 100000; ++i) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(17,20);

        int amount = pow(2,dis(gen));
        std::cout << "AMOUNT IS " << amount << std::endl;
        std::vector<Point> input = Data::generate(amount);
        Ort ort(amount, input);
        KDTree kdtree(amount, input);
        for(int j = 0; j < 10000; ++j) {
            std::vector<Point> points = Data::randomPoints(gen, amount);
            //std::cout << "POINTS: " << points << std::endl;
            std::vector<Point> a = ort.search({points.at(0), points.at(1)});
            std::vector<Point> b = ort.actualQuery(points.at(0), points.at(1));
            Region query = {points.at(0), points.at(1)};
            std::vector<Point> c = kdtree.search(query);
            std::vector<Point> d = kdtree.actualSearch(query);
            std::sort(std::begin(a), std::end(a), sortpointx);
            std::sort(std::begin(b), std::end(b), sortpointx);
            std::sort(std::begin(c), std::end(c), sortpointx);
            std::sort(std::begin(d), std::end(d), sortpointx);
            if(a != b) {
                std::cout << "ERROR" << std::endl;
                std::cout << "Search area: " << points.at(0) << ", " << points.at(1) << std::endl;
                std::cout << a << std::endl;
                std::cout << "Size of a: " << a.size() << std::endl;
                std::cout << b << std::endl;
                std::cout << "Size of b: " << b.size() << std::endl;
                std::cout << "DIFF: " << diff(a,b) << std::endl;
            }
            if(c != d) {
                std::cout << "ERROR TWO" << std::endl;
                std::cout << c << std::endl;
                std::cout << d << std::endl;
                std::cout << "DIFF: " << diff(c,d) << std::endl;
            }
        }
    }
}

void measureTimeOfPackedInts() {
    std::vector<uint> vec;

    for(int i = 0; i < 8; ++i) {
        for(int j = 0; j < 10; ++j) {
            vec.push_back(i);
        }
    }
    std::vector<int> vec2;
    for(int i = 0; i < 1000000; ++i) {
        vec2.push_back(i % vec.size());
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(std::begin(vec), std::end(vec), gen);
    std::shuffle(std::begin(vec2), std::end(vec2), gen);

    auto sizekey = std::max_element(std::begin(vec), std::end(vec));
    int biggest = vec.at(std::distance(std::begin(vec), sizekey));

    int size = std::ceil(std::log2(biggest+1));
       
    //std::cout << Data::packBits(vec, size) << std::endl;
    auto packed = Data::packBits(vec, size);
    
    for(int i = 0; i < vec.size(); ++i) {
        if(Data::findInt(packed, size, i) != vec.at(i)) {
            std::cout << Data::findInt(packed, size, i) << " == " << vec.at(i) << std::endl;
        }
    }

    auto packed2 = Data::packBits2(vec, size);
    std::cout << "TO" << std::endl;
    for(int i = 0; i < vec.size(); ++i) {
        if(Data::findInt3(packed, size, i) != vec.at(i)) {
            std::cout << Data::findInt3(packed, size, i) << " == " << vec.at(i) << std::endl;
        }
    }

    for(const auto& e : Data::packBits(vec, size)) {
        std::bitset<32> bs(e);
        std::cout << bs.to_string() << std::endl;
    }

    Timer<unitofmeassure> t1;
    t1.start();
    for(const auto& e: vec2) {
        Data::findInt(packed, size, e);
    }
    t1.stop();
    std::cout << t1.duration().count() << std::endl;

    t1.startover();
    for(const auto& e : vec2) {
        Data::findInt3(packed, size, e);
    }
    t1.stop();
    std::cout << t1.duration().count() << std::endl;

    t1.startover();
    for(const auto& e: vec2) {
        Data::findInt(packed, size, e);
    }
    t1.stop();
    std::cout << t1.duration().count() << std::endl;

    t1.startover();
    for(const auto& e : vec2) {
        Data::findInt3(packed, size, e);
    }
    t1.stop();
    std::cout << t1.duration().count() << std::endl;
}


void TESTS() {
    
    Tester test(26);

    //test.how_much_faster_is_ort_vertical("Testing how much faster Ort is than KDTree vertical");
    test.run(2,0);
    test.run(3,0);
    test.run(4,0);
    //test.run(2,1);
    //test.run(3,0);
    //test.run2();

    /*    
    test.slices_of_100_vertical_independent_of_n("Testing that slices of 100 is independent of n");
    test.slices_of_100_horizontal_independent_of_n("Testing that slices of 100 horizontally is independent of n");

    //test.cacheimportance("Showing cache difference");
    
    */
    //test.compare_vertical_slices_times_between_ort_and_kdtree("Compare vertical slices size between ort and kdtree");
    //test.compare_horizontal_slices_times_between_ort_and_kdtree("Compare horizontal slices size between ort and kdtree");
    /*
    

    test.ten_vertical_slices_have_same_performance("Testing if vertical lines agree");
    test.ten_horizontal_slices_have_same_performance("Testing if horizontal lines agree");
    test.ten_vertical_slices_kdtree("Testing if vertical lines on kdtree agree");
    test.ten_horizontal_slices_kdtree("Testing if horizontal lines on kdtree agree");
    */

    //test.how_much_faster_is_ort_horizontal("Testing how much faster Ort is than KDTree horizontal");


    // NO LONGER RELEVANT!
    //test.test_two_different_findints("Two different findints in ort");
}





auto main(int argc, char** argv) -> int {

    TESTS();

    //repl();
    /*int amount = pow(2,15);
    std::random_device rd;
    std::mt19937 gen(rd());
    Ort ort(amount, Data::generate(amount));
    std::vector<Point> points = Data::randomPoints(gen, amount);
    std::vector<Point> a = ort.search({points.at(0), points.at(1)}, 4);
    std::vector<Point> b = ort.actualQuery(points.at(0), points.at(1));
    std::sort(std::begin(a), std::end(a), sortpointx);
    std::sort(std::begin(b), std::end(b), sortpointx);
    std::cout << "Punkterne er ens: " << (a == b) << std::endl;*/



    


    
    /*int amount = pow(2,15);
    std::random_device rd;
    std::mt19937 gen(rd());
    Ort ort(amount, Data::generate(amount));
    std::vector<Point> points = Data::randomPoints(gen, amount);
    for(int i = 0; i < 100; ++i) {
        ort.easyQuery(points.at(0), points.at(1));
    }*/

    /*
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(4,14);
    int amount = pow(2,22);
    int loop = 100;
    std::vector<Point> input = Data::generate(amount);
    std::vector<Point> points = Data::randomPoints(gen, amount);


    std::cout << "Generating data done" << std::endl;
    Ort ort(amount, input);
    std::cout << "Done building ort" << std::endl;
    Timer<unitofmeassure> t1;
    //points.at(0) = {20,1};
    //points.at(1) = {50,amount};
    t1.start();
    for(int i = 0; i < loop; ++i) {
        ort.easyQuery(points.at(0), points.at(1));
    }
    t1.stop();

    std::cout << "Ort tree took: " << t1.duration().count() << " ms" << std::endl;

    KDTree kdtree(amount, input);
    Timer<unitofmeassure> t2;
    t2.start();
    Region query = {points.at(0), points.at(1)};
    for(int i = 0; i < loop; ++i) {
        kdtree.search(query);
    }
    t2.stop();

    std::cout << "KDTree took: " << t2.duration().count() << " ms" << std::endl;
    std::cout << "Differs by factor: " << float(t1.duration().count())/float(t2.duration().count()) << std::endl;
    */


    /*
    for(int i = 0; i < 100000; ++i) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(16,18);

        int amount = pow(2,dis(gen));
        std::cout << "AMOUNT IS " << amount << std::endl;
        std::vector<Point> input = Data::generate(amount);
        Ort ort(amount, input);
        KDTree kdtree(amount, input);
        for(int j = 0; j < 10000; ++j) {
            std::vector<Point> points = Data::randomPoints(gen, amount);
            //std::cout << "POINTS: " << points << std::endl;
            std::vector<Point> a = ort.search({points.at(0), points.at(1)});
            std::vector<Point> b = ort.actualQuery(points.at(0), points.at(1));
            Region query = {points.at(0), points.at(1)};
            std::vector<Point> c = kdtree.search(query);
            std::vector<Point> d = kdtree.actualSearch(query);
            std::sort(std::begin(a), std::end(a), sortpointx);
            std::sort(std::begin(b), std::end(b), sortpointx);
            std::sort(std::begin(c), std::end(c), sortpointx);
            std::sort(std::begin(d), std::end(d), sortpointx);
            if(a != b) {
                std::cout << "ERROR" << std::endl;
                std::cout << "Search area: " << points.at(0) << ", " << points.at(1) << std::endl;
                std::cout << a << std::endl;
                std::cout << "Size of a: " << a.size() << std::endl;
                std::cout << b << std::endl;
                std::cout << "Size of b: " << b.size() << std::endl;
                std::cout << "DIFF: " << diff(a,b) << std::endl;
            }
            if(c != d) {
                std::cout << "ERROR TWO" << std::endl;
                std::cout << c << std::endl;
                std::cout << d << std::endl;
                std::cout << "DIFF: " << diff(c,d) << std::endl;
            }
        }
    }*/

    /*if(argc == 1) {
        for(int i = 0; i < 5000; ++i) {
            int amount = 256;
            std::random_device rd;
            std::mt19937 gen(rd());
            std::vector<Point> points = Data::randomPoints(gen, amount);
            KDTree kdtree(amount, Data::generate(amount));
            Region q2 = {{10,10}, {100,100}};
            std::vector<Point> a = kdtree.search(q2);
            std::vector<Point> b = kdtree.actualSearch(q2);
            std::sort(std::begin(a), std::end(a), sortpointx);
            std::sort(std::begin(b), std::end(b), sortpointx);
            if(a != b) {
                std::cout << std::endl << std::endl << "ERROR" << std::endl;
                std::cout <<kdtree.search(q2) << std::endl;
                std::cout << kdtree.actualSearch(q2) << std::endl;
                kdtree.saveState(q2);

            }
        }
    }*/
/*
    if(argc == 2) {
        const char* input_file = argv[1];
        std::string input(input_file);
        KDTree kdtree(128);
        kdtree.loadState(input);
    }
*/

    return 0;
}
