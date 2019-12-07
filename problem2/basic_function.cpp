#include <initializer_list>

#include "basic_function.h"

#define _USE_MATH_DEFINES // for C++

// IdentFunc
IdentFunc::IdentFunc(const std::any &parameters) 
        : TFunction() {
    std::cout << "IdentFunc" << std::endl;
}

double IdentFunc::operator()(double x) const {
    return x;
}

std::string IdentFunc::ToString() const {
    return "x";
}

double IdentFunc::GetDerive(double x) const {
    return 1;
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

double ConstFunc::operator()(double x) const {
    return value;
}

std::string ConstFunc::ToString() const {
    return std::to_string(value);
}

double ConstFunc::GetDerive(double x) const {
    return 0;
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

double PowerFunc::operator()(double x) const {
    return std::pow(x, power);
}

std::string PowerFunc::ToString() const {
    std::string str;
    str = "x^" + std::to_string(power);
    return str;
}

double PowerFunc::GetDerive(double x) const {
    return power * std::pow(x, power - 1);
}

// ExpFunc
ExpFunc::ExpFunc(const std::any &parameters) 
        : TFunction() {
    std::cout << "ExpFunc" << std::endl;
}

std::string ExpFunc::ToString() const {
    return "e^x";
}

double ExpFunc::operator()(double x) const {
    return std::exp(x);
}

double ExpFunc::GetDerive(double x) const {
    return std::exp(x);
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

double PolynomialFunc::operator()(double x) const {
    double sum = 0;
    double curr_power_x;
    for (int curr_coef = 0; curr_coef < coef.size(); ++curr_coef) {
        curr_power_x = std::pow(x, curr_coef);
        sum = sum + coef[curr_coef] * curr_power_x;
    }
    return sum;
}

std::string PolynomialFunc::ToString() const {
    std::string str;
    for (int curr_coef = 0; curr_coef < coef.size(); ++curr_coef) {
        str += std::to_string(coef[curr_coef]);
        str += " * x^";
        str += std::to_string(curr_coef);
        if (curr_coef != coef.size() - 1) {
            str = str + " + ";
        }
    }
    return str;
}

double PolynomialFunc::GetDerive(double x) const {
    double derive_sum = 0;
    double curr_power_x;
    for (int curr_coef = 1; curr_coef < coef.size(); ++curr_coef) {
        curr_power_x = std::pow(x, curr_coef - 1);
        derive_sum += coef[curr_coef] * curr_coef * curr_power_x;
    }
    return derive_sum;
}

//TFunctionPlus
TFunctionPlus::TFunctionPlus(const std::shared_ptr<TFunction> &func1,
                             const std::shared_ptr<TFunction> &func2) 
        : func1(func1)
        , func2(func2) {}

double TFunctionPlus::operator()(double x) const {
    return (*func1)(x) + (*func2)(x);
}

std::string TFunctionPlus::ToString() const {
    return "(" + func1->ToString() + ")" + " + " + "(" + func2->ToString() + ")";
}

double TFunctionPlus::GetDerive(double x) const {
    return func1->GetDerive(x) + func2->GetDerive(x);
}

//TFunctionMinus
TFunctionMinus::TFunctionMinus(const std::shared_ptr<TFunction> &func1,
                               const std::shared_ptr<TFunction> &func2) 
        : func1(func1)
        , func2(func2) {}

double TFunctionMinus::operator()(double x) const {
    return (*func1)(x) - (*func2)(x);
}

std::string TFunctionMinus::ToString() const {
    return "(" + func1->ToString() + ")" + " - " + "(" + func2->ToString() + ")";
}

double TFunctionMinus::GetDerive(double x) const {
    return func1->GetDerive(x) - func2->GetDerive(x);
}

//TFunctionMult
TFunctionMult::TFunctionMult(const std::shared_ptr<TFunction> &func1,
                             const std::shared_ptr<TFunction> &func2) 
        : func1(func1)
        , func2(func2) {}

double TFunctionMult::operator()(double x) const {
    return (*func1)(x) * (*func2)(x);
}

std::string TFunctionMult::ToString() const {
    return "(" + func1->ToString() + ")" + " * " + "(" + func2->ToString() + ")";
}

double TFunctionMult::GetDerive(double x) const {
    return func1->GetDerive(x) * (*func2)(x) + func2->GetDerive(x) * (*func1)(x);
}

//TFunctionDiv
TFunctionDiv::TFunctionDiv(const std::shared_ptr<TFunction> &func1,
                             const std::shared_ptr<TFunction> &func2) 
        : func1(func1)
        , func2(func2) {}

double TFunctionDiv::operator()(double x) const {
    return (*func1)(x) / (*func2)(x);
}

std::string TFunctionDiv::ToString() const {
    return "(" + func1->ToString() + ")" + " / " + "(" + func2->ToString() + ")";
}

double TFunctionDiv::GetDerive(double x) const {
    return (func1->GetDerive(x) * (*func2)(x) - func2->GetDerive(x) * (*func1)(x)) / std::pow((*func2)(x), 2);
}

// operators
TFunctionPlus operator+(const std::shared_ptr<TFunction> &left, 
                        const std::any &right) {
    std::shared_ptr<TFunction> right_arg;
    try {
        right_arg = std::any_cast<std::shared_ptr<TFunction>>(right);
    } catch(std::bad_cast& e) {
        throw std::logic_error("showd be: shared_ptr<TFunction> + shared_ptr<TFunction>");
    }
    return TFunctionPlus(left, right_arg);
}

TFunctionMinus operator-(const std::shared_ptr<TFunction> &left, 
                         const std::any &right) {
    std::shared_ptr<TFunction> right_arg;
    try {
        right_arg = std::any_cast<std::shared_ptr<TFunction>>(right);
    } catch(std::bad_cast& e) {
        throw std::logic_error("showd be: shared_ptr<TFunction> + shared_ptr<TFunction>");
    }
    return TFunctionMinus(left, right_arg);
}

TFunctionMult operator*(const std::shared_ptr<TFunction> &left, 
                        const std::any &right) {
    std::shared_ptr<TFunction> right_arg;
    try {
        right_arg = std::any_cast<std::shared_ptr<TFunction>>(right);
    } catch(std::bad_cast& e) {
        throw std::logic_error("showd be: shared_ptr<TFunction> + shared_ptr<TFunction>");
    }
    return TFunctionMult(left, right_arg);
}

TFunctionDiv operator/(const std::shared_ptr<TFunction> &left, 
                       const std::any &right) {
    std::shared_ptr<TFunction> right_arg;
    try {
        right_arg = std::any_cast<std::shared_ptr<TFunction>>(right);
    } catch(std::bad_cast& e) {
        throw std::logic_error("showd be: shared_ptr<TFunction> + shared_ptr<TFunction>");
    }
    return TFunctionDiv(left, right_arg);
}

double Calculate_function_root(const std::shared_ptr<TFunction> &func,
                               double initial_value,
                               int iter_number) {
    double x = initial_value;
    for (int curr_iter = 0; curr_iter < iter_number; ++curr_iter) {
        x = x - (*func)(x) / func->GetDerive(x);
    }
    return x;
}