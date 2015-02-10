#include <iostream>
#include "Ort.hpp"
#include "Data.hpp"
#include "KDTree.hpp"

std::vector<Point> diff(std::vector<Point> a, std::vector<Point> b) {
    std::vector<Point> result;
    std::set_difference(a.begin(), a.end(), b.begin(), b.end(), 
                        std::inserter(result, result.begin()), sortpointx);
    return result;
}

std::vector<Point> randomPoints(std::mt19937 gen, int amount) {

     std::uniform_int_distribution<> dis(1, amount);
     Point l, u;

    int a = 5;
    int b = 5;

    while(a == b) {
     
        a = dis(gen);
        b = dis(gen);
        if(a < b) {
            l.x = a; 
            u.x = b;
        } else {
            u.x = a;
            l.x = b;
        }
    }

    a = 5;
    b = 5;
    while(a == b) {
        a = dis(gen);
        b = dis(gen);
        if(a < b) {
            l.y = a;
            u.y = b;
        } else {
            u.y = a;
            l.y = b;
        }
    }
    std::vector<Point> result {l, u};
    return result;
}


int main(int argc, char** argv) {
    /*std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(4,14);
    for(int i = 0; i < 1000; ++i) {
        int amount = pow(2,dis(gen));
        std::cout << "AMOUNT IS " << amount << std::endl;
        Ort ort(amount);
        std::vector<Point> points = randomPoints(gen, amount);
        std::cout << "POINTS: " << points << std::endl;
        std::vector<Point> a = ort.easyQuery(points.at(0), points.at(1));
        std::vector<Point> b = ort.actualQuery(points.at(0), points.at(1));
        std::sort(std::begin(a), std::end(a), sortpointx);
        std::sort(std::begin(b), std::end(b), sortpointx);
        if(a != b) {
            std::cout << "ERROR" << std::endl;
            std::cout << a << std::endl;
            std::cout << b << std::endl;
            std::cout << diff(a,b) << std::endl;
        }
    }*/
    if(argc == 1) {
        for(int i = 0; i < 1; ++i) {
            KDTree kdtree(32);
            kdtree.build();
            Region query = {{20, 20}, {30, 30}};
            kdtree.search(query);
            Region q2 = {{10,10}, {20,20}};
            if(kdtree.search(q2) != kdtree.actualSearch(q2)) {
                std::cout << std::endl << std::endl << "ERROR" << std::endl;
                std::cout <<kdtree.search(q2) << std::endl;
                std::cout << kdtree.actualSearch(q2) << std::endl;
                kdtree.saveState(q2);

            }
        }
    }

    if(argc == 2) {
        const char* input_file = argv[1];
        std::string input(input_file);
        KDTree kdtree(128);
        kdtree.loadState(input);
    }


    return 0;
}
