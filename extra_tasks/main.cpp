#include <iostream>
#include <unordered_set>

#include "my_iterator.h" 

int main() {
    TRange tR(1, 9, 2);
    //TRange tR(1, 3, 2);
    
    tR.GetAllIntegers();
    std::cout << "*(tR.begin()) = " << *(tR.begin()) << std::endl;
    std::cout << "*(tr.end()) = " << *(tR.end()) << std::endl;
    for (auto it = tR.begin(); it != tR.end(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;

    try {
        TRange noncorrect_tR1(1, 3, 0);
    } catch(std::logic_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    try {
        TRange noncorrect_tR2(1, 1, 2);
    } catch(std::logic_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    
    TRange tR2(0, 100500, 3);
    TRange tR3(15, 0, 5);
    TRange tR4(10, 11111, 4);
    TRange tR5(0, 1234567, 7);
    std::unordered_set<TRange, TRangeHash> tR_set;
    tR_set.insert(tR);
    tR_set.insert(tR2);
    tR_set.insert(tR3);
    tR_set.insert(tR4);
    tR_set.insert(tR5);
    //tR_set.insert(tR3);
    auto fn = tR_set.hash_function();
    std::cout << "fn = " << fn(tR) << std::endl;
    std::cout << "fn2 = " << fn(tR2) << std::endl;
    std::cout << "fn3 = " << fn(tR3) << std::endl;
    std::cout << "fn4 = " << fn(tR4) << std::endl;
    std::cout << "fn5 = " << fn(tR5) << std::endl;

    return 0;
}
