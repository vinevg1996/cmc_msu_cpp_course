#include <ctime>
#include <map>
#include <iostream>
/*
int main() {
    typedef std::map<unsigned int,unsigned int> map;

    const unsigned int k=100000;
    const unsigned int reps=10;

    // Avoid edge cases by padding either end
    map srcMap;
    {
        for(unsigned int i=0; i!=k;++i) {
            srcMap.insert(std::make_pair(i,i));
        }
        unsigned int l=3*k;
        for(unsigned int i=2*k; i!=l;++i) {
            srcMap.insert(std::make_pair(i,i));
        }
    }

    std::cout << "Hint is always the position of the preceding value\n";
    for(unsigned int i=0; i!=reps;++i)
    {
        map testMap(srcMap);
        map::iterator p=testMap.lower_bound(k-1);
        unsigned int l=2*k;
        std::clock_t start = std::clock();
        for(unsigned int i=k; i!=l;++i) {
            p=testMap.insert(p,std::make_pair(i,i));
        }
        std::clock_t end = std::clock();
        std::cout << static_cast<double>((end - start) ) << " ";
    }
    std::cout << std::endl;

    std::cout << "Hint is always the position of the following value\n";
    for(unsigned int i=0; i!=reps;++i)
    {
        map testMap(srcMap);
        map::iterator p=testMap.lower_bound(2*k);
        unsigned int l=k-1;
        std::clock_t start = std::clock();
        for(unsigned int i=2*k-1; i!=l;--i) {
            p=testMap.insert(p,std::make_pair(i,i));
        }
        std::clock_t end = std::clock();
        std::cout << static_cast<double>((end - start) ) << " ";
    }
    std::cout << std::endl;

    std::cout << "Hint is always the start of the container\n";
    for(unsigned int i=0; i!=reps;++i)
    {
        map testMap(srcMap);
        unsigned int l=2*k;
        std::clock_t start = std::clock();
        for(unsigned int i=k; i!=l;++i) {
            testMap.insert(testMap.begin(),std::make_pair(i,i));
        }
        std::clock_t end = std::clock();
        std::cout << static_cast<double>((end - start)) << " ";
    }
    std::cout << std::endl;

    std::cout << "No hint\n";
    for(unsigned int i=0; i!=reps;++i)
    {
        map testMap(srcMap);
        unsigned int l=2*k;
        std::clock_t start = std::clock();
        for(unsigned int i=k; i!=l;++i) {
            testMap.insert(std::make_pair(i,i));
        }
        std::clock_t end = std::clock();
        std::cout << static_cast<double>((end - start)) << " ";
    }
    std::cout << std::endl;

    return 0;
}
*/

int main(int argc, char const *argv[]) {
    std::map<int, int> map_without_hint;
    int mode = std::stoi(argv[1]);
    switch(mode) {
    case 1:  
        for (int i = 0; i < 1000000; ++i) {
            map_without_hint.insert(std::make_pair(i, i));
        }
        break;

    case 2:     
        for (int i = 0; i < 1000000; ++i) {
            map_without_hint.insert(std::make_pair(i, i));
        }
        break;

    case 3: 
        for (int i = 1000000; i >= 0; --i) {
            if (i != 500000) {
                map_without_hint.insert(std::make_pair(i, i));
            }
        }
        break;

    default: 
        std::cout << "This input value is not found" << std::endl;
        break;
    }

    return 0;
}
