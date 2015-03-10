#include <iostream>
#include <map>
#include <sstream>
#include "Ort.hpp"
#include "Data.hpp"
#include "KDTree.hpp"
#include "Timer.hpp"
#include <bitset>

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
                Timer t1;
                t1.start();
                Ort ort(amount, input);
                t1.stop();
                std::cout << "Built Ort tree with " << amount << " elements. Took " << t1.duration().count() << " ms." << std::endl;

                Timer t2;
                t2.start();
                KDTree kdtree(amount, input);
                t2.stop();
                std::cout << "Built kd tree with " << amount << " elements. Took " << t2.duration().count() << " ms." << std::endl;

                if(ortmap.find(n) == ortmap.end()) {
                    ortmap.insert(std::make_pair(n, ort));
                }
                if(kdtreemap.find(n) == kdtreemap.end()) {
                    kdtreemap.insert(std::make_pair(n, kdtree));
                }

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

        if(commands.at(0) == "search") {
            if(commands.size() != 7) {
                std::cout << "search takes 6 arguments: structure to search, number of iterations and a region x_1, y_1, x_2, y_2." << std::endl;
            } else {
                auto ort = ortmap.find(std::stoi(commands.at(1)));
                auto kdtree = kdtreemap.find(std::stoi(commands.at(1)));
                Point ll = {std::stoi(commands.at(3)), std::stoi(commands.at(4))};
                Point ur = {std::stoi(commands.at(5)), std::stoi(commands.at(6))};
                int count = std::stoi(commands.at(2));
                if(ort != ortmap.end()) {
                    Timer t1;
                    t1.start();
                    for(int i = 0; i < count; ++i) {
                        ort->second.easyQuery(ll,ur);
                    }
                    t1.stop();
                    //std::cout << ort->second.easyQuery(ll, ur) << std::endl;
                    std::cout << "Ort search took: " << t1.duration().count() << " ms." << std::endl;
                }
                else {
                    std::cout << "Ort structure at index " << commands.at(1) << " not found." <<std::endl;
                }

                if(kdtree != kdtreemap.end()) {
                    Timer t2;
                    t2.start();
                    for(int i = 0; i < count; ++i) {
                        kdtree->second.search({ll,ur});
                    }
                    t2.stop();
                    //std::cout << kdtree->second.search({ll, ur}) << std::endl;
                    std::cout << "KDtree search took: " << t2.duration().count() << " ms." << std::endl;
                } else {
                    std::cout << "KDtree structure at index " << commands.at(1) << " not found." << std::endl;
                }
                
            }
        }
    }
}





auto main(int argc, char** argv) -> int {

    /*int amount = pow(2,15);
    std::random_device rd;
    std::mt19937 gen(rd());
    Ort ort(amount, Data::generate(amount));
    std::vector<Point> points = Data::randomPoints(gen, amount);
    std::vector<Point> a = ort.easyQuery(points.at(0), points.at(1));
    std::vector<Point> b = ort.actualQuery(points.at(0), points.at(1));
    std::sort(std::begin(a), std::end(a), sortpointx);
    std::sort(std::begin(b), std::end(b), sortpointx);
    std::cout << "Punkterne er ens: " << (a == b) << std::endl;*/

    /*std::vector<uint> vec {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3};
    std::cout << Data::packBits(vec, 3) << std::endl;
    auto packed = Data::packBits(vec, 3);
    for(const auto& e : Data::packBits(vec, 3)) {
        std::bitset<32> bs(e);
        std::cout << bs.to_string() << std::endl;
    }
    std::cout << Data::findInt(packed, 3, 3) << std::endl;
    for(int i = 0; i < vec.size(); ++i) {
        Data::findInt(packed, 3, i);
    }
    std::cout << std::endl;*/

    
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
    Timer t1;
    //points.at(0) = {20,1};
    //points.at(1) = {50,amount};
    t1.start();
    for(int i = 0; i < loop; ++i) {
        ort.easyQuery(points.at(0), points.at(1));
    }
    t1.stop();

    std::cout << "Ort tree took: " << t1.duration().count() << " ms" << std::endl;

    KDTree kdtree(amount, input);
    Timer t2;
    t2.start();
    Region query = {points.at(0), points.at(1)};
    for(int i = 0; i < loop; ++i) {
        kdtree.search(query);
    }
    t2.stop();

    std::cout << "KDTree took: " << t2.duration().count() << " ms" << std::endl;
    std::cout << "Differs by factor: " << float(t1.duration().count())/float(t2.duration().count()) << std::endl;
    */

    for(int i = 0; i < 1000; ++i) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(4,14);

        int amount = pow(2,dis(gen));
        std::cout << "AMOUNT IS " << amount << std::endl;
        std::vector<Point> input = Data::generate(amount);
        Ort ort(amount, input);
        KDTree kdtree(amount, input);
        std::vector<Point> points = Data::randomPoints(gen, amount);
        //std::cout << "POINTS: " << points << std::endl;
        std::vector<Point> a = ort.easyQuery(points.at(0), points.at(1));
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
            std::cout << a << std::endl;
            std::cout << b << std::endl;
            std::cout << diff(a,b) << std::endl;
        }
        if(c != d) {
            std::cout << "ERROR TWO" << std::endl;
            std::cout << c << std::endl;
            std::cout << d << std::endl;
            std::cout << diff(c,d) << std::endl;
        }
    }
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
