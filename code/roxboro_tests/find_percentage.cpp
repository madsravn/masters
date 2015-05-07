#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <sstream>



// From http://stackoverflow.com/questions/236129/splitting-a-string-in-c
std::vector<std::string>& split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

// From http://stackoverflow.com/questions/236129/splitting-a-string-in-c
std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}


// Finds the entry (size of window) where the ort ds search is $percentage$-100 faster than the kd-tree search. percentage = 100 for equal
int main(int argc, char** argv) {
   
    if(argc == 3) {
        std::ifstream myfile(argv[1]);
        std::string line;
        int percentage = std::stoi(argv[2]);
        int count = 0;
        int current = 0;
        float diff = 1000000;
        int x = 0;
        if (myfile.is_open()) {
            while ( myfile.good()) {
                std::getline (myfile,line);
                if(line.size() > 0) {
                    auto tokens = split(line, ' ');
                    if(tokens.at(0) == "Showing") {
                        if(x == 1) {
                            std::cout << count << " " << current << std::endl;
                        }
                        x = 1;
                        current = 0;
                        diff = 1000000;
                        count = std::stoi(tokens.at(3));
                    } else {
                        //std::cout << fabs(percentage - 100*float(std::stoi(tokens.at(2)))/float(std::stoi(tokens.at(1)))) << std::endl;

                        if(fabs(percentage - 100*float(std::stoi(tokens.at(2)))/float(std::stoi(tokens.at(1)))) < diff) {
                            diff = fabs(percentage - 100*float(std::stoi(tokens.at(2)))/float(std::stoi(tokens.at(1))));
                            current = std::stoi(tokens.at(0));
                        }
                    }

                }
            }
            myfile.close();
        }
        std::cout << count << " " << current << std::endl;
    }
    return 0;

}
