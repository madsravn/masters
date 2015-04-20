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


template<typename T>
std::vector<std::vector<int>> numbers2(std::vector<std::vector<T>> vecs, bool reverse = false) {
    std::vector<std::vector<int>> rret;
    for(auto& input : vecs) {
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
        rret.push_back(ret);
    }
    return rret;
}



Tester::Tester(int k) {

    size_of_trees = k;
    
    auto now = std::chrono::system_clock::now();
    std::random_device rd;
    std::mt19937 gen(rd());
    auto secs = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch());


    std::string filename = "tests/" + std::to_string(secs.count());
    std::uniform_int_distribution<> dis(7652, 8761238);
    int random = dis(gen);
    filename += "_" + std::to_string(random);
    output.open(filename);
    std::cout << "Saving testing data to: " << filename << std::endl;
    
}

Tester::~Tester() {
    output.flush();
    output.close();

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

    output << std::endl << std::endl << "TESTING " << name << std::endl;
    output << "Best = " << vec.at(0) << " " << timename << std::endl;
    output << "5% percentile = " << vec.at(1) << " " << timename << std::endl;
    output << "25% percentile = " << vec.at(2) << " " << timename << std::endl;
    output << "50% percentile = " << vec.at(3) << " " << timename << std::endl;
    output << "75% percentile = " << vec.at(4) << " " << timename << std::endl;
    output << "95% percentile = " << vec.at(5) << " " << timename << std::endl;
    output << "Worst = " << vec.at(6) << "  " << timename << std::endl;
    output << "Average = " << vec.at(7) << " " << timename << std::endl;
    output << "<=== === === === === === === === ===>" << std::endl;

}

void
Tester::report2(const std::vector<std::vector<int>>& vec, std::string name, std::string timename) {
    std::cout << std::endl << std::endl << "TESTING " << name << std::endl;
    std::cout << "< 5%, 50%, 95%, average >" << std::endl;
    for(const auto& e : vec) {
        std::cout << "< " << e.at(1) << ", " << e.at(3) << ", " << e.at(5) << ", " << e.at(7) << " >" << std::endl;
    }
}


void
Tester::how_much_faster_is_ort_horizontal(std::string name) {
    for(int k = 17; k < 23; ++k) {
        std::cout << "Starting tree with size " << k << std::endl;
        int testSize = k;
        Timer<unitofmeassure> t1;
        int amount = pow(2,testSize);
        int how_many = std::sqrt(amount)*1.5;
        std::cout << "how_many = " << how_many << std::endl;
        int interval = 5;
        int jumps = how_many/interval;
        std::vector<std::vector<int>> timevector(jumps, std::vector<int> {});
        std::vector<std::vector<int>> timevector2(jumps, std::vector<int> {});
        for(int i = 0; i < 10; ++i) {
            std::tuple<Ort, KDTree> trees = buildtrees(testSize);
            Ort ort = std::get<0>(trees);
            KDTree kdtree = std::get<1>(trees);
            for(int size = 1; size < jumps+1; ++size) {
                for(int h = 0; h < 10; ++h) {
                    for(int j = 0; j < 100; ++j) {
                        t1.reset();
                        t1.start();
                        ort.search({{0, (amount/100)*j},{amount, (amount/100)*j + size*interval}}, 3);
                        t1.stop();

                        timevector.at(size-1).push_back(t1.duration().count());

                        t1.reset();
                        t1.start();
                        kdtree.search({{0, (amount/100)*j},{amount, (amount/100)*j + size*interval}});
                        t1.stop();

                        timevector2.at(size-1).push_back(t1.duration().count());
                        
                    }
                }
            }
        }
        for(int i = 0; i < timevector.size(); ++i) {
            std::vector<int> rep = numbers(timevector.at(i));
            report(rep, std::to_string(k) + " and " + std::to_string((i+1)*interval) + " = (ORT) " + name, t1.type());
            std::vector<int> rep2 = numbers(timevector2.at(i));
            report(rep2, std::to_string(k) + " and " + std::to_string((i+1)*interval) + " = (KDTREE) " + name, t1.type());
        }


    }



}




void
Tester::how_much_faster_is_ort_vertical(std::string name) {
    for(int k = 17; k < 23; ++k) {
        std::cout << "Starting tree with size " << k << std::endl;
        int testSize = k;
        Timer<unitofmeassure> t1;
        int amount = pow(2,testSize);
        int how_many = std::sqrt(amount)*1.5;
        std::cout << "how_many = " << how_many << std::endl;
        int interval = 5;
        int jumps = how_many/interval;
        std::vector<std::vector<int>> timevector(jumps, std::vector<int> {});
        std::vector<std::vector<int>> timevector2(jumps, std::vector<int> {});
        for(int i = 0; i < 10; ++i) {
            std::tuple<Ort, KDTree> trees = buildtrees(testSize);
            Ort ort = std::get<0>(trees);
            KDTree kdtree = std::get<1>(trees);
            for(int size = 1; size < jumps+1; ++size) {
                for(int h = 0; h < 10; ++h) {
                    for(int j = 0; j < 100; ++j) {
                        t1.reset();
                        t1.start();
                        ort.search({{(amount/100)*j, 0},{(amount/100)*j + size*interval, amount}}, 3);
                        t1.stop();

                        timevector.at(size-1).push_back(t1.duration().count());

                        t1.reset();
                        t1.start();
                        kdtree.search({{(amount/100)*j, 0},{(amount/100)*j + size*interval, amount}});
                        t1.stop();

                        timevector2.at(size-1).push_back(t1.duration().count());
                        
                    }
                }
            }
        }
        for(int i = 0; i < timevector.size(); ++i) {
            std::vector<int> rep = numbers(timevector.at(i));
            report(rep, std::to_string(k) + " and " + std::to_string((i+1)*interval) + " = (ORT) " + name, t1.type());
            std::vector<int> rep2 = numbers(timevector2.at(i));
            report(rep2, std::to_string(k) + " and " + std::to_string((i+1)*interval) + " = (KDTREE) " + name, t1.type());
        }


    }
}


void
Tester::slices_of_100_horizontal_independent_of_n(std::string name) {
    for(int k = 17; k < 24; ++k) {
        int testSize = k;
        Timer<unitofmeassure> t1;
        int amount = pow(2,testSize);
        std::vector<int> times;
        for(int i = 0; i < 10; ++i) {
            Ort ort = std::get<0>(buildtrees(testSize));
            for(int h = 0; h < 10; ++h) {
                for(int j = 0; j < 100; ++j) {
                    t1.reset();
                    t1.start();
                    ort.search({{0, (amount/100)*j},{amount, (amount/100)*j + 100}}, 3);
                    t1.stop();

                    times.push_back(t1.duration().count());
                    
                }
            }
        }
        std::vector<int> rep = numbers(times);
        report(rep, std::to_string(k) + " = " + name, t1.type());
    }

}

void
Tester::CACHE_only_create_ort_trees(std::string name) {
    for(int k = 17; k < 22; ++k) {
        Timer<unitofmeassure> t1;
        int testSize = k;
        int amount = pow(2,testSize);
        std::vector<int> times;
        for(int i = 0; i < 1; ++i) {
            t1.reset();
            t1.start();
            Ort ort = std::get<0>(buildtrees(testSize));
            t1.stop();
            times.push_back(t1.duration().count());
        }
    }
}

void
Tester::CACHE_create_and_search_ort_type_four_same(std::string name) {
 for(int k = 17; k < 22; ++k) {
        Timer<unitofmeassure> t1;
        int testSize = k;
        int amount = pow(2,testSize);
        std::vector<int> times;
        Ort ort = std::get<0>(buildtrees(testSize));
        for(int h = 0; h < 10; ++h) {
            for(int j = 0; j < 100; ++j) {
                t1.reset();
                t1.start();
                ort.search({{0, (amount/100)*h},{amount, (amount/100)*h + 100}}, 4);
                t1.stop();

                times.push_back(t1.duration().count());
                
            }
        }
        std::vector<int> rep = numbers(times);
        report(rep, std::to_string(k) + " = " + name, t1.type());
    }
}


void
Tester::CACHE_create_and_search_ort_type_four_different(std::string name) {
 for(int k = 17; k < 22; ++k) {
        Timer<unitofmeassure> t1;
        int testSize = k;
        int amount = pow(2,testSize);
        std::vector<int> times;
        Ort ort = std::get<0>(buildtrees(testSize));
        for(int h = 0; h < 10; ++h) {
            for(int j = 0; j < 100; ++j) {
                t1.reset();
                t1.start();
                ort.search({{0, (amount/100)*j},{amount, (amount/100)*j + 100}}, 4);
                t1.stop();

                times.push_back(t1.duration().count());
                
            }
        }
        std::vector<int> rep = numbers(times);
        report(rep, std::to_string(k) + " = " + name, t1.type());
    }
}


void
Tester::CACHE_create_and_search_ort_type_three_same(std::string name) {
 for(int k = 17; k < 22; ++k) {
        Timer<unitofmeassure> t1;
        int testSize = k;
        int amount = pow(2,testSize);
        std::vector<int> times;
        Ort ort = std::get<0>(buildtrees(testSize));
        for(int h = 0; h < 10; ++h) {
            for(int j = 0; j < 100; ++j) {
                t1.reset();
                t1.start();
                ort.search({{0, (amount/100)*h},{amount, (amount/100)*h + 100}}, 3);
                t1.stop();

                times.push_back(t1.duration().count());
                
            }
        }
        std::vector<int> rep = numbers(times);
        report(rep, std::to_string(k) + " = " + name, t1.type());
    }
}


void
Tester::CACHE_create_and_search_ort_type_three_different(std::string name) {
 for(int k = 17; k < 22; ++k) {
        Timer<unitofmeassure> t1;
        int testSize = k;
        int amount = pow(2,testSize);
        std::vector<int> times;
        Ort ort = std::get<0>(buildtrees(testSize));
        for(int h = 0; h < 10; ++h) {
            for(int j = 0; j < 100; ++j) {
                t1.reset();
                t1.start();
                ort.search({{0, (amount/100)*j},{amount, (amount/100)*j + 100}}, 3);
                t1.stop();

                times.push_back(t1.duration().count());
                
            }
        }
        std::vector<int> rep = numbers(times);
        report(rep, std::to_string(k) + " = " + name, t1.type());
    }
}

void
Tester::test_two_different_findints(std::string name) {
    CACHE_create_and_search_ort_type_three_different("Type three different");

    CACHE_create_and_search_ort_type_four_different("Type four different");

    CACHE_create_and_search_ort_type_three_same("Type three same");
    CACHE_create_and_search_ort_type_four_same("Type four same");
}



void
Tester::slices_of_100_vertical_independent_of_n(std::string name) {
    for(int k = 17; k < 24; ++k) {
        int testSize = k;
        Timer<unitofmeassure> t1;
        int amount = pow(2,testSize);
        std::vector<int> times;
        for(int i = 0; i < 10; ++i) {
            Ort ort = std::get<0>(buildtrees(testSize));
            for(int h = 0; h < 10; ++h) {
                for(int j = 0; j < 100; ++j) {
                    t1.reset();
                    t1.start();
                    ort.search({{(amount/100)*j, 0},{(amount/100)*j + 100, amount}}, 3);
                    t1.stop();

                    times.push_back(t1.duration().count());
                    
                }
            }
        }
        std::vector<int> rep = numbers(times);
        report(rep, std::to_string(k) + " = " + name, t1.type());
    }

}

void Tester::cacheimportance(std::string name) { 
    for(int k = 17; k < 24; ++k) {
        int testSize = k;
        Timer<std::chrono::nanoseconds> t1;
        int amount = pow(2, testSize);
        std::vector<int> times;
        for(int i = 0; i < 10; ++i) {
            Ort ort = std::get<0>(buildtrees(testSize));
            for(int j = 0; j < 100; ++j) {
                for(int h = 0; h < 100; ++h) {
                    t1.reset();
                    t1.start();
                    ort.search({{(amount/100)*j, 0},{(amount/100)*j + 20, amount}}, 3);
                    t1.stop();

                    times.push_back(t1.duration().count());

                }
            }
        }
        std::vector<int> rep = numbers(times);
        report(rep, std::to_string(k) + " = " + name, t1.type());
        

        std::vector<int> times2;
        for(int i = 0; i < 10; ++i) {
            Ort ort = std::get<0>(buildtrees(testSize));
            for(int j = 0; j < 100; ++j) {
                for(int h = 0; h < 100; ++h) {
                    t1.reset();
                    t1.start();
                    ort.search({{(amount/100)*h, 0},{(amount/100)*h + 20, amount}}, 3);
                    t1.stop();

                    times2.push_back(t1.duration().count());

                }
            }
        }

        std::vector<int> rep2 = numbers(times2);
        report(rep2, std::to_string(k) + " = " + name, t1.type());
    }

}

void
Tester::ten_vertical_slices_have_same_performance(std::string name) {
    for(int k = 17; k < 21; ++k) {
        int testSize = k;
        Timer<std::chrono::nanoseconds> t1;
        int amount = pow(2, testSize);
        std::vector<std::vector<int>> times(10, std::vector<int> {});
        for(int i = 0; i < 10; ++i) {
            Ort ort = std::get<0>(buildtrees(testSize));
            for(int j = 0; j < 100; ++j) {
                for(int h = 0; h < 10; ++h) {
                    t1.reset();
                    t1.start();
                    ort.search({{(amount/10)*h, 0},{(amount/10)*h + 50, amount}}, 3);
                    t1.stop();
                    times.at(h).push_back(t1.duration().count());

                }
            }
        }
        std::vector<std::vector<int>> rep = numbers2(times);
        report2(rep, std::to_string(k) + " = " + name, t1.type());
    }
}

void
Tester::ten_vertical_slices_kdtree(std::string name) {
    for(int k = 17; k < 22; ++k) {
        int testSize = k;
        Timer<std::chrono::nanoseconds> t1;
        int amount = pow(2, testSize);
        std::vector<std::vector<int>> times(10, std::vector<int> {});
        for(int i = 0; i < 10; ++i) {
            KDTree kdtree = std::get<1>(buildtrees(testSize));
            for(int j = 0; j < 100; ++j) {
                for(int h = 0; h < 10; ++h) {
                    t1.reset();
                    t1.start();
                    kdtree.search({{(amount/10)*h, 0},{(amount/10)*h + 50, amount}});
                    t1.stop();
                    times.at(h).push_back(t1.duration().count());

                }
            }
        }
        std::vector<std::vector<int>> rep = numbers2(times);
        report2(rep, std::to_string(k) + " = " + name, t1.type());
    }
}



void
Tester::ten_horizontal_slices_have_same_performance(std::string name) {
    for(int k = 17; k < 22; ++k) {
        int testSize = k;
        Timer<std::chrono::nanoseconds> t1;
        int amount = pow(2, testSize);
        std::vector<std::vector<int>> times(10, std::vector<int> {});
        for(int i = 0; i < 10; ++i) {
            Ort ort = std::get<0>(buildtrees(testSize));
            for(int j = 0; j < 100; ++j) {
                for(int h = 0; h < 10; ++h) {
                    t1.reset();
                    t1.start();
                    ort.search({{0, (amount/10)*h},{amount, (amount/10)*h + 50}}, 3);
                    t1.stop();
                    times.at(h).push_back(t1.duration().count());

                }
            }
        }
        std::vector<std::vector<int>> rep = numbers2(times);
        report2(rep, std::to_string(k) + " = " + name, t1.type());
    }
}

void
Tester::ten_horizontal_slices_kdtree(std::string name) {
    for(int k = 17; k < 22; ++k) {
        int testSize = k;
        Timer<std::chrono::nanoseconds> t1;
        int amount = pow(2, testSize);
        std::vector<std::vector<int>> times(10, std::vector<int> {});
        for(int i = 0; i < 10; ++i) {
            KDTree kdtree = std::get<1>(buildtrees(testSize));
            for(int j = 0; j < 100; ++j) {
                for(int h = 0; h < 10; ++h) {
                    t1.reset();
                    t1.start();
                    kdtree.search({{0, (amount/10)*h},{amount, (amount/10)*h + 50}});
                    t1.stop();
                    times.at(h).push_back(t1.duration().count());

                }
            }
        }
        std::vector<std::vector<int>> rep = numbers2(times);
        report2(rep, std::to_string(k) + " = " + name, t1.type());
    }
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
                
                if(a == 0) {
                    times.push_back(a);
                } else {
                    times.push_back(size);
                }
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
                
                if(a == 0) {
                    times.push_back(a);
                } else {
                    times.push_back(size);
                }
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
                
                if(a == 0) {
                    times.push_back(a);
                } else {
                    times.push_back(size);
                }
               
            }
        }
    }
    std::vector<int> rep = numbers(times, true);
    report(rep, name, "times");

}

void
Tester::compare_horizontal_slices_times_between_ort_and_kdtree(std::string name) {
    for(int k = 17; k < 23; ++k) {
        int testSize = k;
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
            for(int h = 0; h < 100; ++h) {
                for(int j = 0; j < 10; ++j) {
                    int a = 0;
                    int size = 10;
                    Region reg {{0, (amount/10)*j},{amount, (amount/10)*j + size}};

                    t1.reset();
                    t1.start();
                    ort.search(reg, 3);
                    t1.stop();

                    t2.reset();
                    t2.start();
                    kdtree.search(reg);
                    t2.stop();


                    while(t1.duration().count() < t2.duration().count()) {
                        a += 5;
                        size += 5;
                        reg = {{0, (amount/10)*j},{amount, (amount/10)*j + size}};



                        t1.reset();
                        t1.start();
                        ort.search(reg, 3);
                        t1.stop();

                        t2.reset();
                        t2.start();
                        kdtree.search(reg);
                        t2.stop();

                    }
                    if(a == 0) {
                        times.push_back(a);
                    } else {
                        times.push_back(size);
                    }
                }
            }
        }
        std::vector<int> rep = numbers(times, true);
        report(rep, std::to_string(k) + " = " + name, "times");
    }

}



void
Tester::compare_vertical_slices_times_between_ort_and_kdtree(std::string name) {
    for(int k = 17; k < 23; ++k) {
        int testSize = k;
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
            for(int h = 0; h < 100; ++h) {
                for(int j = 0; j < 10; ++j) {
                    int a = 0;
                    int size = 10;
                    Region reg {{(amount/10)*j, 0},{(amount/10)*j + size, amount}};

                    t1.reset();
                    t1.start();
                    ort.search(reg, 3);
                    t1.stop();

                    t2.reset();
                    t2.start();
                    kdtree.search(reg);
                    t2.stop();


                    while(t1.duration().count() < t2.duration().count()) {
                        a += 5;
                        size += 5;
                        reg = {{(amount/10)*j, 0},{(amount/10)*j + size, amount}};


                        t1.reset();
                        t1.start();
                        ort.search(reg, 3);
                        t1.stop();

                        t2.reset();
                        t2.start();
                        kdtree.search(reg);
                        t2.stop();

                    }
                    if(a == 0) {
                        times.push_back(a);
                    } else {
                        times.push_back(size);
                    }
                }
            }
        }
        std::vector<int> rep = numbers(times, true);
        report(rep, std::to_string(k) + " = " + name, "times");
    }

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
