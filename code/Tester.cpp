#include "Tester.hpp"
#include <chrono>
#include <functional>


using unitofmeassure = std::chrono::microseconds;
//using unitofmeassure = std::chrono::nanoseconds;

template<typename T>
std::vector<int> numbers(std::vector<T> input, bool reverse = false) {
    std::vector<int> ret;
    if(reverse) {
        std::sort(std::begin(input), std::end(input), std::greater<T>());
    } else {
        std::sort(std::begin(input), std::end(input), std::less<T>());
    }

    ret.push_back(input.at(0)); // 0
    ret.push_back(input.at(0.05*(input.size()-1))); // 1
    ret.push_back(input.at(0.25*(input.size()-1))); // 2
    ret.push_back(input.at(0.5*(input.size()-1))); // 3
    ret.push_back(input.at(0.75*(input.size()-1))); // 4
    ret.push_back(input.at(0.95*(input.size()-1))); // 5
    ret.push_back(input.at(input.size()-1)); // 6

    float res = 0.0;
    for(const auto& e : input) {
        res += float(e)/input.size();
    }
    ret.push_back(res); // 7
    return ret;
}

Tester::Tester() {
    // Nothing
}

std::tuple<Ort, KDTree>
Tester::buildtrees(int n) {
    int amount = pow(2,n);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::vector<Point> points = Data::generate(amount);

    Ort ort(amount, points);
    KDTree kdtree(amount, points);

    return std::make_tuple(ort, kdtree);
}

//TODO: REWRITE DET HELE TIL MERE SIMPLE FUNKTIONER
//TODO: REWRITE SIZE OG A
//TODO: REWRITE TIL AT FINDE MELLEM A OG B HVOR ORT ER BEDRE END KD I STEDET FOR BARE OP TIL

void
Tester::report(const std::vector<int>& vec, std::string name, std::string timename) {
    std::cout << std::endl << std::endl << "TESTING " << name << std::endl;
    std::cout << "Best = " << vec.at(0) << " " << timename << std::endl;
    std::cout << "5% percentile = " << vec.at(1) << " " << timename << std::endl;
    std::cout << "25% percentile = " << vec.at(2) << " " << timename << std::endl;
    std::cout << "50% percentile = " << vec.at(3) << " " << timename << std::endl;
    std::cout << "75% percentile = " << vec.at(4) << " " << timename << std::endl;
    std::cout << "95% percentile = " << vec.at(5) << " " << timename << std::endl;
    std::cout << "Worst = " << vec.at(6) << "  " << timename << std::endl;
    std::cout << "Average = " << vec.at(7) << " " << timename << std::endl;
    std::cout << "<=== === === === === === === === ===>" << std::endl;
}


void
Tester::Test2(std::string name) {
    int testSize = 17;
    Timer<unitofmeassure> t1;
    int amount = pow(2,testSize);
    std::vector<int> times;
    int max = 0;
    int x = 0;
    for(int i = 0; i < 100; ++i) {
        Ort ort = std::get<0>(buildtrees(testSize));
        for(int j = 0; j < 100; ++j) {
            t1.reset();
            t1.start();
            ort.search({{(amount/100)*j, 0},{(amount/100)*j + 20, amount}}, 3);
            t1.stop();
            ++x;
            if(t1.duration().count() > max) {
                max = t1.duration().count();
                std::cout << x << ": NEW MAX : " << max << std::endl;
            }
            times.push_back(t1.duration().count());
            
        }
    }
    std::vector<int> rep = numbers(times);
    report(rep, name, t1.type());

}

void
Tester::Test3(std::string name) {
    int testSize = 17;
    Timer<unitofmeassure> t1;
    int amount = pow(2, testSize);
    std::vector<int> times;
    int max = 0;
    int x = 0;
    for(int i = 0; i < 10; ++i) {
        Ort ort = std::get<0>(buildtrees(testSize));
        for(int j = 0; j < 100; ++j) {
            for(int h = 0; h < 100; ++h) {
                t1.reset();
                t1.start();
                ort.search({{(amount/100)*j, 0},{(amount/100)*j + 20, amount}}, 3);
                t1.stop();
                ++x;
                times.push_back(t1.duration().count());
                if(t1.duration().count() > max) {
                    max = t1.duration().count();
                    std::cout << x << ": NEW MAX : " << max << std::endl;
                }

            }
        }
    }
    std::vector<int> rep = numbers(times);
    report(rep, name, t1.type());
}

void
Tester::Test9(std::string name) {
    int testSize = 17;
    Timer<std::chrono::nanoseconds> t1;
    int amount = pow(2, testSize);
    std::vector<std::vector<int>> times(10, std::vector<int> {});
    int max = 0;
    int x = 0;
    for(int i = 0; i < 10; ++i) {
        Ort ort = std::get<0>(buildtrees(testSize));
        for(int j = 0; j < 100; ++j) {
            for(int h = 0; h < 10; ++h) {
                t1.reset();
                t1.start();
                ort.search({{(amount/10)*h, 0},{(amount/10)*h + 50, amount}}, 3);
                t1.stop();
                ++x;
                times.at(h).push_back(t1.duration().count());

            }
        }
    }
    for(int i = 0; i < 10; ++i) {
        std::vector<int> rep = numbers(times.at(i));
        report(rep, name, t1.type());
    }
}

void
Tester::Test10(std::string name) {
    int testSize = 17;
    Timer<std::chrono::nanoseconds> t1;
    int amount = pow(2, testSize);
    std::vector<std::vector<int>> times(10, std::vector<int> {});
    int max = 0;
    int x = 0;
    for(int i = 0; i < 10; ++i) {
        Ort ort = std::get<0>(buildtrees(testSize));
        for(int j = 0; j < 100; ++j) {
            for(int h = 0; h < 10; ++h) {
                t1.reset();
                t1.start();
                ort.search({{0, (amount/10)*h},{amount, (amount/10)*h + 50}}, 3);
                t1.stop();
                ++x;
                times.at(h).push_back(t1.duration().count());

            }
        }
    }
    for(int i = 0; i < 10; ++i) {
        std::vector<int> rep = numbers(times.at(i));
        report(rep, name, t1.type());
    }
}




void
Tester::Test5(std::string name) {
    int testSize = 17;
    Timer<unitofmeassure> t1;
    Timer<unitofmeassure> t2;
    int amount = pow(2, testSize);
    std::vector<int> times;
    int max = 0;
    int x = 0;
    for(int i = 0; i < 10; ++i) {
        std::tuple<Ort, KDTree> trees = buildtrees(testSize);
        Ort ort = std::get<0>(trees);
        KDTree kdtree = std::get<1>(trees);
        for(int j = 0; j < 100; ++j) {
            for(int h = 0; h < 100; ++h) {
                int a = 0;
                int size = 10;

                t1.reset();
                t1.start();
                ort.search({{(amount/100)*h, 0},{(amount/100)*h + size, amount}}, 3);
                t1.stop();

                t2.reset();
                t2.start();
                kdtree.search({{(amount/100)*h, 0},{(amount/100)*h + size, amount}});
                t2.stop();


                while(t1.duration().count() < t2.duration().count()) {
                    a += 5;
                    size += 5;

                    t1.reset();
                    t1.start();
                    ort.search({{(amount/100)*h, 0},{(amount/100)*h + size, amount}}, 3);
                    t1.stop();

                    t2.reset();
                    t2.start();
                    kdtree.search({{(amount/100)*h, 0},{(amount/100)*h + size, amount}});
                    t2.stop();

                }
                times.push_back(a);
            }
        }
    }
    std::vector<int> rep = numbers(times, true);
    report(rep, name, "times");

}


void
Tester::Test6(std::string name) {
    int testSize = 17;
    Timer<unitofmeassure> t1;
    Timer<unitofmeassure> t2;
    int amount = pow(2, testSize);
    std::vector<int> times;
    int max = 0;
    int x = 0;
    for(int i = 0; i < 10; ++i) {
        std::tuple<Ort, KDTree> trees = buildtrees(testSize);
        Ort ort = std::get<0>(trees);
        KDTree kdtree = std::get<1>(trees);
        for(int j = 0; j < 100; ++j) {
            for(int h = 0; h < 100; ++h) {
                int a = 0;
                int size = 10;

                t1.reset();
                t1.start();
                ort.search({{0, (amount/100)*j},{amount, (amount/100)*j + size}}, 3);
                t1.stop();

                t2.reset();
                t2.start();
                kdtree.search({{0, (amount/100)*j},{amount, (amount/100)*j + size}});
                t2.stop();


                while(t1.duration().count() < t2.duration().count()) {
                    a += 5;
                    size += 5;

                    t1.reset();
                    t1.start();
                    ort.search({{0, (amount/100)*j},{amount, (amount/100)*j + size}}, 3);
                    t1.stop();

                    t2.reset();
                    t2.start();
                    kdtree.search({{0, (amount/100)*j},{amount, (amount/100)*j + size}});
                    t2.stop();

                }
                
                /*if(a == 0) {
                    Region reg {{0, (amount/100)*j},{amount, (amount/100)*j + size}};
                    std::cout << reg << std::endl;
                }*/
                times.push_back(a);
            }
        }
    }
    std::vector<int> rep = numbers(times, true);
    report(rep, name, "times");

}


void
Tester::Test8(std::string name) {
    int testSize = 17;
    Timer<unitofmeassure> t1;
    Timer<unitofmeassure> t2;
    int amount = pow(2, testSize);
    std::vector<int> times;
    int max = 0;
    int x = 0;
    for(int i = 0; i < 10; ++i) {
        std::tuple<Ort, KDTree> trees = buildtrees(testSize);
        Ort ort = std::get<0>(trees);
        KDTree kdtree = std::get<1>(trees);
        for(int j = 0; j < 100; ++j) {
            for(int h = 0; h < 10; ++h) {
                int a = 0;
                int size = 10;

                Region reg {{0, (amount/100)*j},{amount-size, (amount/100)*j + 50}};

                t1.reset();
                t1.start();
                ort.search(reg, 3);
                t1.stop();

                t2.reset();
                t2.start();
                kdtree.search(reg);
                t2.stop();


                while(t1.duration().count() < t2.duration().count() && amount > (size+5)) {
                    a += 5;
                    size += 5;

                    reg = {{0, (amount/100)*j},{amount-size, (amount/100)*j + 50}};
                    reg = {{(amount/100)*j, 0},{(amount/100)*j + 50, amount-size}};

                    t1.reset();
                    t1.start();
                    ort.search(reg, 3);
                    t1.stop();

                    t2.reset();
                    t2.start();
                    kdtree.search(reg);
                    t2.stop();

                }
                
                /*if(a == 0) {
                    std::cout << reg << std::endl;
                }*/
                times.push_back(a);
            }
        }
    }
    std::vector<int> rep = numbers(times, true);
    report(rep, name, "times");

}

void
Tester::Test7(std::string name) {
    int testSize = 17;
    Timer<unitofmeassure> t1;
    Timer<unitofmeassure> t2;
    int amount = pow(2, testSize);
    std::vector<int> times;
    int max = 0;
    int x = 0;
    for(int i = 0; i < 10; ++i) {
        std::tuple<Ort, KDTree> trees = buildtrees(testSize);
        Ort ort = std::get<0>(trees);
        KDTree kdtree = std::get<1>(trees);
        for(int j = 0; j < 100; ++j) {
            for(int h = 0; h < 10; ++h) {
                int a = 0;
                int size = 10;

                Region reg {{(amount/100)*j, 0},{(amount/100)*j + 50, amount-size}};

                t1.reset();
                t1.start();
                ort.search(reg, 3);
                t1.stop();

                t2.reset();
                t2.start();
                kdtree.search(reg);
                t2.stop();


                while(t1.duration().count() < t2.duration().count() && amount > (size+5)) {
                    a += 5;
                    size += 5;
                    reg = {{(amount/100)*j, 0},{(amount/100)*j + 50, amount-size}};

                    t1.reset();
                    t1.start();
                    ort.search(reg, 3);
                    t1.stop();

                    t2.reset();
                    t2.start();
                    kdtree.search(reg);
                    t2.stop();

                }
                
                /*if(a == 0) {
                    std::cout << reg << std::endl;
                }*/
                times.push_back(a);
            }
        }
    }
    std::vector<int> rep = numbers(times, true);
    report(rep, name, "times");

}


void
Tester::Test4(std::string name) {
    int testSize = 17;
    Timer<unitofmeassure> t1;
    Timer<unitofmeassure> t2;
    int amount = pow(2, testSize);
    std::vector<int> times;
    int max = 0;
    int x = 0;
    for(int i = 0; i < 10; ++i) {
        std::tuple<Ort, KDTree> trees = buildtrees(testSize);
        Ort ort = std::get<0>(trees);
        KDTree kdtree = std::get<1>(trees);
        for(int j = 0; j < 100; ++j) {
            for(int h = 0; h < 100; ++h) {
                int a = 0;
                int size = 10;

                t1.reset();
                t1.start();
                ort.search({{(amount/100)*j, 0},{(amount/100)*j + size, amount}}, 3);
                t1.stop();

                t2.reset();
                t2.start();
                kdtree.search({{(amount/100)*j, 0},{(amount/100)*j + size, amount}});
                t2.stop();


                while(t1.duration().count() < t2.duration().count()) {
                    a += 5;
                    size += 5;

                    t1.reset();
                    t1.start();
                    ort.search({{(amount/100)*j, 0},{(amount/100)*j + size, amount}}, 3);
                    t1.stop();

                    t2.reset();
                    t2.start();
                    kdtree.search({{(amount/100)*j, 0},{(amount/100)*j + size, amount}});
                    t2.stop();

                }
                /*if(a == 0) {
                    Region reg {{(amount/100)*j, 0},{(amount/100)*j + size, amount}};
                    std::cout << reg << std::endl;
                }*/
                times.push_back(a);
            }
        }
    }
    std::vector<int> rep = numbers(times, true);
    report(rep, name, "times");

}

// All horizontal queries are equal
void
Tester::Test1(std::string name) {
    int testSize = 17;
    Timer<unitofmeassure> t1;
    int amount = pow(2,testSize);
    int max = 0;
    int x = 0;
    std::vector<int> times;
    for(int i = 0; i < 100; ++i) {
        Ort ort = std::get<0>(buildtrees(testSize));
        for(int j = 0; j < 100; ++j) {
            t1.reset();
            t1.start();
            ort.search({{0,(amount/100)*j},{amount, (amount/100)*j + 20}}, 3);
            t1.stop();
            ++x;
            times.push_back(t1.duration().count());
            if(t1.duration().count() > max) {
                max = t1.duration().count();
                std::cout << x << ": NEW MAX : " << max << std::endl;
            }
            if(t1.duration().count() > 100) {
                std::cout << "WE NAILED A BIG ONE, CAPT!" << std::endl;
                std::cout << "Setting: (0, " << (amount/100)*j << "), (" << amount << ", " << (amount/100)*j + 20 << ")." << std::endl;
            }

            
        }
    }
    std::vector<int> rep = numbers(times);
    report(rep, name, t1.type());

}
