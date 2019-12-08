#include <iostream>
#include <functional>
#include <any>
#include <gtest/gtest.h>
#include "factory_functions.h"
#include "basic_function.h"

TEST(ExeptionTests, NO_THROW_TESTS) {
    TFactory factory;
    EXPECT_NO_THROW(factory.CreateObject("ident function"));
    EXPECT_NO_THROW(factory.CreateObject("const function", 3));
    EXPECT_NO_THROW(factory.CreateObject("const function", 3.0));
    EXPECT_NO_THROW(factory.CreateObject("power function", 4));
    EXPECT_NO_THROW(factory.CreateObject("power function", 4.0));
    EXPECT_NO_THROW(factory.CreateObject("exp function"));
    EXPECT_NO_THROW(factory.CreateObject("poly function", std::vector<int>({1, 2, 3, 4})));
    EXPECT_NO_THROW(factory.CreateObject("poly function", std::vector<double>({1.0, 2.0, 3.0, 4.0})));
    // ident function with others
    EXPECT_NO_THROW({
        auto f = factory.CreateObject("ident function");
        auto g = factory.CreateObject("const function", 3);
        auto res1 = f + g;
        auto res2 = f - g;
        auto res3 = f * g;
        auto res4 = f / g;
    });
    EXPECT_NO_THROW({
        auto f = factory.CreateObject("ident function");
        auto g = factory.CreateObject("power function", 4);
        auto res1 = f + g;
        auto res2 = f - g;
        auto res3 = f * g;
        auto res4 = f / g;
    });
    EXPECT_NO_THROW({
        auto f = factory.CreateObject("ident function");
        auto g = factory.CreateObject("exp function");
        auto res1 = f + g;
        auto res2 = f - g;
        auto res3 = f * g;
        auto res4 = f / g;
    });
    EXPECT_NO_THROW({
        auto f = factory.CreateObject("ident function");
        auto g = factory.CreateObject("poly function", std::vector<int>({1, 2, 3, 4}));
        auto res1 = f + g;
        auto res2 = f - g;
        auto res3 = f * g;
        auto res4 = f / g;
    });
    // const function with others
    EXPECT_NO_THROW({
        auto f = factory.CreateObject("const function", 3);
        auto g = factory.CreateObject("power function", 4);
        auto res1 = f + g;
        auto res2 = f - g;
        auto res3 = f * g;
        auto res4 = f / g;
    });
    EXPECT_NO_THROW({
        auto f = factory.CreateObject("const function", 3);
        auto g = factory.CreateObject("exp function");
        auto res1 = f + g;
        auto res2 = f - g;
        auto res3 = f * g;
        auto res4 = f / g;
    });
    EXPECT_NO_THROW({
        auto f = factory.CreateObject("const function", 3);
        auto g = factory.CreateObject("poly function", std::vector<int>({1, 2, 3, 4}));
        auto res1 = f + g;
        auto res2 = f - g;
        auto res3 = f * g;
        auto res4 = f / g;
    });
    // power function with others
    EXPECT_NO_THROW({
        auto f = factory.CreateObject("power function", 4);
        auto g = factory.CreateObject("exp function");
        auto res1 = f + g;
        auto res2 = f - g;
        auto res3 = f * g;
        auto res4 = f / g;
    });
    EXPECT_NO_THROW({
        auto f = factory.CreateObject("power function", 4);
        auto g = factory.CreateObject("poly function", std::vector<int>({1, 2, 3, 4}));
        auto res1 = f + g;
        auto res2 = f - g;
        auto res3 = f * g;
        auto res4 = f / g;
    });
    // exp function with others
    EXPECT_NO_THROW({
        auto f = factory.CreateObject("exp function");
        auto g = factory.CreateObject("poly function", std::vector<int>({1, 2, 3, 4}));
        auto res1 = f + g;
        auto res2 = f - g;
        auto res3 = f * g;
        auto res4 = f / g;
    });
}

TEST(ExeptionTests, THROW_TESTS) {
    TFactory factory;
    EXPECT_THROW(factory.CreateObject("const function"), 
                 std::bad_cast);
    EXPECT_THROW(factory.CreateObject("power function"), 
                 std::bad_cast);
    EXPECT_THROW(factory.CreateObject("power function", 'a'), 
                 std::bad_cast);
    EXPECT_THROW(factory.CreateObject("poly function", 4), 
                 std::bad_cast);
    
    EXPECT_THROW({
            auto f = factory.CreateObject("poly function", std::vector<double>({1.0, 2.0, 3.0, 4.0}));
            auto g = f + "abc";
        }, 
        std::logic_error
    );
    EXPECT_THROW({
            auto f = factory.CreateObject("const function", 4);
            auto g = f + 17;
        }, 
        std::logic_error
    );
    EXPECT_THROW({
            auto f = factory.CreateObject("exp");
            auto g = f + std::sin(1);
        }, 
        std::logic_error
    );
    EXPECT_THROW({
            auto f = factory.CreateObject("exp function");
            auto g = factory.CreateObject("const function", 0);
            auto h = f / g;
            double h_value_1 = (*h)(1);
        },
        std::logic_error
    );
}

TEST(OperatorTests, TestResultsOperator) {
    TFactory factory;
    auto f1 = factory.CreateObject("ident function");
    auto f2 = factory.CreateObject("const function", 3);
    auto f3 = factory.CreateObject("power function", 4);
    auto f4 = factory.CreateObject("exp function");
    auto f5 = factory.CreateObject("poly function", std::vector<int>({1, 2, 3}));
    
    auto f_2 = factory.CreateObject("power function", 2);
    auto f_3 = factory.CreateObject("ident function", 1);
    auto F = f5 - f_2 + f_3;

    auto f_4 = factory.CreateObject("ident function", 1);
    auto f_5 = factory.CreateObject("const function", 6);
    auto f_6 = factory.CreateObject("const function", 3);
    auto F2 = f_4 * f_5 / f_6;

    EXPECT_EQ(4, (*f1)(4));
    EXPECT_EQ(3, (*f2)(4));
    EXPECT_EQ(256, (*f3)(4));
    EXPECT_EQ(std::exp(4), (*f4)(4));
    EXPECT_EQ(57, (*f5)(4));
    EXPECT_EQ(15, (*F)(2));
    EXPECT_NEAR(4, (*F2)(2), 0.001);
}

TEST(DerivationTests, TestResultsDerivation) {
    TFactory factory;
    auto f1 = factory.CreateObject("ident function");
    auto f2 = factory.CreateObject("const function", 3);
    auto f3 = factory.CreateObject("power function", 4);
    auto f4 = factory.CreateObject("exp function");
    auto f5 = factory.CreateObject("poly function", std::vector<int>({1, 2, 3}));

    EXPECT_EQ(1, f1->GetDerive(4));
    EXPECT_EQ(0, f2->GetDerive(4));
    EXPECT_EQ(108, f3->GetDerive(3));
    EXPECT_EQ(std::exp(4), f4->GetDerive(4));
    EXPECT_EQ(26, f5->GetDerive(4));
}

TEST(ToStringTests, TestConvertToString) {
    TFactory factory;
    auto f1 = factory.CreateObject("ident function");
    auto f2 = factory.CreateObject("const function", 3);
    auto f3 = factory.CreateObject("power function", 4);
    auto f4 = factory.CreateObject("exp function");
    auto f5 = factory.CreateObject("poly function", std::vector<int>({1, 2, 3}));

    EXPECT_EQ("x", f1->ToString());
    EXPECT_EQ("e^x", f4->ToString());
}

TEST(FindRootTests, TestFindRoot) {
    TFactory factory;
    auto f1 = factory.CreateObject("ident function");
    auto f2 = factory.CreateObject("const function", 1);
    auto f_2 = factory.CreateObject("const function", 2);
    auto f3 = factory.CreateObject("power function", 2);
    auto f4 = factory.CreateObject("exp function");
    auto f5 = factory.CreateObject("poly function", std::vector<int>({1, -2, 1}));
    auto f6 = f5 - f2;

    EXPECT_NEAR(0, Calculate_function_root(f1, -2, 10), 0.001);
    EXPECT_NEAR(0, Calculate_function_root(f3, -3, 10), 0.01);
    EXPECT_NEAR(1, Calculate_function_root(f5, 0, 10), 0.001);
    EXPECT_NEAR(0, Calculate_function_root(f6, 0, 10), 0.001);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
