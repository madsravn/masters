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


int main() {
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
    KDTree kdtree(16);
    kdtree.build();


    return 0;
}
