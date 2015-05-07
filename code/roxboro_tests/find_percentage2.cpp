#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cmath>



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
   
    if(argc == 3) {
        std::ifstream myfile(argv[1]);
        std::string line;
        int lgn = 0;
        int current = 0;
        int placement = 0;
        int percentage = std::stoi(argv[2]);
        float diff = 1000000;
        int x = 0;
        int kdtree;
        int ort;
        int windowsize = 0;
        int maxjump = 0;
        float avg_jump = 0;
        float jumps_per_result = 0;
        int out_maxjump = 0;
        float out_avg_jump = 0;
        float out_jumps_per_result = 0;

        if (myfile.is_open()) {
            while ( myfile.good()) {
                std::getline (myfile,line);
                if(line.size() > 0) {
                    auto tokens = split(line, ' ');
                    if(tokens.at(0) == "TESTING") {
                        int t = std::stoi(tokens.at(1));
                        current = std::stoi(tokens.at(3));
                        if(lgn < t && x == 1) {
                            std::cout << lgn << " " << windowsize << " " << out_maxjump << " " << out_avg_jump << " " << out_jumps_per_result << " " << std::sqrt(std::pow(2, lgn)) << std::endl;

                            lgn = t;
                            diff = 1000000;
                        } else {
                            lgn = t;
                        }
                        x = 1;
                        if(tokens.at(5) == "(ORT)") {
                            placement = 0;
                        }
                        if(tokens.at(5) == "(JUMPS)") {
                            placement = 1;
                        }
                        if(tokens.at(5) == "(KDTREE)") {
                            placement = 2;
                        }
                    } else {
                        if(tokens.at(0) == "Average") {
                            if(placement == 0) {
                                ort = std::stoi(tokens.at(2));
                            }
                            if(placement == 2) {
                                kdtree = std::stoi(tokens.at(2));
                                if(fabs(percentage - 100*float(kdtree)/float(ort)) < diff) {
                                    diff = fabs(percentage - 100*float(kdtree)/float(ort));
                                    windowsize = current;
                                    out_maxjump = maxjump;
                                    out_avg_jump = avg_jump;
                                    out_jumps_per_result = jumps_per_result;
                                }
 

                            }
                        }
                        if(tokens.at(0) == "That") {
                            jumps_per_result = std::stof(tokens.at(2));
                        }
                        if(tokens.at(0) == "With") {
                            maxjump = std::stoi(tokens.at(5));
                            avg_jump = std::stof(tokens.at(10));
                        }
                    }

                }
            }
            myfile.close();
        }

        std::cout << lgn << " " << windowsize << " " << out_maxjump << " " << out_avg_jump << " " << out_jumps_per_result << " " << std::sqrt(std::pow(2,lgn)) <<  std::endl;
    }
    return 0;

}
