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

    for(int i = 0; i < x.size(); ++i) {
        points.push_back({x[i], y[i]});
    }

    // Sort the points by their x-coordinates
    std::sort(std::begin(points), std::end(points), sortpointx);


}

void
KDTree::build() {
    buildTree(0, points.size(), 0);
    createRegion();
    std::cout << points << std::endl;

}

void
KDTree::createRegion() {
    if(!points.empty()){ 
        std::vector<Point> cpy(points);
        Point smallest;
        Point biggest;
        std::sort(std::begin(cpy), std::end(cpy), sortpointx);
        smallest.x = cpy.front().x;
        biggest.x = cpy.back().x;

        std::sort(std::begin(cpy), std::end(cpy), sortpointy);
        smallest.y = cpy.front().y;
        biggest.y = cpy.back().y;

        region.ll = smallest;
        region.ur = biggest;
    }
}

std::vector<Point>
KDTree::search(Region query) {
    return search(region, query);
}

std::vector<Point>
KDTree::search(Region reg, Region query) {

    std::cout << query << std::endl;
    std::cout << reg << std::endl;
    

    // TODO : DET ER HER DET SKER!!!


    if(overlap(query, reg)) {
        std::cout << "overlap" << std::endl;
    } else {
        std::cout << "NO overlap" << std::endl;
    }
    return points;

}

// Trimming a region from a given side
Region limitRegion(Region reg, Point p, SIDE side) {
    if(side == SIDE::LEFT) {
        reg.ll.x = p.x;
    }
    if(side == SIDE::RIGHT) {
        reg.ur.x = p.x;
    }
    if(side == SIDE::UP) {
        reg.ur.y = p.y;
    }
    if(side == SIDE::DOWN) {
        reg.ll.y = p.y;
    }
    return reg;
}

bool
KDTree::overlap(Region r1, Region r2) {
    bool overlap = (r1.ll.x < r2.ur.x) && 
        (r1.ur.x > r2.ll.x) &&
        (r1.ll.y < r2.ur.y) && 
        (r1.ur.y > r2.ll.y);
    return overlap;
}



void
KDTree::buildTree(int start, int size, int level) {

    if(size > 1) {
        if(level%2 == 0) {
            std::sort(std::begin(points) + start, std::begin(points) + start + size, sortpointx);
        } else {
            std::sort(std::begin(points) + start, std::begin(points) + start + size, sortpointy);
        }

        int middle = std::ceil(float(size)/2) - 1;
        std::cout << std::endl << std::endl << "start: " << start << std::endl;

        std::vector<Point> entire(std::begin(points) + start, std::begin(points) + start + size);
        std::cout << "Entire range: " << entire << std::endl;
        std::vector<Point> left(std::begin(points) + start, std::begin(points)+start+middle);
        std::vector<Point> right(std::begin(points) + start + middle + 1, std::begin(points)+start+size);
        std::cout << "Left side contains: " << left << std::endl;
        std::cout << "Middle is: " << points.at(start+middle) << std::endl;
        std::cout << "Right side contains: " << right << std::endl;

        buildTree(start, middle,level+1);
        buildTree(start+middle+1, size-middle-1, level+1);
    }

}




