#include <iostream>
#include <vector>

std::vector<int> populate() {
    std::vector<int> vec;
    for(int i = 0; i < 16; ++i) {
        vec.push_back(1 << i);
    }
    return vec;
}

int main() {

    std::vector<int> vec = populate();
    for(const auto& e : vec) {
        std::cout << e << ", ";
    }
    std::cout << std::endl;

    return 0;
}
