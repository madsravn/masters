#include <random>
#include <algorithm>
#include "Data.hpp"


std::vector<Point>
Data::generate(int amount) {
    int n{0};
    std::vector<int> x(amount);
    std::vector<int> y(amount);

    std::generate(std::begin(x), std::end(x), [&] { return ++n;});
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



