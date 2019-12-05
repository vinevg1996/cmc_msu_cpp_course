#include <map>
#include <any>

#include "factory_functions.h"
#include "basic_function.h"

class TFactory::TImpl {
    class ICreator {
    public:
        virtual ~ICreator(){}
        virtual std::unique_ptr<TFunction> Create(const std::any &parameters) const = 0;
        //virtual std::unique_ptr<TFunction> Create(double value) const = 0;
    };

    using TCreatorPtr = std::shared_ptr<ICreator>;
    using TRegisteredCreators = std::map<std::string, TCreatorPtr>;
    
    TRegisteredCreators RegisteredCreators;

public:

    template <typename TCurrentObject>
    class TCreator: public ICreator {
        std::unique_ptr<TFunction> Create(const std::any &parameters) const override {
            return std::make_unique<TCurrentObject>(parameters);
        }
    };

    TImpl() { 
        RegisterAll();
    }

    template <typename T>
    void RegisterCreator(const std::string& name) {
        RegisteredCreators[name] = std::make_shared<TCreator<T>>();
    }

    void RegisterAll() {
        RegisterCreator<IdentFunc>("ident function");
        RegisterCreator<ConstFunc>("const function");
        RegisterCreator<PowerFunc>("power function");
        RegisterCreator<ExpFunc>("exp function");
        RegisterCreator<PolynomialFunc>("poly function");
    }

    std::unique_ptr<TFunction> CreateObject(const std::string& n, const std::any &parameters) const {
        auto creator = RegisteredCreators.find(n);
        if (creator == RegisteredCreators.end()) {
            return nullptr;
        } else {
            return creator->second->Create(parameters);
        }
    }

    std::vector<std::string> GetAvailableObjects () const {
        std::vector<std::string> result;
        for (const auto& creatorPair : RegisteredCreators) {
            result.push_back(creatorPair.first);
        }
        return result;
    }

};

std::unique_ptr<TFunction> TFactory::CreateObject(const std::string& n, const std::any &parameters) {
    return Impl->CreateObject(n, parameters);
}

TFactory::TFactory() 
    : Impl(std::make_unique<TFactory::TImpl>()) {}

TFactory::~TFactory(){}

std::vector<std::string> TFactory::GetAvailableObjects() const {
    return Impl->GetAvailableObjects();
}
