#ifndef BASIC_FUNCTIONS
#define BASIC_FUNCTIONS

#define _USE_MATH_DEFINES // for C++

#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <memory>
#include <any>

class TFunctionPlus;
class TFunctionMinus;
class TFunctionMult;
class TFunctionDiv;

class TFunction {
public:
    TFunction() {}
    virtual double operator()(double x) const = 0;
    virtual std::string ToString() const = 0;
    virtual double GetDerive(double x) const = 0;

    friend std::shared_ptr<TFunctionPlus> operator+(const std::shared_ptr<TFunction> &left, 
                                   					const std::any &right);
    friend std::shared_ptr<TFunctionMinus> operator-(const std::shared_ptr<TFunction> &left, 
                                    				 const std::any &right);
    friend std::shared_ptr<TFunctionMult> operator*(const std::shared_ptr<TFunction> &left, 
                                   					const std::any &right);
    friend std::shared_ptr<TFunctionDiv> operator/(const std::shared_ptr<TFunction> &left, 
                                  				   const std::any &right);
};

class IdentFunc: public TFunction {

public:
    IdentFunc(const std::any &parameters);
    virtual double operator()(double x) const override;
    virtual std::string ToString() const override;
    virtual double GetDerive(double x) const override;
};

class ConstFunc: public TFunction {
    double value;

public:
    ConstFunc(const std::any &parameters);
    virtual double operator()(double x) const override;
    virtual std::string ToString() const override;
    virtual double GetDerive(double x) const override;
};

class PowerFunc: public TFunction {
    double power;

public:
    PowerFunc(const std::any &parameters);
    virtual double operator()(double x) const override;
    virtual std::string ToString() const override;
    virtual double GetDerive(double x) const override;
};

class ExpFunc: public TFunction {
public:
    ExpFunc(const std::any &parameters);
    virtual double operator()(double x) const override;
    virtual std::string ToString() const override;
    virtual double GetDerive(double x) const override;
};

class PolynomialFunc: public TFunction {
    std::vector<double> coef;

public:
    PolynomialFunc(const std::any &parameters);
    virtual double operator()(double x) const override;
    virtual std::string ToString() const override;
    virtual double GetDerive(double x) const override;
};

class TFunctionPlus: public TFunction {
    std::shared_ptr<TFunction> func1;
    std::shared_ptr<TFunction> func2;

public:
    TFunctionPlus(const std::shared_ptr<TFunction> &func1,
                  const std::shared_ptr<TFunction> &func2);
    virtual double operator()(double x) const override;
    virtual std::string ToString() const override;
    virtual double GetDerive(double x) const override;
};

class TFunctionMinus: public TFunction {
    std::shared_ptr<TFunction> func1;
    std::shared_ptr<TFunction> func2;

public:
    TFunctionMinus(const std::shared_ptr<TFunction> &func1,
                   const std::shared_ptr<TFunction> &func2);
    virtual double operator()(double x) const override;
    virtual std::string ToString() const override;
    virtual double GetDerive(double x) const override;
};

class TFunctionMult: public TFunction {
    std::shared_ptr<TFunction> func1;
    std::shared_ptr<TFunction> func2;

public:
    TFunctionMult(const std::shared_ptr<TFunction> &func1,
                  const std::shared_ptr<TFunction> &func2);
    virtual double operator()(double x) const override;
    virtual std::string ToString() const override;
    virtual double GetDerive(double x) const override;
};

class TFunctionDiv: public TFunction {
    std::shared_ptr<TFunction> func1;
    std::shared_ptr<TFunction> func2;

public:
    TFunctionDiv(const std::shared_ptr<TFunction> &func1,
                 const std::shared_ptr<TFunction> &func2);
    virtual double operator()(double x) const override;
    virtual std::string ToString() const override;
    virtual double GetDerive(double x) const override;
};

double Calculate_function_root(const std::shared_ptr<TFunction> &func,
                               double initial_value,
                               int iter_number);

#endif
