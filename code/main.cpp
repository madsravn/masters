#include <iostream>
#include "Ort.hpp"
#include "Data.hpp"
#include "KDTree.hpp"

int main() {

    for(int i = 0; i < 1000; ++i) {
        Ort ort(2048);
        std::vector<Point> a = ort.easyQuery({4,100}, {29,300});
        std::vector<Point> b = ort.actualQuery({4,100}, {29,300});
        std::sort(std::begin(a), std::end(a), sortpointx);
        std::sort(std::begin(b), std::end(b), sortpointx);
        if(a != b) {
            std::cout << "ERROR" << std::endl;
        }
    }


    return 0;
}
