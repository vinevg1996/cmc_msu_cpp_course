#include <memory>
#include <iostream>

int main() {

    using constPtr = std::shared_ptr<int>;

    std::shared_ptr<int> sp1, sp2, sp3;
    std::weak_ptr<int> wp;
                                       // sharing group:
                                       // --------------
    sp1 = std::make_shared<int> (20);    // sp1
    wp = sp1;                            // sp1, wp

    //sp2 = wp.lock();                     // sp1, wp, sp2
    
    //sp1.reset();                         //      wp, sp2
    //sp2.reset();

    sp2 = static_cast<std::shared_ptr<int>>(wp.lock());
    sp3 = (std::shared_ptr<int>)(wp.lock());

    //sp1.reset();                         //      wp, sp2
    //sp2.reset();


    //std::cout << "*sp1: " << *sp1 << '\n';
    //std::cout << "*sp2: " << *sp2 << '\n';

	return 0;
}
