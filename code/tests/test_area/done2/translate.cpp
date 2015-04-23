#include <iostream>
#include <fstream>
#include <vector>
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


// Find the run time of the kd-tree and ort ds where window size = num. Then writes it to stdout for each size of the tree.
int main(int argc, char** argv) {
   
    if(argc == 3) {
        std::ifstream myfile(argv[1]);
        std::string line;
        std::string num(argv[2]);
        int count = 0;
        if (myfile.is_open()) {
            while ( myfile.good()) {
                std::getline (myfile,line);
                if(line.size() > 0) {
                    auto tokens = split(line, ' ');
                    if(tokens.at(0) == "Showing") {
                        count = std::stoi(tokens.at(3));
                    }
                    if(tokens.at(0) == num) {
                        std::cout << count << " "  << tokens.at(1) << " " << tokens.at(2) << " " << 100*float(std::stoi(tokens.at(2)))/float(std::stoi(tokens.at(1))) << std::endl;
                    }

                }
            }
            myfile.close();
        }
    }
    return 0;

}
