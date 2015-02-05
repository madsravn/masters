#include "KDTree.hpp"

KDTree::KDTree(int amount) {
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

    // Sort the points by their x-coordinates
    std::sort(std::begin(points), std::end(points), sortpointx);

}

void
KDTree::build() {
    buildTree(0, points.size(), 0);

}

void
KDTree::buildTree(int start, int end, int level) {

}




