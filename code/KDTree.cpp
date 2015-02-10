#include "KDTree.hpp"

KDTree::KDTree(int amount) {
    debug = false;
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
    //std::cout << points << std::endl;

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

void
KDTree::saveState(Region query) {
    Data::saveState(points, query);
}

void
KDTree::loadState(std::string filename) {
    auto state = Data::loadState(filename);
    points = std::get<0>(state);
    Region query = std::get<1>(state);
    createRegion();
    debug = false;
    std::cout << points << std::endl;
    std::cout << "The query was " << query << std::endl;
    std::cout << search(query) << std::endl;
    std::cout << actualSearch(query) << std::endl;
}



std::vector<Point>
KDTree::search(Region query) {
    return search(region, query, 0, points.size(), 0);
}

std::vector<Point>
KDTree::search(Region reg, Region query, int start, int size, int level) {

    std::vector<Point> ret;
    if(size > 0) {
        std::vector<Point> comp(std::begin(points) + start, std::begin(points) + start + size);
        std::cout << std::endl << comp << std::endl;
        std::cout << "Should all be in : " << reg << std::endl;
        bool t = true;
        for(const auto& p : comp) {
            t = t && (reg.ll.x <= p.x && reg.ll.y <= p.y && p.x <= reg.ur.x && p.y <= reg.ur.y);
        }
        if(!t) {
            std::cout << "DET ER LØGN" << std::endl;
        }
        std::cout << std::endl;

    }
    if(size > 1) {
        if(query.ll.x <= reg.ll.x && query.ll.y <= reg.ll.y && reg.ur.x <= query.ur.x && reg.ur.y <= query.ur.y) {
            std::vector<Point> complete(std::begin(points) + start, std::begin(points) + start + size);
            if(debug) {
                std::cout << std::endl << "COMPLETE REGION INCLUDED: " << complete << std::endl;
                std::cout << "Region is: " << reg << std::endl;
                std::cout << "Query is: " << query << std::endl << std::endl;
            }
            return complete;
        }

        int middle = std::ceil(float(size)/2) - 1; // The middle point belongs to the left region
        Point div = points.at(start+middle);
        if(debug) {
            std::cout << std::endl << "Region is " << reg << std::endl;
            std::cout << "diving point is: " << div << std::endl;
            std::vector<Point> entire(std::begin(points) + start, std::begin(points) + start + size);
            std::cout << "Entire vector is: " << entire << std::endl;
            std::cout << "We are dividing on the " << (level%2 == 0 ? "x" : "y") << " axis" << std::endl;

        }
        if(level%2 == 0) {
            Region left = limitRegion(reg, div, SIDE::RIGHT);
            Region right = limitRegion(reg, div, SIDE::LEFT);

            if(debug) {
                std::cout << "Going left" << std::endl;
                std::cout << reg << " ==> " << left << std::endl;
            }
            std::vector<Point> l = search(left, query, start, middle+1, level+1);

            if(debug) {
                std::cout << "Going right" << std::endl;
                std::cout << reg << " ==> " << right << std::endl;
            }
 
            std::vector<Point> r = search(right, query, start+middle+1, size-middle-1, level+1);

            ret.insert(std::end(ret), std::begin(l), std::end(l));
            ret.insert(std::end(ret), std::begin(r), std::end(r));
        } else {
            Region down = limitRegion(reg, div, SIDE::UP);
            Region up = limitRegion(reg, div, SIDE::DOWN);
            if(debug) {
                std::cout << "Going down" << std::endl;
                std::cout << reg << " ==> " << down << std::endl;
            }
 

            std::vector<Point> d = search(down, query, start, middle+1, level+1);
            if(debug) {
                std::cout << "Going up" << std::endl;
                std::cout << reg << " ==> " << up << std::endl;
            }
 

            std::vector<Point> u = search(up, query, start+middle+1, size-middle-1, level+1);

            ret.insert(std::end(ret), std::begin(d), std::end(d));
            ret.insert(std::end(ret), std::begin(u), std::end(u));
        }

    }

    if(size == 1) {
        Point p = points.at(start);
        if(query.ll.x <= p.x && query.ll.y <= p.y && p.x <= query.ur.x && p.y <= query.ur.y) {
            if(debug) {
                std::cout << std::endl << "SINGLE POINT included: " << p << std::endl << std::endl;
            }
            ret.push_back(p);
        }
    }
    return ret;

}

std::vector<Point>
KDTree::actualSearch(Region query) {
    std::vector<Point> ret;
    for(const auto& p : points) {
        if(query.ll.x <= p.x && query.ll.y <= p.y && p.x <= query.ur.x && p.y <= query.ur.y) {
            ret.push_back(p);
        }
    }
    return ret;
}

// Trimming a region from a given side
Region 
KDTree::limitRegion(Region reg, Point p, SIDE side) {
    if(side == SIDE::LEFT) {
        reg.ll.x = p.x + 1;
    }
    if(side == SIDE::RIGHT) {
        reg.ur.x = p.x;
    }
    if(side == SIDE::UP) {
        reg.ur.y = p.y;
    }
    if(side == SIDE::DOWN) {
        reg.ll.y = p.y + 1;
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
        /*std::cout << std::endl << std::endl << "start: " << start << std::endl;

        std::vector<Point> entire(std::begin(points) + start, std::begin(points) + start + size);
        std::cout << "Entire range: " << entire << std::endl;
        std::vector<Point> left(std::begin(points) + start, std::begin(points)+start+middle);
        std::vector<Point> right(std::begin(points) + start + middle + 1, std::begin(points)+start+size);
        std::cout << "Left side contains: " << left << std::endl;
        std::cout << "Middle is: " << points.at(start+middle) << std::endl;
        std::cout << "Right side contains: " << right << std::endl;*/

        buildTree(start, middle, level+1);
        buildTree(start+middle+1, size-middle-1, level+1);
    }

}




