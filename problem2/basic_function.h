#ifndef BASIC_FUNCTIONS
#define BASIC_FUNCTIONS

#define _USE_MATH_DEFINES // for C++

#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <any>

class TFunction {
public:
    TFunction() {}
    virtual double operator()(double x) const = 0;
    virtual void ToString() const = 0;
};

class IdentFunc: public TFunction {

public:
    IdentFunc(const std::any &parameters);
    virtual double operator()(double x) const override {
        std::cout << "f(" << x  << ") = " << x << std::endl;
        //std::cerr << __FILE__ << " " << __LINE__ << std::endl;
    }
    virtual void ToString() const override;

};

class ConstFunc: public TFunction {
    double value;

public:
    ConstFunc(const std::any &parameters);
    virtual double operator()(double x) const override {
        std::cout << "f(" << x  << ") = " << value << std::endl;
        //std::cerr << __FILE__ << " " << __LINE__ << std::endl;
    }
    virtual void ToString() const override;
};

class PowerFunc: public TFunction {
    double power;

public:
    PowerFunc(const std::any &parameters);
    virtual double operator()(double x) const override {
        double power_of_func = std::pow(x, power);
        std::cout << "f(" << x  << ") = " << power_of_func << std::endl;
        //std::cerr << __FILE__ << " " << __LINE__ << std::endl;
    }
    virtual void ToString() const override;
};

class ExpFunc: public TFunction {
public:
    ExpFunc(const std::any &parameters);
    virtual double operator()(double x) const override {
        std::cout << "f(" << x  << ") = " << exp(x) << std::endl;
        //std::cerr << __FILE__ << " " << __LINE__ << std::endl;
    }
    virtual void ToString() const override;
};

class PolynomialFunc: public TFunction {
    std::vector<double> coef;

public:
    PolynomialFunc(const std::any &parameters);
    virtual double operator()(double x) const override {
        double sum = 0;
        double curr_power_x;
        for (int curr_coef = 0; curr_coef < coef.size(); ++curr_coef) {
            curr_power_x = std::pow(x, curr_coef);
            sum = sum + coef[curr_coef] * curr_power_x;
        }
        std::cout << "f(" << x  << ") = " << sum << std::endl;
        //std::cerr << __FILE__ << " " << __LINE__ << std::endl;
    }
    virtual void ToString() const override;
};

#endif
