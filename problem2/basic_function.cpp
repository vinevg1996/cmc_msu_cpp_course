#include <initializer_list>

#include "basic_function.h"

// IdentFunc
IdentFunc::IdentFunc(const std::any &parameters) 
        : TFunction() {
    std::cout << "IdentFunc" << std::endl;
}

void IdentFunc::ToString() const {
    std::cout << "x";
}

// ConstFunc
ConstFunc::ConstFunc(const std::any &parameters) 
        : TFunction() {
    try {
        this->value = std::any_cast<double>(parameters);
    } catch (const std::bad_any_cast& e) {
        int int_value = std::any_cast<int>(parameters);
        this->value = static_cast<double>(int_value);
    }
    std::cout << "ConstFunc" << std::endl;
}

void ConstFunc::ToString() const {
    std::cout << value;
}

// PowerFunc
PowerFunc::PowerFunc(const std::any &parameters)
        : TFunction() {
    try {
        this->power = std::any_cast<double>(parameters);
    } catch (const std::bad_any_cast& e) {
        int int_value = std::any_cast<int>(parameters);
        this->power = static_cast<double>(int_value);
    }
    std::cout << "PowerFunc" << std::endl;
}

void PowerFunc::ToString() const {
    std::cout << "x^" << power;
}

// ExpFunc
ExpFunc::ExpFunc(const std::any &parameters) 
        : TFunction() {
    std::cout << "ExpFunc" << std::endl;
}

void ExpFunc::ToString() const {
    std::cout << "e^x";
}

// PolynomialFunc
PolynomialFunc::PolynomialFunc(const std::any &parameters)
        : TFunction() {
    try {
        this->coef = std::any_cast<std::vector<double>>(parameters);
    } catch (const std::bad_any_cast& e) {
        std::vector<int> int_vector = std::any_cast<std::vector<int>>(parameters);
        for (const auto &elem: int_vector) {
            this->coef.push_back(static_cast<double>(elem));
        }
    }
    
    std::cout << "PolyFunc" << std::endl;
}

void PolynomialFunc::ToString() const {
    for (int curr_coef = 0; curr_coef < coef.size(); ++curr_coef) {
        std::cout << coef[curr_coef] << "x^" << curr_coef;
        if (curr_coef != coef.size() - 1) {
            std::cout << "+";
        }
    }
    std::cout << std::endl;
}
