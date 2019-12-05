#include <iostream>
#include <functional>
#include "factory_functions.h"
#include "basic_function.h"

using TFunctionPtr = std::shared_ptr<TFunction>;

int main() {
    TFactory factory;
    auto functions = factory.GetAvailableObjects();
    std::cout << "Available functions:" << std::endl;
    for (const auto& func : functions) {
        std::cout << func << "; ";
    }
    std::cout << std::endl;

    //std::initializer_list<int> list = {1, 2, 3};

    auto ident_func = factory.CreateObject("ident function");
    auto const_func = factory.CreateObject("const function", 2);
    auto power_func = factory.CreateObject("power function", 5);
    auto exp_func = factory.CreateObject("exp function");
    auto poly_func = factory.CreateObject("poly function", std::vector<int>({1, 2, 3}));
    (*ident_func)(3);
    (*const_func)(3);
    (*power_func)(3);
    (*exp_func)(3);
    (*poly_func)(3);

    std::vector<TFunctionPtr> cont;
    //cont.push_back(ident_func);

    return 0;
}
