#include <random>
#include <algorithm>
#include <chrono>
#include "Data.hpp"


std::vector<Point> 
Data::randomPoints(std::mt19937 gen, int amount) {

     std::uniform_int_distribution<> dis(1, amount);
     Point l, u;

    int a = 5;
    int b = 5;

    while(a == b) {
     
        a = dis(gen);
        b = dis(gen);
        if(a < b) {
            l.x = a; 
            u.x = b;
        } else {
            u.x = a;
            l.x = b;
        }
    }

    a = 5;
    b = 5;
    while(a == b) {
        a = dis(gen);
        b = dis(gen);
        if(a < b) {
            l.y = a;
            u.y = b;
        } else {
            u.y = a;
            l.y = b;
        }
    }
    std::vector<Point> result {l, u};
    return result;
}



std::vector<Point>
Data::generate(int amount) {
    int n{0};
    std::vector<int> x(amount);
    std::vector<int> y(amount);

    std::generate(std::begin(x), std::end(x), [&] { return ++n;});
    std::copy(std::begin(x), std::end(x), std::begin(y));

    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(std::begin(x), std::end(x), g);
    std::shuffle(std::begin(y), std::end(y), g);

    std::vector<Point> points;
    for(int i = 0; i < amount; ++i) {
        points.push_back({x[i], y[i]});
    }
    return points;
}

std::vector<Point>
Data::generateRandom(int amount, int start, int stop) {

    std::vector<int> x(amount);
    std::vector<int> y(amount);
    std::vector<int> placeholder(stop-start);
    std::generate(std::begin(placeholder), std::end(placeholder), [&] {return start++;});

    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(std::begin(placeholder), std::end(placeholder), g);
    std::copy(std::begin(placeholder), std::begin(placeholder)+amount, std::begin(x));
    
    std::shuffle(std::begin(placeholder), std::end(placeholder), g);
    std::copy(std::begin(placeholder), std::begin(placeholder)+amount, std::begin(y));

    std::vector<Point> points;
    for(int i = 0; i < amount; ++i) {
        points.push_back({x[i], y[i]});
    }
    return points;
}

void
Data::saveState(std::vector<Point> points, Region region) {
     auto now = std::chrono::system_clock::now();
     std::random_device rd;
     std::mt19937 gen(rd());
     auto secs = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch());

     std::string filename = "debug/" + std::to_string(secs.count());
     std::uniform_int_distribution<> dis(7652, 8761238);
     int random = dis(gen);
     filename += "_" + std::to_string(random);
     std::ofstream output(filename);
     output << region.ll.x << " " << region.ll.y << " " << region.ur.x << " " << region.ur.y;
     for(const auto& p : points) {
         output << std::endl << p.x << " " << p.y;
     }
     output.flush();
     output.close();
     std::cout << "Error state saved as " << filename << std::endl;

}

std::tuple<std::vector<Point>, Region> 
Data::loadState(std::string filename) {
    std::ifstream file("debug/" + filename);
    Region query;
    std::vector<Point> points;
    if(file.fail()) {
        std::cout << "Encountered an error opening the file" << std::endl;
        file.close();
    } else {
        file >> query.ll.x >> query.ll.y >> query.ur.x >> query.ur.y;
        int x,y;
        while(file >> x >> y) {
            points.push_back({x,y});
        }
        file.close();
    }
    return std::make_tuple(points, query);
}




