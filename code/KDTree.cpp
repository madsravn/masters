#include "KDTree.hpp"

KDTree::KDTree(int amount, std::vector<Point> input) {
    debug = false;
    points = input;
    build();


}

void
KDTree::build() {
    buildTree(0, points.size(), 0);
    //std::cout << middles << std::endl;
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
    build();
    debug = false;
    std::cout << points << std::endl;
    std::cout << "The query was " << query << std::endl;
    std::cout << search(query) << std::endl;
    std::cout << actualSearch(query) << std::endl;
}



std::vector<Point>
KDTree::search(Region query) {
    std::vector<Point> temp;
    search(region, query, 0, points.size(), 0);
    results.swap(temp);
    return temp;
}

void
KDTree::search(Region reg, Region query, int from, int to, int level) {

    int size = to-from;
    if(size > 1) {
        if(query.ll.x <= reg.ll.x && query.ll.y <= reg.ll.y && reg.ur.x <= query.ur.x && reg.ur.y <= query.ur.y) {
            results.insert(std::end(results), std::begin(points) + from, std::begin(points) + to);
            return;
        }

        int middle = std::ceil(float(size)/2) - 1; // The middle point belongs to the left region
        Point div = points.at(from+middle);
        if(query.ll.x <= div.x && div.x <= query.ur.x && query.ll.y <= div.y && div.y <= query.ur.y) {
            results.push_back(div);
        }

        if(level%2 == 0) {
            Region left = limitRegion(reg, div, SIDE::RIGHT);
            Region right = limitRegion(reg, div, SIDE::LEFT);
            
            
            if(overlap(query, left)) {
                search(left, query, from, from+middle, level+1);
            }
            if(overlap(query, right)) {
                search(right, query, from+middle+1, to, level+1);
            }
            
        } else {
            Region down = limitRegion(reg, div, SIDE::UP);
            Region up = limitRegion(reg, div, SIDE::DOWN);


            if(overlap(query, down)) {
                search(down, query, from, from+middle, level+1);
            }
            if(overlap(query, up)) {
                search(up, query, from+middle+1, to, level+1);
            }

        }

    }

    if(size == 1) {
        Point p = points.at(from);
        if(query.ll.x <= p.x && query.ll.y <= p.y && p.x <= query.ur.x && p.y <= query.ur.y) {
            results.push_back(p);
        }
    }
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
        reg.ll.x = p.x ;
    }
    if(side == SIDE::RIGHT) {
        reg.ur.x = p.x;
    }
    if(side == SIDE::UP) {
        reg.ur.y = p.y;
    }
    if(side == SIDE::DOWN) {
        reg.ll.y = p.y ;
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

        /*std::vector<Point> l(std::begin(points) + start, std::begin(points) + start + middle + 1);
        std::vector<Point> r(std::begin(points) + start+middle+1, std::begin(points) + start+size);
        std::vector<Point> a(std::begin(points) + start, std::begin(points)+start+size);
        std::cout << std::endl << std::endl << "left: " << l << std::endl;
        std::cout << "right: " << r << std::endl;
        std::cout << "all: " << a << std::endl;
        std::cout << "level: " << level << std::endl;*/
        
        buildTree(start, middle, level+1);
        buildTree(start+middle+1, size-middle-1, level+1);
    }

}




