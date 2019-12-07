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
    std::vector<TFunctionPtr> cont_of_func;

    auto ident_func = factory.CreateObject("ident function");
    auto const_func = factory.CreateObject("const function", 2);
    auto power_func = factory.CreateObject("power function", 5);
    auto exp_func = factory.CreateObject("exp function");
    auto poly_func = factory.CreateObject("poly function", std::vector<int>({1, 2, 3, 4}));

    cont_of_func.push_back(ident_func);
    cont_of_func.push_back(const_func);
    cont_of_func.push_back(power_func);
    cont_of_func.push_back(exp_func);
    cont_of_func.push_back(poly_func);

    std::cout << "ToString" << std::endl;
    for (const auto &ptr: cont_of_func) {
        std::cout << ptr->ToString() << ": for x = 3 is " << (*ptr)(3) << std::endl;
    }

    auto new_func = ident_func + const_func;
    std::cout << new_func.ToString() << std::endl;
    std::cout << new_func(3) << std::endl;
    std::cout << "Derivation = " << ident_func->GetDerive(1) << std::endl;
    std::cout << "Derivation = " << poly_func->GetDerive(3) << std::endl;

    auto test_minus_func = poly_func - power_func;
    std::cout << test_minus_func.ToString() << std::endl;
    std::cout << test_minus_func(3) << std::endl;

    auto null_func = factory.CreateObject("const function", 0);
    auto test_div_func = ident_func / null_func;
    std::cout << test_div_func.ToString() << std::endl;
    std::cout << test_div_func(3) << std::endl;
    
    double Calculate_function_root(const std::shared_ptr<TFunction> &func,
                                   double initial_value,
                                   int iter_number);

    
    auto poly_func2 = factory.CreateObject("poly function", std::vector<int>({1, -2, 1}));    
    
    auto ptr = power_func + exp_func;
    std::cout << "__________________" << std::endl;
    std::cout << ptr.ToString() << std::endl;
    std::cout << ptr(3) << std::endl;

    //auto ptr1 = power_func + "abc";
    std::cout << "__________________" << std::endl;
    double root = Calculate_function_root(poly_func2, -2, 10);

    std::cout << "root = " << root << std::endl;

    return 0;
}
