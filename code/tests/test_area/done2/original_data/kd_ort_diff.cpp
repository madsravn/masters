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


int main(int argc, char** argv) {
   
    if(argc == 2) {
        std::ifstream myfile(argv[1]);
        std::string line;
        int count = 0;
        if (myfile.is_open()) {
            while ( myfile.good()) {
                std::getline (myfile,line);
                if(line.size() > 0) {
                    auto tokens = split(line, ' ');
                    if(tokens.at(0) == "TESTING") {
                        if(tokens.at(1) != std::to_string(count)) {
                            count = std::stoi(tokens.at(1));
                            std::cout << std::endl << std::endl << "Showing data for " << count << std::endl << std::endl;

                        }
                        if(tokens.at(5) == "(ORT)") {
                            std::cout << std::endl << tokens.at(3) << " ";
                        }

                    }
                    if(tokens.at(0) == "Average") {
                        std::cout << tokens.at(2) << " ";
                    }
                }
            }
            myfile.close();
        }
    }
    return 0;

}
