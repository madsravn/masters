#include <random>
#include <algorithm>
#include <bitset>
#include <chrono>
#include "Data.hpp"

std::vector<char> translatetobits(const std::vector<uint>& numbers, int size) {
    std::vector<char> bits;

    for(int i = 0; i < numbers.size(); ++i) {
        std::bitset<32> bs(numbers.at(i));
        for(const auto& e : bs.to_string().substr(32-size)) {
            bits.push_back(e - '0');
        }
    }

    return bits;
}

std::vector<char> translatetobits2(const std::vector<uint>& numbers, int size) {
    
    std::vector<char> bits;

    for(int i = 0; i < numbers.size(); ++i) {
        std::bitset<32> bs(numbers.at(i));
        if((bits.size()%32) + size > 32) {
            while(bits.size() % 32 != 0) {
                bits.push_back(0);
            }
        }

        for(const auto& e : bs.to_string().substr(32-size)) {
            bits.push_back(e - '0');
        }
    }

    return bits;
}

uint
Data::findInt2(const std::vector<uint>& input, int size, int pos) {
    

    //TODO: OPTIMIZE
    int intspercontainer = 32/size;
    int container = pos/intspercontainer;
    int position = (pos % intspercontainer)*size;

    int end = position+size;
    
    uint number = input.at(container);
    number = number >> (32 - end);
    number = number & ((1 << size) - 1);
    return number;
}



// TODO: Assert that number can reside in two entries next to each other
// The way $input$ is packed with 32 bits currently, means that this assertion holds
uint
Data::findInt(const std::vector<uint>& input, int size, int pos) {
    pos = pos*size;
    int end = pos+size;
    int firstc = pos >> 5;
    int secondc = end >> 5;
    int ipos = pos & 31;
    int jpos = end & 31;
    
    if(firstc == secondc) {
        uint number = input[firstc];
        number = number >> (32 - end);
        number = number & ((1 << size) - 1);
        return number;
    }
    // else
    uint number = input[firstc];
    number = number << (jpos);
    number = number & ((1 << size) -1);
    uint number2 = input[secondc];
    number2 = number2 >> (32 - jpos);
    number2 = number2 & ((1 << jpos) - 1);
    
    return (number | number2);
}

uint
Data::findInt3(const std::vector<uint>& input, int size, int pos) {
    pos = pos*size;
    int firstc = pos >> 5;
    int ipos = pos & 31;
    int end = ipos+size;
    std::uint64_t t = input[firstc];

    std::uint64_t num = (t << 32) | input[firstc+1];
    std::uint64_t number = num >> (64-end);
    number = number & ((1 << size)-1);

    return number;
}



std::vector<uint>
Data::packBits(const std::vector<uint>& input, int size) {

    std::vector<char> bits = translatetobits(input, size);
    while(bits.size() % 32 != 0) {
        bits.push_back(0);
    }
    
    std::vector<uint> packedbits;
    for(int i = 0; i < bits.size(); i += 32) {
        uint res = 0;
        for(int j = 0; j < 31; ++j) {
            res += (bits.at(i+j));
            res = res << 1;
        }
        res += (bits.at(i+31));
        packedbits.push_back(res);
    }

    // Current lookup requires an empty entry - should be fixed
    packedbits.push_back(0);

    return packedbits;
}


std::vector<uint>
Data::packBits2(const std::vector<uint>& input, int size) {

    std::vector<char> bits = translatetobits2(input, size);
    while(bits.size() % 32 != 0) {
        bits.push_back(0);
    }
    
    std::vector<uint> packedbits;
    for(int i = 0; i < bits.size(); i += 32) {
        uint res = 0;
        for(int j = 0; j < 31; ++j) {
            res += (bits.at(i+j));
            res = res << 1;
        }
        res += (bits.at(i+31));
        packedbits.push_back(res);
    }

    // Current lookup requires an empty entry - should be fixed
    packedbits.push_back(0);

    return packedbits;
}



std::vector<Point> 
Data::randomPoints(std::mt19937 gen, int amount) {

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



std::vector<Point>
Data::generate(int amount) {
    int n{0};
    std::vector<int> x(amount);
    std::vector<int> y(amount);

    std::generate(std::begin(x), std::end(x), [&] { return n++;});
    std::copy(std::begin(x), std::end(x), std::begin(y));

    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(std::begin(x), std::end(x), g);
    std::shuffle(std::begin(y), std::end(y), g);

    std::vector<Point> points;
    for(int i = 0; i < amount; ++i) {
        points.push_back({x[i], y[i]});
    }
    return points;
}

std::vector<Point>
Data::generateRandom(int amount, int start, int stop) {

    std::vector<int> x(amount);
    std::vector<int> y(amount);
    std::vector<int> placeholder(stop-start);
    std::generate(std::begin(placeholder), std::end(placeholder), [&] {return start++;});

    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(std::begin(placeholder), std::end(placeholder), g);
    std::copy(std::begin(placeholder), std::begin(placeholder)+amount, std::begin(x));
    
    std::shuffle(std::begin(placeholder), std::end(placeholder), g);
    std::copy(std::begin(placeholder), std::begin(placeholder)+amount, std::begin(y));

    std::vector<Point> points;
    for(int i = 0; i < amount; ++i) {
        points.push_back({x[i], y[i]});
    }
    return points;
}

void
Data::saveState(std::vector<Point> points, Region region) {
     auto now = std::chrono::system_clock::now();
     std::random_device rd;
     std::mt19937 gen(rd());
     auto secs = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch());

     std::string filename = "debug/" + std::to_string(secs.count());
     std::uniform_int_distribution<> dis(7652, 8761238);
     int random = dis(gen);
     filename += "_" + std::to_string(random);
     std::ofstream output(filename);
     output << region.ll.x << " " << region.ll.y << " " << region.ur.x << " " << region.ur.y;
     for(const auto& p : points) {
         output << std::endl << p.x << " " << p.y;
     }
     output.flush();
     output.close();
     std::cout << "Error state saved as " << filename << std::endl;

}

std::tuple<std::vector<Point>, Region> 
Data::loadState(std::string filename) {
    std::ifstream file("debug/" + filename);
    Region query;
    std::vector<Point> points;
    if(file.fail()) {
        std::cout << "Encountered an error opening the file" << std::endl;
        file.close();
    } else {
        file >> query.ll.x >> query.ll.y >> query.ur.x >> query.ur.y;
        int x,y;
        while(file >> x >> y) {
            points.push_back({x,y});
        }
        file.close();
    }
    return std::make_tuple(points, query);
}




