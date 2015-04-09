#include "Tester.hpp"
#include <chrono>


using unitofmeassure = std::chrono::microseconds;

template<typename T>
std::vector<int> numbers(std::vector<T> input) {
    std::vector<int> ret;
    std::sort(std::begin(input), std::end(input));
    ret.push_back(input.at(0.05*(input.size()-1)));
    ret.push_back(input.at(0.25*(input.size()-1)));
    ret.push_back(input.at(0.5*(input.size()-1)));
    ret.push_back(input.at(0.75*(input.size()-1)));
    ret.push_back(input.at(0.95*(input.size()-1)));

    float res = 0.0;
    for(const auto& e : input) {
        res += float(e)/input.size();
    }
    ret.push_back(res);
    return ret;
}

Tester::Tester() {
    // Nothing
}

Ort
Tester::BuildOrt(int n) {
    int amount = pow(2,n);
    std::random_device rd;
    std::mt19937 gen(rd());
    Ort ort(amount, Data::generate(amount));
    return ort;
}


void
Tester::Test2(std::string name) {
    int testSize = 17;
    Timer<unitofmeassure> t1;
    int amount = pow(2,testSize);
    std::vector<int> times;
    for(int i = 0; i < 100; ++i) {
        Ort ort = BuildOrt(testSize);
        for(int j = 0; j < 100; ++j) {
            t1.reset();
            t1.start();
            ort.search({{(amount/100)*j, 0},{(amount/100)*j + 20, amount}}, 3);
            t1.stop();
            times.push_back(t1.duration().count());
            
        }
    }
    std::vector<int> report = numbers(times);
    std::cout << std::endl << std::endl << "TESTING " << name << std::endl;
    std::cout << "5% percentile = " << report.at(0) << " " << t1.type() << std::endl;
    std::cout << "25% percentile = " << report.at(1) << " " << t1.type() << std::endl;
    std::cout << "50% percentile = " << report.at(2) << " " << t1.type() << std::endl;
    std::cout << "75% percentile = " << report.at(3) << " " << t1.type() << std::endl;
    std::cout << "95% percentile = " << report.at(4) << " " << t1.type() << std::endl;
    std::cout << "Average = " << report.at(5) << " " << t1.type() << std::endl;
    std::cout << "<=== === === === === === === === ===>" << std::endl;



}

// All horizontal queries are equal
void
Tester::Test1(std::string name) {
    int testSize = 17;
    Timer<unitofmeassure> t1;
    int amount = pow(2,testSize);
    std::vector<int> times;
    for(int i = 0; i < 100; ++i) {
        Ort ort = BuildOrt(testSize);
        for(int j = 0; j < 100; ++j) {
            t1.reset();
            t1.start();
            ort.search({{0,(amount/100)*j},{amount, (amount/100)*j + 20}}, 3);
            t1.stop();
            times.push_back(t1.duration().count());
            
        }
    }
    std::vector<int> report = numbers(times);
    std::cout << std::endl << std::endl << "TESTING " << name << std::endl;
    std::cout << "5% percentile = " << report.at(0) << " " << t1.type() << std::endl;
    std::cout << "25% percentile = " << report.at(1) << " " << t1.type() << std::endl;
    std::cout << "50% percentile = " << report.at(2) << " " << t1.type() << std::endl;
    std::cout << "75% percentile = " << report.at(3) << " " << t1.type() << std::endl;
    std::cout << "95% percentile = " << report.at(4) << " " << t1.type() << std::endl;
    std::cout << "Average = " << report.at(5) << " " << t1.type() << std::endl;
    std::cout << "<=== === === === === === === === ===>" << std::endl;



}
