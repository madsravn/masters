#include <iostream>
#include "Ort.hpp"
#include "Data.hpp"
#include "KDTree.hpp"
#include "Timer.hpp"

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
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(4,14);
    int amount = pow(2,14);
    int loop = 1000;
    std::vector<Point> input = Data::generate(amount);
    Ort ort(amount, input);
    std::vector<Point> points = randomPoints(gen, amount);
    Timer t1;
    t1.start();
    for(int i = 0; i < loop; ++i) {
        ort.easyQuery(points.at(0), points.at(1));
    }
    t1.stop();

    KDTree kdtree(amount, input);
    Timer t2;
    t2.start();
    Region query = {points.at(0), points.at(1)};
    for(int i = 0; i < loop; ++i) {
        kdtree.search(query);
    }
    t2.stop();

    std::cout << "Ort tree took: " << t1.duration().count() << " ms" << std::endl;
    std::cout << "KDTree took: " << t2.duration().count() << " ms" << std::endl;
    std::cout << "Differs by factor: " << float(t1.duration().count())/float(t2.duration().count()) << std::endl;



    /*
    for(int i = 0; i < 1000; ++i) {
        int amount = pow(2,dis(gen));
        std::cout << "AMOUNT IS " << amount << std::endl;
        Ort ort(amount);
        KDTree kdtree(amount);
        std::vector<Point> points = randomPoints(gen, amount);
        std::cout << "POINTS: " << points << std::endl;
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
    */
    /*
    if(argc == 1) {
        for(int i = 0; i < 5000; ++i) {
            KDTree kdtree(64);
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
