#include "Ort.hpp"
#include <iostream>

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
    os << "(" << p.x << ", " << p.y << ")" << std::endl;
    return os;
}

// Generates $amount$ of points with unique x-coordinates and unique y-coordinates
Ort::Ort(int amount) {
    std::vector<int> x(amount);
    std::vector<int> y(amount);
    int n {0};
    std::generate(std::begin(x), std::end(x), [&]{ return ++n;});
    std::copy(std::begin(x), std::end(x), std::begin(y));

    std::cout << x << std::endl;
    std::cout << y << std::endl;
    
    std::random_device rd;
    std::mt19937 g(rd());
 
    std::shuffle(std::begin(x), std::end(x), g);
    std::shuffle(std::begin(y), std::end(y), g);

    std::vector<Point> points;
    for(int i = 0; i < x.size(); ++i) {
        points.push_back({x[i], y[i]});
    }

    std::cout << points << std::endl;

}



