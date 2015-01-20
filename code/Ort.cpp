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

    //std::cout << cpoints << std::endl;

    uint bit = 1;
    for(int i = 0; i < 32; ++i) {
        bits.push_back(bit);
        bit = bit << 1;
    }
    std::reverse(std::begin(bits), std::end(bits));
    divide(0,5,points);

}


// TODO: NU KENDER JEG LEVEL, SIZE OF POINTS OG POSITION.
// NU KAN BIT VEKTOREN NEMT LAVES

void
Ort::divide(int level, int pos, std::vector<Point> points) {
    if(points.size() > 1) {
        std::vector<Point> temp(points.size());
        std::copy(std::begin(points), std::end(points), std::begin(temp));
        std::nth_element(std::begin(temp), std::begin(temp) + temp.size()/2, std::end(temp), sortpointx);
        int median = (temp[temp.size()/2]).x;
        std::cout << "MEDIAN: " << median << std::endl;
        std::vector<Point> left, right;
        for(const auto& e : points) {
            if(e.x < median) {
                left.push_back(e);
            } else {
                right.push_back(e);
            }
        }
        divide(level,2,left);
        divide(level+points.size()/2,2,right);
        std::cout << "level: " << level << "LEFT: " << left << std::endl;
        std::cout << "level: " << level+1 << "RIGHT: " << right << std::endl;

    } else {
        std::cout << level << " - " << points.at(0) << std::endl;
    }

}

