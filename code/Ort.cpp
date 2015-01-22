#include "Ort.hpp"
#include <iostream>
#include <bitset>

template <class T>
inline std::ostream& operator << (std::ostream& os, const std::vector<T>& v) {
	os << "[";
	for (const auto& elem : v)
	{
		os << " " << elem;
	}
	os << " ]";
	return os;
}

inline std::ostream& operator << (std::ostream& os, const Point& p){
    os << "(" << p.x << ", " << p.y << ")" << ", ";
    return os;
}


uint 
Ort::rank(uint number) {
    uint first = number >> 16;
    uint last = number & 65'535;

    uint answer = inttobin[first] + inttobin[last];
    return answer;
}

uint
Ort::makemask(uint range) {
    uint result = 0;
    for(int i = 0; i < 32-range; ++i) {
        result = result << 1;
        result += 1;
    }
    result = ~result;
    return result;
}

uint
Ort::findRank(int level, int nodepos, int pos) {

    // Slå op i ranks level og position med pos/32 og pos%32
    // Træk nodepos/2 fra (da der er lige mange 1'ere og 0'ere før
    // Så har du din rank

    /*std::cout << "FINDRANK STARTER HER" << std::endl;
    std::vector<uint> curr_rank = ranks.at(level);
    std::cout << "curr_rank: " << curr_rank << std::endl;
    std::vector<uint> curr_level = levels.at(level);
    std::cout << "curr_level: " << curr_level << std::endl;
    int pos_i = pos/32;
    int pos_a = pos%32;
    int resultrank = curr_rank.at(pos_i);
    std::cout << "resultrank = " << resultrank << std::endl;
    int t = curr_level.at(pos_i);
    std::cout << "pos_a = " << pos_a << std::endl;
    outputLevels();
    std::bitset<32> b(t);
    std::cout << b.to_string() << std::endl;
    t = t & makemask(pos_a);
    std::bitset<32> bb(t);
    std::cout << bb.to_string() << std::endl;
    resultrank += rank(t);
    resultrank -= nodepos/2;*/

    // Simple version
    uint mask = makemask(pos);
    uint t = (levels.at(level)).at(0);
    t = t & mask;
    uint resultrank = rank(t);

    return resultrank;
}

void
Ort::populateList() {
    for(uint i = 0; i < UINT16_MAX+1; ++i) {
        std::bitset<32> bits(i);
        inttobin.push_back(bits.count());
    }
}

// position beskriver den vi kigger på
// nodepos beskriver hvor den node vi kigger på starter henne sådan vi kan regne ud hvor mange 1'ere der kommer før den
// level beskriver level. 
// amount beskriver hvor mange der er i hver node
Point
Ort::followball(int level, int nodepos, int pos, int amount) {
    if(amount > 1) {
        
        uint irank = findRank(level, nodepos, pos) - nodepos/2;
        std::vector<uint> curr_level = levels.at(level);
        uint mask = bits.at(pos);
        uint num = (levels.at(level)).at(0) & mask;
        uint dir = rank(num);
        
        if(dir == 0) {

            std::cout << "venstre" << std::endl;;
            return followball(level+1, nodepos, nodepos + pos - irank, amount/2);

        } else if(dir == 1) {

            std::cout << "højre" << std::endl;
            return followball(level+1, nodepos + amount/2, nodepos + amount/2 + irank, amount/2);

        } else {

            std::cout << "error" << std::endl;

        }
    } 

    return balls.at(nodepos);
    
}



// Generates $amount$ of points with unique x-coordinates and unique y-coordinates
Ort::Ort(int amount) {

    std::vector<int> x(amount);
    std::vector<int> y(amount);

    int n {0};
    std::generate(std::begin(x), std::end(x), [&]{ return ++n;});
    std::copy(std::begin(x), std::end(x), std::begin(y));
    
    std::random_device rd;
    std::mt19937 g(rd());
 
    std::shuffle(std::begin(x), std::end(x), g);
    std::shuffle(std::begin(y), std::end(y), g);

    std::vector<Point> points;
    for(int i = 0; i < x.size(); ++i) {
        points.push_back({x[i], y[i]});
    }

    std::sort(std::begin(points), std::end(points), sortpointy);

    std::cout << points << std::endl;

    std::vector<Point> cpoints(amount);
    std::copy(std::begin(points), std::end(points), std::begin(cpoints));

    // Correct
    std::nth_element(std::begin(cpoints), std::begin(cpoints) + cpoints.size()/2, std::end(cpoints), sortpointx);


    uint bit = 1;
    for(int i = 0; i < 32; ++i) {
        bits.push_back(bit);
        bit = bit << 1;
    }

    populateList();

    std::reverse(std::begin(bits), std::end(bits));

    //std::cout << bits << std::endl;

    std::vector<std::vector<uint>> vs(std::log2(amount), std::vector<uint>(std::ceil(float(amount)/32), 0));
    levels = vs;
    std::vector<Point> ps(amount);
    balls = ps;
    
    divide(0,0,points);

    //std::cout << levels << std::endl;
    outputLevels();
    //std::cout << balls << std::endl;


    std::vector<std::vector<uint>> vvs(std::log2(amount), std::vector<uint>());
    ranks = vvs;
    // Create the rank lists
    for(int i = 0; i < levels.size(); ++i) {

        uint sum = 0;
        (ranks.at(i)).push_back(sum);
        for(int j = 0; j < (levels.at(i)).size(); ++j) {
            sum += rank((levels.at(i)).at(j));
            (ranks.at(i)).push_back(sum);
        }
    }


    std::cout << findRank(0, 0, 5) << std::endl;
    std::cout << followball(0,0,3,8) << std::endl;


}

void
Ort::setBit(int level, int pos, int value) {
    // TODO: Tjek om den er sat
    if(value != 0) {
        int pos_i = pos/32;
        int pos_a = pos%32;
        (levels.at(level)).at(pos_i) += bits.at(pos_a);

    }
}

void
Ort::outputLevels() {
    for(const auto& vs : levels) {
        for(const auto& v : vs) {
            std::bitset<32> bb(v);
            std::cout << bb.to_string().substr(0,8);
        }
        std::cout << std::endl;
    }
}

void
Ort::divide(int level, int pos, std::vector<Point> points) {

    if(points.size() > 1) {

        // Find the median using nth_element
        std::vector<Point> temp(points.size());
        std::copy(std::begin(points), std::end(points), std::begin(temp));
        std::nth_element(std::begin(temp), std::begin(temp) + temp.size()/2, std::end(temp), sortpointx);

        int median = (temp[temp.size()/2]).x;

        //std::cout << "MEDIAN: " << median << std::endl;
        std::vector<Point> left, right;

        for(int i = 0; i < points.size(); ++i) {
            if((points.at(i)).x < median) {
                left.push_back(points.at(i));
            } else {
                right.push_back(points.at(i));
                setBit(level, pos+i, 1);
            }
        }

        divide(level+1,pos,left);
        divide(level+1, pos+points.size()/2,right);


    } else {
        //std::cout << level << " - " << pos << " - " << points.at(0) << std::endl;
        balls.at(pos) = points.at(0);
    }

}

