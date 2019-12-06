#ifndef FACTORY
#define FACTORY

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <cmath>

#include "basic_function.h"

class TFactory {
    class TImpl;
    std::shared_ptr<const TImpl> Impl;

public:
    TFactory();
    ~TFactory();
    std::shared_ptr<TFunction> CreateObject(const std::string& n, const std::any &parameters = nullptr);
    std::vector<std::string> GetAvailableObjects() const;
};

#endif