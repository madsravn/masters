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

// <do we jump, character, rank, alphabet size>
qreturn
Ort::bigJump(int level, int pos) {

    // || type == 1
    if(linear.at(level).jump == 1) {
        //std::cout << "Small steps" << std::endl;
        return {0,1,1,1};
    }

    /*
    // Skift mellem at bruge jumps eller notsolinear
    if(type == 2) {
        //int character = jumps.at(level).targets.at(pos);
        //int rank = jumps.at(level).entries.at(pos);
        //int size = jumps.at(level).jump;
        int character = notsolinear.at(level).entries.at(pos);
        int size = notsolinear.at(level).jump;
        int end = notsolinear.at(level).end;
        if(end == 0) {

            int major_size = pow(2, size);
            int div = notsolinear.at(level).div;
            int major = notsolinear.at(level).major.at((pos/div)*major_size + character);
            int minor =  notsolinear.at(level).minor.at(pos);
            int rank = major + minor;
        
            return {1, character, rank, size};
        }
        return {1,character, 0, size};
    }
    
    
    // New type with a little garbage at the end of every uint
    if(type == 4) {
        int character = Data::findInt2(lineargarb.at(level).entries, lineargarb.at(level).entrieskey, pos);
        int size = lineargarb.at(level).jump;
        int end = lineargarb.at(level).end;

        if(end == 0) {

            int major_size = pow(2, size);
            int div = lineargarb.at(level).div;
            int major = Data::findInt2(lineargarb.at(level).major, lineargarb.at(level).majorkey, (pos/div)*major_size + character);
            int minor =  Data::findInt2(lineargarb.at(level).minor, lineargarb.at(level).minorkey, pos);
            int rank = major + minor;
        
            return {1, character, rank, size};
        }

        return {1,character, 0, size};
    }*/

    // ELSE TYPE == 3

    int character = Data::findInt(linear.at(level).entries, linear.at(level).entrieskey, pos);
    int size = linear.at(level).jump;
    int end = linear.at(level).end;

    if(end == 0) {

        int major_size = pow(2, size);
        int div = linear.at(level).div;
        int major = Data::findInt(linear.at(level).major, linear.at(level).majorkey, (pos/div)*major_size + character);
        int minor =  Data::findInt(linear.at(level).minor, linear.at(level).minorkey, pos);
        int rank = major + minor;
        
        return {1, character, rank, size};
    }

    return {1,character, 0, size};

}

std::vector<Point> 
Ort::Depthsearch(Region reg, int& jumpcount, int& maxdepth, int& startlevel) {
    startlevel = 0;
    jumpcount = 0;
    maxdepth = 0;
    //type = t;
    //std::cout << "Searching with type = " << type << std::endl;
    return DeptheasyQuery(reg.ll, reg.ur, jumpcount, maxdepth, startlevel);
}

std::vector<Point> 
Ort::search(Region reg) {
    //int jumpcount = 0;
    //int maxdepth = 0;
    //type = t;
    //std::cout << "Searching with type = " << type << std::endl;
    return easyQuery(reg.ll, reg.ur); //, jumpcount, maxdepth);
}



// Will return the size in the amount of 32-bits containers used (int, uint)
uint
Ort::size(int t) const {

    
    uint storage = 0;

    for(const auto&e : levels) {
        storage += e.size();
    }

    storage += 2*balls.size();
    storage += bits.size();
    storage += xb.size() + yb.size();
    storage += masks.size();
    for(const auto& e : ranks) {
        storage += e.size();
    }
    storage += inttobin.size();


    // No big jumps
    if(t == 1) {
        return storage;
    }

    // One of the expensive big jumps
    /*if(t == 2) {
        for(const auto& e : notsolinear) {
            storage += 4; // jump, majorkey, minorkey, div
            storage += e.major.size();
            storage += e.minor.size();
            storage += e.entries.size();
        }
    }*/

    // The packed big jumps
    if(t == 3) {
        for(const auto& e : linear) {
            storage += 4; // jump, majorkey, minorkey, div
            storage += e.major.size();
            storage += e.minor.size();
            storage += e.entries.size();
        }
    }

    return storage;
}

uint
Ort::findRank(int level, int nodepos, int pos) {

    // Simple version expanded
    int pos_i = pos/32;
    int pos_a = pos % 32;
    uint mask = makemask(pos_a);
    if(pos_i == levels.at(level).size()) {
        return (ranks.at(level)).at(pos_i);
    }

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

// Will return values between 0 and 2^(stop-start) range
int
Ort::convertRangeToInt(std::vector<uint> vec, int start, int stop) {
    int ret = vec.at(start);
    for(int i = start+1; i < stop; ++i) {
        ret = ret << 1;
        ret += vec.at(i);
    }
    return ret;
}


std::vector<int>
Ort::createLinkedList(int size) {
    std::vector<int> jumplist(size, 1);
    // Calculate the budget.
    // TODO!
    //
    // Another idea could be to find the middle level and let that jump to the end
    // All levels above it considers the middle as the actual goal. Then we have split it in half
    
    int B = 2;
    for(int i = 1; i < std::ceil(std::log2(size+1)); ++i) {
        int skiplevels = pow(B, i);
        for(int j = skiplevels-1; j < size; j+= skiplevels) {
            jumplist.at(j) = skiplevels;
        }
    }
        
    
    std::reverse(std::begin(jumplist), std::end(jumplist));

    
    for(int i = 0; i < jumplist.size(); ++i) {
        // Is the jump close to just hitting the end? Then let it
        if(i+jumplist.at(i) > jumplist.size() - 4) {
            // TODO: Better semantics
            jumplist.at(i) = jumplist.size()+3;
        }
    }
    //std::cout << jumplist << std::endl;
    return jumplist;
}


// TODO: REFACTOR!
void
Ort::generateJumps() {
    
    for(current = 0; current < balls.size(); ++current) {
        linkedlists.push_back(std::vector<uint>{});
        buildfollowball(0,0,current,balls.size());

    }

    if(linkedlists.at(0).size() != twodarray.size() || twodarray.size() != levels.size()) {
        std::cout << "Houston, we have a problem" << std::endl;
        std::cout << "linkedlists.at(0).size() = " << linkedlists.at(0).size() << std::endl;
        std::cout << "twodarray.size() = " << twodarray.size() << std::endl;
        std::cout << "levels.size() = " << levels.size() << std::endl;
        return;
    }
    std::vector<int> jumplist = createLinkedList(levels.size());
    
    if(jumplist.size() != levels.size()) {
        std::cout << "Houston, another problem!" << std::endl;
    }


    for(int i = 0; i < levels.size(); i++) {

        int tskiplevels = jumplist.at(i);
        int skiplevels = 1000;
        int end = 0;

        if(i+tskiplevels <= levels.size()) {
            skiplevels = tskiplevels;
        } else {
            skiplevels = levels.size()-i;
        }

        if(i+skiplevels == levels.size()) {
            end = 1;
        }

        //Jumper jump;
        //jump.jump = skiplevels;
        if(skiplevels > 1) {
            std::vector<uint> targets;
            for(int j = 0; j < linkedlists.size(); ++j) {
                std::vector<uint> linkedlist = linkedlists.at(twodarray.at(i).at(j));
                int target = convertRangeToInt(linkedlist, i, i+skiplevels);
                targets.push_back(target);
            }

            //std::cout << "targets: " << targets << std::endl;
            //jump.targets = targets;
            std::vector<uint> alph(pow(2,skiplevels), 0);
            std::vector<uint> entries(targets.size(), 0);

            for(int ent = 0; ent < targets.size(); ++ent) {
                int entry = targets.at(ent);
                entries.at(ent) = alph.at(entry);
                alph.at(entry)++;
            }

            //std::cout << "entries: " << entries << std::endl;
            //jump.entries = entries;
            //jump.end = false;
            //jumps.at(i) = jump;

            // Converting to linear representation
            // TODO : TARGETS OG ENTRIES HEDDER DET FORKERTE. TJEK DATAEN FRA BIGJUMP OG FIND UD AF HVAD DET GØR
            std::vector<std::vector<uint>> majorcheckpoints; //(std::log2(balls.size()) + 2, std::vector<uint>(pow(2,skiplevels), 0));
            std::vector<uint> minor;
            std::vector<uint> seen(pow(2, skiplevels), 0);
            majorcheckpoints.push_back(seen);

            int curr = 0;
            int div = pow(2, skiplevels)*std::log2(balls.size());
            for(int ent = 0; ent < targets.size(); ++ent) {
                if(curr != ent/div) {
                    curr++;
                    majorcheckpoints.push_back(seen);
                }
                uint one = seen.at(targets.at(ent));
                uint two = majorcheckpoints.at(curr).at(targets.at(ent));
                minor.push_back(one - two);
                seen.at(targets.at(ent))++;
            }

            std::vector<uint> major;
            for(const auto& outer : majorcheckpoints) {
                for(const auto& inner : outer) {
                    major.push_back(inner);
                }
            }

            major.shrink_to_fit();
            minor.shrink_to_fit();
            targets.shrink_to_fit();

            //LinearJumper notsolinearjump;
            //notsolinearjump.jump = skiplevels;

            //notsolinearjump.div = div;
            //if(end == 0) {
            //    notsolinearjump.major = major;
            //    notsolinearjump.minor = minor;
            //}
            //notsolinearjump.entries = targets;
            //notsolinearjump.end = end;
            //notsolinear.at(i) = notsolinearjump;


            LinearJumper linearjump;
            linearjump.jump = skiplevels;

            //LinearJumper lineargarbjump;
            //lineargarbjump.jump = skiplevels;

            if(end == 0) {
                auto majorkeyindex = std::max_element(std::begin(major), std::end(major));
                uint majorkey = major.at(std::distance(std::begin(major), majorkeyindex));

                //TODO: LINEAR PLADSFORBRUG: ER MAJORKEY+1 NOK TIL AT FJERNE SPECIALCASE?

                // TODO: Lav anden håndtering ved sådan et special-case. Kun '0'-entries kommer til at tage 2 bits plads
                // Når skiplevels bliver stor nok er der kun éen major, den første som holder 0'er
                if(majorkey == 0) {
                    majorkey = 1;
                }

                linearjump.majorkey = std::ceil(std::log2(majorkey+1));
                linearjump.major = Data::packBits(major, linearjump.majorkey);

                //lineargarbjump.majorkey = std::ceil(std::log2(majorkey+1));
                //lineargarbjump.major = Data::packBits2(major, lineargarbjump.majorkey);


                auto minorkeyindex = std::max_element(std::begin(minor), std::end(minor));
                uint minorkey = minor.at(std::distance(std::begin(minor), minorkeyindex));

                if(minorkey == 0) {
                    minorkey = 1;
                }

                linearjump.minorkey = std::ceil(std::log2(minorkey+1));
                linearjump.minor = Data::packBits(minor, linearjump.minorkey);

                //lineargarbjump.minorkey = std::ceil(std::log2(minorkey+1));
                //lineargarbjump.minor = Data::packBits2(minor, lineargarbjump.minorkey);

                linearjump.div = div;
                linearjump.major.shrink_to_fit();
                linearjump.minor.shrink_to_fit();

                //lineargarbjump.div = div;
                //lineargarbjump.major.shrink_to_fit();
                //lineargarbjump.minor.shrink_to_fit();
            }

            auto entrieskeyindex = std::max_element(std::begin(targets), std::end(targets));
            uint entrieskey = targets.at(std::distance(std::begin(targets), entrieskeyindex));

            if(entrieskey == 0) {
                entrieskey = 1;
            }

            linearjump.entrieskey = std::ceil(std::log2(entrieskey+1));
            linearjump.entries = Data::packBits(targets, linearjump.entrieskey);

            //lineargarbjump.entrieskey = std::ceil(std::log2(entrieskey+1));
            //lineargarbjump.entries = Data::packBits2(targets, lineargarbjump.entrieskey);


            linearjump.entries.shrink_to_fit();
            linearjump.end = end;
            linear.at(i) = linearjump;

            //lineargarbjump.entries.shrink_to_fit();
            //lineargarbjump.end = end;
            //lineargarb.at(i) = lineargarbjump;
        }
    }

}


Point
Ort::buildfollowball(int level, int nodepos, int pos, int amount) {
    if(amount > 1) {
    
        // TODO: Refactor this piece of code
        uint irank = findRank(level, nodepos, pos) - nodepos/2;
        uint mask = bits.at(pos%32);
        uint num = (levels.at(level)).at(pos/32) & mask;
        uint dir = rank(num);

        
        if(dir == 0) {

            (linkedlists.at(current)).push_back(0);
            (twodarray.at(level)).at(pos) = current;
            
            return buildfollowball(level+1, nodepos, pos - irank, amount/2);

        } else if(dir == 1) {

            (linkedlists.at(current)).push_back(1);
            (twodarray.at(level)).at(pos) = current;

            return buildfollowball(level+1, nodepos + amount/2, nodepos + amount/2 + irank, amount/2);

        } else {

            std::cout << "error" << std::endl;

        }
    } 

    // Nodepos and pos should be equal now - since amount == 1
    return balls.at(nodepos);
}



// position beskriver den vi kigger på
// nodepos beskriver hvor den node vi kigger på starter henne sådan vi kan regne ud hvor mange 1'ere der kommer før den
// level beskriver level. 
// amount beskriver hvor mange der er i hver node
Point
Ort::followball(int level, int nodepos, int pos, int amount) {
    if(amount > 1) {
    
        qreturn big = bigJump(level, pos);
        if(big.jump == 1) {
            //std::cout << std::endl << "Using big jump" << std::endl;
            int character = big.character;
            int rank = big.rank;
            int jumps = big.size; 
            int size = pow(2, jumps);
            return followball(level+jumps, nodepos + (amount*character)/size, (character*amount)/size + nodepos + rank - nodepos/size, amount/size);

        }

        uint irank = findRank(level, nodepos, pos) - nodepos/2;
        uint mask = bits.at(pos%32);
        uint num = (levels.at(level)).at(pos/32) & mask;
        uint dir = rank(num);

        
        if(dir == 0) {

            return followball(level+1, nodepos, pos - irank, amount/2);

        } else if(dir == 1) {

            return followball(level+1, nodepos + amount/2, nodepos + amount/2 + irank, amount/2);

        } else {

            std::cout << "error" << std::endl;

        }
    } 

    // Nodepos and pos should be equal now - since amount == 1
    return balls.at(nodepos);
    
}

Point
Ort::Depthwhilefollowball(int level, int nodepos, int pos, int amount) {


    int tempjumps = 0;
    while(amount > 1) {
        ++internaljumpcount;
        ++tempjumps;
        qreturn big = bigJump(level, pos);
        if(big.jump == 1) {
            int size = pow(2, big.size);

            level += big.size;
            // If bottom is hit, the (big.rank - nodepos/size) will be 0. Thus we can save away the entire rank storage
            int tlong = (ulon(amount)*ulon(big.character))/size;
            pos = tlong + nodepos + (big.rank - nodepos/size);
            nodepos += tlong;
            amount = amount/size;

        } else {

            uint irank = findRank(level, nodepos, pos) - nodepos/2;
            uint mask = bits.at(pos%32);
            uint num = (levels.at(level)).at(pos/32) & mask;
            uint dir = rank(num);

            
            if(dir == 0) {

                ++level;
                pos = pos - irank;
                amount = amount/2;

            } else if(dir == 1) {

                ++level;
                pos = nodepos + amount/2 + irank;
                nodepos += amount/2;
                amount = amount/2;

            } else {

                std::cout << "error" << std::endl;

            }
        }

    }
    if(tempjumps > internalmaxdepth) {
        internalmaxdepth = tempjumps;
    }
    return balls.at(nodepos);
}




Point
Ort::whilefollowball(int level, int nodepos, int pos, int amount) {


    //int tempjumps = 0;
    while(amount > 1) {
        //++internaljumpcount;
        //++tempjumps;
        qreturn big = bigJump(level, pos);
        if(big.jump == 1) {
            int size = pow(2, big.size);

            level += big.size;
            // If bottom is hit, the (big.rank - nodepos/size) will be 0. Thus we can save away the entire rank storage
            int tlong = (ulon(amount)*ulon(big.character))/size;
            pos = tlong + nodepos + (big.rank - nodepos/size);
            nodepos += tlong;
            amount = amount/size;

        } else {

            uint irank = findRank(level, nodepos, pos) - nodepos/2;
            uint mask = bits.at(pos%32);
            uint num = (levels.at(level)).at(pos/32) & mask;
            uint dir = rank(num);

            
            if(dir == 0) {

                ++level;
                pos = pos - irank;
                amount = amount/2;

            } else if(dir == 1) {

                ++level;
                pos = nodepos + amount/2 + irank;
                nodepos += amount/2;
                amount = amount/2;

            } else {

                std::cout << "error" << std::endl;

            }
        }

    }
    /*if(tempjumps > internalmaxdepth) {
        internalmaxdepth = tempjumps;
    }*/
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
Ort::Ort(int amount, std::vector<Point> input) : balls(amount), levels(std::log2(amount), std::vector<uint>(std::ceil(float(amount)/32), 0)) {

    /*
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
    }*/

    std::vector<Point> points;
    points = input;

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


    // Generating big jumps

    // TODO: FIX THIS! How do I do this correctly with the constructor? 
    std::vector<std::vector<uint>> temparray(levels.size(), std::vector<uint>(points.size(), -1));
    twodarray = temparray;
    //twodarray.insert(std::begin(twodarray), levels.size(), std::vector<int>(points.size(), -1));
    
    //Jumper tempjump;
    //tempjump.jump = 1;
    //std::vector<Jumper> tjumps(levels.size(), tempjump);
    //jumps = tjumps;

    LinearJumper templinearjump;
    templinearjump.jump = 1;
    templinearjump.end = 0;
    std::vector<LinearJumper> tlinearjumps(levels.size(), templinearjump);
    //notsolinear = tlinearjumps;
    linear = tlinearjumps;
    //lineargarb = tlinearjumps;



    
    generateJumps();
    // GenerateJumps debug output
    /*for(const auto& l : linkedlists) {
        std::cout << l << std::endl;
    }
    //std::cout << points << std::endl;

    for(const auto& l : twodarray) {
        std::cout << l << std::endl;
    }
    for(const auto& e : jumps) {
        std::cout << e.jump << std::endl;
    }*/



    //type = 3;
    // Testing that all balls falls to their correct leaf
    /*bool all = true;
    for(int i = 0; i < points.size(); ++i) {
        all = all & (points.at(i) == whilefollowball(0,0,i,points.size()));
    }

    std::cout << "ALL WAS " << all << std::endl;*/

    initializeBinarySearches();
    linkedlists.clear();
    twodarray.clear();
    //type = 3;
}

std::vector<Point>
Ort::DeptheasyQuery(Point lowerleft, Point upperright, int& jumpcount, int& maxdepth, int& startlevel) {
    
    auto lx = std::lower_bound(std::begin(xb), std::end(xb), lowerleft.x);
    auto ux = std::upper_bound(std::begin(xb), std::end(xb), upperright.x);
    int lx_index = std::distance(std::begin(xb), lx);
    int ux_index = std::distance(std::begin(xb), ux) - 1;

    //std::cout << "lx_index: " << lx_index << std::endl;
    //std::cout << "ux_index: " << ux_index << std::endl;

    auto ly = std::lower_bound(std::begin(yb), std::end(yb), lowerleft.y);
    auto uy = std::upper_bound(std::begin(yb), std::end(yb), upperright.y);
    int ly_index = std::distance(std::begin(yb), ly);
    //TODO: HVORFOR SKAL DEN HER IKKE HAVE - 1 ? 
    int uy_index = std::distance(std::begin(yb), uy);

    //std::cout << "ly_index: " << ly_index << std::endl;
    //std::cout << "uy_index: " << uy_index << std::endl;
    
    Point x{lowerleft.y, upperright.y};
    corner = x;

    std::vector<Point> temp;

    // TODO: Find a better way to express amount of balls
    internaljumpcount = 0;
    internalmaxdepth = 0;
    internalstartlevel = 0;
    DepthFindPoints(lx_index, ux_index, ly_index, uy_index, 32-std::ceil(std::log2(balls.size())), 0, balls.size(), 0);


    results.swap(temp);
    maxdepth = internalmaxdepth;
    jumpcount = internaljumpcount;
    startlevel = internalstartlevel;
    internalstartlevel = 0;
    internalmaxdepth = 0;
    internaljumpcount = 0;
    return temp;
}



std::vector<Point>
Ort::easyQuery(Point lowerleft, Point upperright) {
    
    auto lx = std::lower_bound(std::begin(xb), std::end(xb), lowerleft.x);
    auto ux = std::upper_bound(std::begin(xb), std::end(xb), upperright.x);
    int lx_index = std::distance(std::begin(xb), lx);
    int ux_index = std::distance(std::begin(xb), ux) - 1;

    //std::cout << "lx_index: " << lx_index << std::endl;
    //std::cout << "ux_index: " << ux_index << std::endl;

    auto ly = std::lower_bound(std::begin(yb), std::end(yb), lowerleft.y);
    auto uy = std::upper_bound(std::begin(yb), std::end(yb), upperright.y);
    int ly_index = std::distance(std::begin(yb), ly);
    //TODO: HVORFOR SKAL DEN HER IKKE HAVE - 1 ? 
    int uy_index = std::distance(std::begin(yb), uy);

    //std::cout << "ly_index: " << ly_index << std::endl;
    //std::cout << "uy_index: " << uy_index << std::endl;
    
    Point x{lowerleft.y, upperright.y};
    corner = x;

    //TODO: Skal vi bruge det her?
    //int dist = std::max(ux_index-lx_index, uy_index-ly_index);
    //results.clear();
    //results.reserve(dist);
    
    std::vector<Point> temp;

    // TODO: Find a better way to express amount of balls
    //internaljumpcount = 0;
    //internalmaxdepth = 0;
    FindPoints(lx_index, ux_index, ly_index, uy_index, 32-std::ceil(std::log2(balls.size())), 0, balls.size(), 0);
    //std::cout << results << std::endl;
    /*bool all = true;
    for(const auto& e : results) {
        all = all & (lowerleft.x <= e.x && e.x <= upperright.x && lowerleft.y <= e.y && e.y <= upperright.y);
    }*/
    //std::cout << "AGAIN, ALL WAS " << all << " and the size is: " << results.size() << std::endl;


    results.swap(temp);
    /*maxdepth = internalmaxdepth;
    jumpcount = internaljumpcount;
    internalmaxdepth = 0;
    internaljumpcount = 0;*/
    return temp;
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

void
Ort::addAll(int nodepos, int lrank, int urank, int level, int amount) {
    for(int i = lrank-nodepos; i < urank-nodepos; ++i) {
        results.push_back(whilefollowball(level, nodepos, nodepos+i, amount));
    }
}

void
Ort::DepthaddAll(int nodepos, int lrank, int urank, int level, int amount) {
    for(int i = lrank-nodepos; i < urank-nodepos; ++i) {
        results.push_back(Depthwhilefollowball(level, nodepos, nodepos+i, amount));
    }
}




void
Ort::DepthfollowPoint(int child, int lyrank, int uyrank, int bit, int nodepos, int amount, DIRECTION d, int level) {

    if(amount < 1) {
        std::cout << "FEJL i followPoint" << std::endl;
    }
    
    //std::cout << "Hver for sig" << std::endl;

    if(amount > 1) {
        uint num = bits.at(bit);
        uint dir = child & num;
        uint lrank = findRank(level, nodepos, lyrank) - nodepos/2;
        uint urank = findRank(level, nodepos, uyrank) - nodepos/2;


        if(dir == 0) {
            if(d == LEFT) {
                // We now add all the points from the right subtree
                //std::cout << "Vi tager hele højre undertræ" << std::endl;
                DepthaddAll(nodepos + amount/2, nodepos + amount/2+lrank, nodepos + amount/2 + urank, level+1, amount/2);

            }

            DepthfollowPoint(child, lyrank-lrank, uyrank-urank, bit+1, nodepos, amount/2, d, level+1);
            return;

        } else {
            if(d == RIGHT) {
                // We now add all the points from the left subtree
                //std::cout << "Vi tager hele venstre undertræ" << std::endl;
                DepthaddAll(nodepos, lyrank-lrank, uyrank-urank, level+1, amount/2);

            }

            DepthfollowPoint(child, nodepos+amount/2 + lrank, nodepos + amount/2 + urank, bit+1, nodepos+amount/2, amount/2, d, level+1);
            return;

        }

    }

    // There might only be one point in amount
    // TODO: Is this assumption correct? 
    Point last = balls.at(nodepos);
    if(corner.x <= last.y && last.y <= corner.y) { 
        results.push_back(balls.at(nodepos));
    }

}



// DIRECTION d indicates which subtree of the LCA we are walking in
void
Ort::followPoint(int child, int lyrank, int uyrank, int bit, int nodepos, int amount, DIRECTION d, int level) {

    if(amount < 1) {
        std::cout << "FEJL i followPoint" << std::endl;
    }
    
    //std::cout << "Hver for sig" << std::endl;

    if(amount > 1) {
        uint num = bits.at(bit);
        uint dir = child & num;
        uint lrank = findRank(level, nodepos, lyrank) - nodepos/2;
        uint urank = findRank(level, nodepos, uyrank) - nodepos/2;


        if(dir == 0) {
            if(d == LEFT) {
                // We now add all the points from the right subtree
                //std::cout << "Vi tager hele højre undertræ" << std::endl;
                addAll(nodepos + amount/2, nodepos + amount/2+lrank, nodepos + amount/2 + urank, level+1, amount/2);

            }

            followPoint(child, lyrank-lrank, uyrank-urank, bit+1, nodepos, amount/2, d, level+1);
            return;

        } else {
            if(d == RIGHT) {
                // We now add all the points from the left subtree
                //std::cout << "Vi tager hele venstre undertræ" << std::endl;
                addAll(nodepos, lyrank-lrank, uyrank-urank, level+1, amount/2);

            }

            followPoint(child, nodepos+amount/2 + lrank, nodepos + amount/2 + urank, bit+1, nodepos+amount/2, amount/2, d, level+1);
            return;

        }

    }

    // There might only be one point in amount
    // TODO: Is this assumption correct? 
    Point last = balls.at(nodepos);
    if(corner.x <= last.y && last.y <= corner.y) { 
        results.push_back(balls.at(nodepos));
    }

}


void
Ort::DepthFindPoints(int leftchild, int rightchild, int ly_index, int uy_index, int bit, int nodepos, int amount, int level) {
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
            DepthFindPoints(leftchild, rightchild, ly_index-lrank, uy_index-urank, bit+1, nodepos, amount/2, level+1);
            return;
        } else {
            DepthFindPoints(leftchild, rightchild, nodepos + amount/2 + lrank, nodepos + amount/2 + urank, bit+1, nodepos+amount/2, amount/2, level+1);
            return;
        }
    }
    internalstartlevel = levels.size() - level;
    DepthfollowPoint(leftchild,ly_index-lrank, uy_index-urank, bit+1, nodepos, amount/2, LEFT, level+1);
    DepthfollowPoint(rightchild,nodepos+amount/2+lrank,nodepos+amount/2+urank, bit+1, nodepos+amount/2, amount/2, RIGHT, level+1);
}



void
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
            FindPoints(leftchild, rightchild, ly_index-lrank, uy_index-urank, bit+1, nodepos, amount/2, level+1);
            return;
        } else {
            FindPoints(leftchild, rightchild, nodepos + amount/2 + lrank, nodepos + amount/2 + urank, bit+1, nodepos+amount/2, amount/2, level+1);
            return;
        }
    }
    followPoint(leftchild,ly_index-lrank, uy_index-urank, bit+1, nodepos, amount/2, LEFT, level+1);
    followPoint(rightchild,nodepos+amount/2+lrank,nodepos+amount/2+urank, bit+1, nodepos+amount/2, amount/2, RIGHT, level+1);
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

