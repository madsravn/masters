#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>
#include <string>
#include <cstdint>

using uint = std::uint32_t;

std::vector<uint> arr;

std::vector<uint> populate() {
    std::vector<uint> vec;
    for(int i = 0; i < 16; ++i) {
        vec.push_back(1 << i);
    }
    return vec;
}

int rank_correct(uint number) {
    std::bitset<32> bits(number);
    return bits.count();
}


int rank(uint number) {
    uint first = number >> 16;
    uint last = number & 65'535;

    uint answer = arr[first] + arr[last];
    return answer;
}

std::vector<uint> populateList() {
    std::vector<uint> vec;
    for(uint i = 0; i < UINT16_MAX+1; ++i) {
        std::bitset<32> bits(i);
        vec.push_back(bits.count());
    }
    return vec;
}

uint andtoremovefirst(uint start) {
    uint result = 0;
    for(int i = 0; i < 32-start; ++i) {
        result = result << 1;
        result += 1;
    }
    return result;
}

uint andtoremovelast(uint start) {
    uint t = andtoremovefirst(32-start);
    uint res = ~t;
    return res;
}

std::string printVector(std::vector<uint> bitvector) {
    std::string str;
    for(const auto& e : bitvector) {
        std::bitset<32> bits(e);
        for(const auto& c : bits.to_string()) {
            str += c;
            str += ", ";
        }
    }
    return str;
}

uint rank(std::vector<uint> bv, uint start, uint stop) {

    int start_i = start/32;
    int start_pos = start%32;

    int stop_i = stop/32;
    int stop_pos = stop%32;

    if(start_i == stop_i) {
        std::cout << "We are looking in the same container entry" << std::endl;
    }

    //TODO: Check if we start at entry 31 or stop at entry 0



    return 12;
}



int main() {

    static_assert(sizeof(uint) == 4, "std::uint32_t type not supported on this system");

    std::cout << andtoremovefirst(30) << std::endl;
    std::bitset<32> bits(andtoremovefirst(30));
    std::cout << bits.to_string() << std::endl;

    std::bitset<32> bits2(andtoremovelast(30));
    std::cout << bits2.to_string() << std::endl;
/*
    // REMEMBER TO INITIALIZE THIS
    arr = populateList();


    std::vector<uint> bitvector { 32132, 5623, 7362};
    //std::cout << printVector(bitvector) << std::endl;

    std::cout << rank(bitvector, 12, 32) << std::endl;
    uint test = 4'294'967'001;
    std::cout << rank(test) << " and " << rank_correct(test) << std::endl;
*/
    return 0;
}
