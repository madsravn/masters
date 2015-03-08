#ifndef POINT_HPP_
#define POINT_HPP_
#include <iostream>

struct Point {
    int x, y;
    const bool operator==(Point a) const {
       if (a.x==x && a.y== y)
          return true;
       else
          return false;
    }
};

struct {
    bool operator()(Point a, Point b) {   
        return a.y < b.y;
    }   
} sortpointy;

struct {
    bool operator()(Point a, Point b) {
        return a.x < b.x;
    }
} sortpointx;

struct Region {
    Point ll; // lower left
    Point ur; // upper right
};




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



#endif
