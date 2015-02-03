#include "Ort.hpp"
#include <iostream>
#include <bitset>

//TODO: MAKE SURE EVERYTHING IS ONLY AS BIG AS IT NEEDS TO BE!


uint 
Ort::rank(uint number) {
    uint first = number >> 16;
    uint last = number & 65'535;

    uint answer = inttobin[first] + inttobin[last];
    return answer;
}

void
Ort::intMasks() {
    for(int range = 0; range < 32; ++range) {
        uint result = 0;
        // Why does the binary trick of ( 1 << k) - 1 not work here? 
        // Fordi 32-0 = 32 ikke skal give noget stort, men bare en 0-maske.
        for(int i = 0; i < 32-range; ++i) {
            result = result << 1;
            result += 1;
        }
        result = ~result;
        masks.push_back(result);
    }
}
     

uint
Ort::makemask(uint range) {

    return masks.at(range);

}

uint
Ort::findRank(int level, int nodepos, int pos) {

    // Simple version expanded
    int pos_i = pos/32;
    int pos_a = pos % 32;
    uint mask = makemask(pos_a);
    uint t = (levels.at(level)).at(pos_i);
    t = t & mask;
    uint resultrank = (ranks.at(level)).at(pos_i) + rank(t);

    return resultrank;
}

void
Ort::intIntegerToBinary() {
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
        uint mask = bits.at(pos%32);
        uint num = (levels.at(level)).at(pos/32) & mask;
        uint dir = rank(num);
        
        if(dir == 0) {

            //std::cout << "venstre" << std::endl;;
            return followball(level+1, nodepos, pos - irank, amount/2);

        } else if(dir == 1) {

            //std::cout << "højre" << std::endl;
            return followball(level+1, nodepos + amount/2, nodepos + amount/2 + irank, amount/2);

        } else {

            std::cout << "error" << std::endl;

        }
    } 

    return balls.at(nodepos);
    
}

void
Ort::initializeStuff() {

    // Initialize bits to number for getting x'th bit
    uint bit = 1;
    for(int i = 0; i < 32; ++i) {
        bits.push_back(bit);
        bit = bit << 1;
    }

    std::reverse(std::begin(bits), std::end(bits));

    // Initialize list so we can count the rank of a given number
    intIntegerToBinary();
    // Initialize the list so we get the x first bits in a number.
    // 32 == 0 because we are using rank sums
    intMasks();

}

void
Ort::initializeBinarySearches() {
    for(const auto& e : balls) {
        xb.push_back(e.x);
        yb.push_back(e.y);
    }

    std::sort(std::begin(xb), std::end(xb));
    std::sort(std::begin(yb), std::end(yb));
}


// Generates $amount$ of points with unique x-coordinates and unique y-coordinates
Ort::Ort(int amount) : balls(amount), levels(std::log2(amount), std::vector<uint>(std::ceil(float(amount)/32), 0)) {


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

    // Remember to call this before divide()
    initializeStuff();

    
    // Distribute the balls using the ball-inheritance
    divide(0,0,points);

    // Output the levels so we can see how the ball-inheritance has distributed
    //outputLevels();


    // Now let's precalculate the rank sums
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


    // Testing that all balls falls to their correct leaf
    bool all = true;
    for(int i = 0; i < points.size(); ++i) {
        /*std::cout << "It is: " << followball(0,0,i,points.size()) << std::endl;
        std::cout << "Should be: " << points.at(i) << std::endl;*/
        all = all & (points.at(i) == followball(0,0,i,points.size()));
    }



    std::cout << points.at(10) << std::endl;
    std::cout << followball(0,0,10,points.size()) << std::endl;
    std::cout << "ALL WAS " << all << std::endl;

    initializeBinarySearches();
}

std::vector<Point>
Ort::easyQuery(Point lowerleft, Point upperright) {
    
    auto lx = std::lower_bound(std::begin(xb), std::end(xb), lowerleft.x);
    auto ux = std::upper_bound(std::begin(xb), std::end(xb), upperright.x);
    int lx_index = std::distance(std::begin(xb), lx);
    int ux_index = std::distance(std::begin(xb), ux) - 1;

    std::cout << "lx_index: " << lx_index << std::endl;
    std::cout << "ux_index: " << ux_index << std::endl;

    auto ly = std::lower_bound(std::begin(yb), std::end(yb), lowerleft.y);
    auto uy = std::upper_bound(std::begin(yb), std::end(yb), upperright.y);
    int ly_index = std::distance(std::begin(yb), ly);
    //TODO: HVORFOR SKAL DEN HER IKKE HAVE - 1 ? 
    int uy_index = std::distance(std::begin(yb), uy);

    std::cout << "ly_index: " << ly_index << std::endl;
    std::cout << "uy_index: " << uy_index << std::endl;
    
    Point x{lowerleft.y, upperright.y};
    search = x;

    // TODO: Find a better way to express amount of balls
    std::vector<Point> results = FindPoints(lx_index, ux_index, ly_index, uy_index, 32-std::ceil(std::log2(balls.size())), 0, balls.size(), 0);
    std::cout << results << std::endl;
    bool all = true;
    for(const auto& e : results) {
        all = all & (lowerleft.x <= e.x && e.x <= upperright.x && lowerleft.y <= e.y && e.y <= upperright.y);
    }
    std::cout << "AGAIN, ALL WAS " << all << " and the size is: " << results.size() << std::endl;

    return results;
}

std::vector<Point>
Ort::actualQuery(Point lowerleft, Point upperright) {
    std::vector<Point> outside;
    std::vector<Point> inside;
    for(const auto& e : balls) {
        if(e.x < lowerleft.x || upperright.x < e.x || e.y < lowerleft.y || upperright.y < e.y) {
            outside.push_back(e);
        } else {
            inside.push_back(e);
        }
    }
    return inside;
}
 


// TODO: Tjek om den er sat
void
Ort::setBit(int level, int pos, int value) {
    if(value != 0) {
        int pos_i = pos/32;
        int pos_a = pos%32;
        (levels.at(level)).at(pos_i) += bits.at(pos_a);

    }
}

std::vector<Point>
Ort::addAll(int nodepos, int lrank, int urank, int level, int amount) {
    std::vector<Point> ret;

    for(int i = 0; i < amount; ++i) {
        ret.push_back(followball(level, nodepos, nodepos+i, amount));
    }
    std::vector<Point> nonret;
    for(int i = lrank-nodepos; i < urank-nodepos; ++i) {
        nonret.push_back(followball(level, nodepos, nodepos+i, amount));
    }
    //std::cout << std::endl << "addAll ======>" << std::endl;
    //std::cout << "lrank = " << lrank << " og urank = " << urank << " og amount = " << amount << std::endl;
    //std::cout << "nodepos = " << nodepos << std::endl;
    //std::cout << "ret = " << ret << std::endl;
    //std::cout << "nonret = " << nonret << std::endl;
        

    return nonret;

}

// Jeg ved præcis hvor mange punkter jeg skal melde tilbage med 
// så jeg kan lave en vektor der er af den størrelse.
// DIRECTION d indicates which subtree of the LCA we are walking in
std::vector<Point>
Ort::followPoint(int child, int lyrank, int uyrank, int bit, int nodepos, int amount, DIRECTION d, int level) {

    if(amount < 1) {
        std::cout << "FEJL i followPoint" << std::endl;
    }
    
    //std::cout << "Hver for sig" << std::endl;

    std::vector<Point> p;
    if(amount > 1) {
        uint num = bits.at(bit);
        uint dir = child & num;
        uint lrank = findRank(level, nodepos, lyrank) - nodepos/2;
        uint urank = findRank(level, nodepos, uyrank) - nodepos/2;


        if(dir == 0) {
            if(d == LEFT) {
                // We now add all the points from the right subtree
                //std::cout << "Vi tager hele højre undertræ" << std::endl;
                std::vector<Point> all = addAll(nodepos + amount/2, nodepos + amount/2+lrank, nodepos + amount/2 + urank, level+1, amount/2);
                p.insert(std::end(p), std::begin(all), std::end(all));

            }

            std::vector<Point> left = followPoint(child, lyrank-lrank, uyrank-urank, bit+1, nodepos, amount/2, d, level+1);
            p.insert(std::end(p), std::begin(left), std::end(left));
            return p;

        } else {
            if(d == RIGHT) {
                // We now add all the points from the left subtree
                //std::cout << "Vi tager hele venstre undertræ" << std::endl;
                std::vector<Point> all = addAll(nodepos, lyrank-lrank, uyrank-urank, level+1, amount/2);
                p.insert(std::end(p), std::begin(all), std::end(all));

            }

            std::vector<Point> right = followPoint(child, nodepos+amount/2 + lrank, nodepos + amount/2 + urank, bit+1, nodepos+amount/2, amount/2, d, level+1);
            p.insert(std::end(p), std::begin(right), std::end(right));
            return p;

        }

    }

    // There might only be one point in amount
    Point last = balls.at(nodepos);
    if(search.x <= last.y && last.y <= search.y) { 
        p.push_back(balls.at(nodepos));
    }
    return p;

}

std::vector<Point> 
Ort::FindPoints(int leftchild, int rightchild, int ly_index, int uy_index, int bit, int nodepos, int amount, int level) {
    // TODO: What to do if the number of balls are greater than 2^32? 
    // Lav en vektor med større.
    uint num = bits.at(bit);
    uint left = leftchild & num;
    uint right = rightchild & num;

    uint lrank = findRank(level, nodepos, ly_index) - nodepos/2;
    uint urank = findRank(level, nodepos, uy_index) - nodepos/2;
    //std::cout << std::endl << "FINDPOINTS ======> " << std::endl;
    //std::cout << "ly_rank = " << ly_index << " og lrank = " << lrank << std::endl;
    //std::cout << "uy_rank = " << uy_index << " og urank = " << urank << std::endl;


    if(amount < 1) {
        std::cout << "FEJL i FindPoints" << std::endl;
    }

    // Are they going to the same child? 
    if(left == right) {
        //std::cout << "Sammen" << std::endl;
        if(left == 0) {
            return FindPoints(leftchild, rightchild, ly_index-lrank, uy_index-urank, bit+1, nodepos, amount/2, level+1);
        } else {
            return FindPoints(leftchild, rightchild, nodepos + amount/2 + lrank, nodepos + amount/2 + urank, bit+1, nodepos+amount/2, amount/2, level+1);
        }
    }
    std::vector<Point> p;
    std::vector<Point> leftvec = followPoint(leftchild,ly_index-lrank, uy_index-urank, bit+1, nodepos, amount/2, LEFT, level+1);
    std::vector<Point> rightvec = followPoint(rightchild,nodepos+amount/2+lrank,nodepos+amount/2+urank, bit+1, nodepos+amount/2, amount/2, RIGHT, level+1);
    p.insert(std::end(p), std::begin(leftvec), std::end(leftvec));
    p.insert(std::end(p), std::begin(rightvec), std::end(rightvec));

    return p;
}


//TODO: Pænere output
void
Ort::outputLevels() {
    for(const auto& vs : levels) {
        for(const auto& v : vs) {
            std::bitset<32> bb(v);
            if(balls.size() < 32) {
                std::cout << bb.to_string().substr(0,balls.size());
            } else {
                std::cout << bb.to_string();
            }
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

