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
   
    if(argc == 3) {
        std::ifstream myfile(argv[1]);
        std::string name(argv[2]);
        std::string line;
        int current = 0;
        int placement = 0;
        int ort_avg;
        int max_jump;
        float avg_jump;
        float level_avg;
        int level_max;
        int level_min;
        int kd_avg;
        int size;
        std::ofstream output;
        if (myfile.is_open()) {
            while ( myfile.good()) {
                std::getline (myfile,line);
                if(line.size() > 0) {
                    auto tokens = split(line, ' ');
                    if(tokens.at(0) == "TESTING") {
                        int temp = std::stoi(tokens.at(1));
                        if(current != temp) {
                            current = temp;
                            if(output.is_open()) {
                                output.flush();
                                output.close();
                            }
                            output.open(name + "_" + std::to_string(current) + ".dat");
                        }
                        if(tokens.at(5) == "(ORT)") {
                            placement = 0;
                            size = std::stoi(tokens.at(3));
                        }
                        if(tokens.at(5) == "(JUMPS)") {
                            placement = 1;
                        }
                        if(tokens.at(5) == "(KDTREE)") {
                            placement = 2;
                        }
                    }
                    if(tokens.at(0) == "Average") {
                        if(placement == 0) {
                            ort_avg = std::stoi(tokens.at(2));
                        }
                        if(placement == 2) {
                            kd_avg = std::stoi(tokens.at(2));
                            output << size << " " << ort_avg << " " << kd_avg << " " << avg_jump << " " << max_jump << " " << level_avg << " " << level_max << " " << level_min  << std::endl;
                        }
                    }
                    if(tokens.at(0) == "That") {
                        avg_jump = std::stof(tokens.at(2));
                    }
                    if(tokens.at(0) == "With") {
                        max_jump = std::stoi(tokens.at(5));
                    }
                    if(tokens.at(0) == "startlevel") {
                        level_avg = std::stof(tokens.at(8));
                        level_max = std::stoi(tokens.at(3));
                        level_min = std::stoi(tokens.at(13));
                    }

                }
            }
            myfile.close();
        }
    }
    return 0;

}
