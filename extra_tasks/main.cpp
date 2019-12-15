#include <iostream>
#include <unordered_set>
#include <gtest/gtest.h>

#include "my_iterator.h" 

TEST(ExeptionTests, NO_THROW_TESTS) {
    TRange tR(1, 9, 2);
    EXPECT_NO_THROW(tR.begin());
    EXPECT_NO_THROW(tR.end());
    EXPECT_NO_THROW(tR.GetAllIntegers());
    EXPECT_NO_THROW(tR.end());
    EXPECT_NO_THROW({
        for (auto it = tR.begin(); it != tR.end(); ++it) {
            std::cout << *it << ' ';
        }
        std::cout << std::endl;
    });
    std::unordered_set<TRange, TRangeHash> tR_set;
    TRange tR2(0, 100500, 3);
    TRange tR3(15, 0, 5);
    TRange tR4(10, 11111, 4);
    TRange tR5(0, 1234567, 7);
    EXPECT_NO_THROW(tR_set.insert(tR));
    EXPECT_NO_THROW(tR_set.insert(tR2));
    EXPECT_NO_THROW(tR_set.insert(tR3));
    EXPECT_NO_THROW(tR_set.insert(tR4));
    EXPECT_NO_THROW(tR_set.insert(tR5));
}

TEST(ExeptionTests, THROW_TESTS) {
    EXPECT_THROW(TRange tR(1, 9, 0);, 
                 std::logic_error);
    EXPECT_THROW(TRange tR(1, 1, 2);, 
                 std::logic_error);
}

TEST(OperatorTests, TestResultsOperator) {
    TRange tR(1, 9, 2);
    EXPECT_EQ(3, tR[1]);
    EXPECT_EQ(5, tR[2]);
    TRange tR2(9, 1, 2);
    EXPECT_EQ(7, tR2[1]);
    EXPECT_EQ(5, tR2[2]);
    EXPECT_EQ(5, tR.GetSize());
    EXPECT_EQ(5, tR2.GetSize());
    // N < M
    EXPECT_EQ(1, *(tR.begin()));
    EXPECT_EQ(11, *(tR.end()));
    auto it = tR.begin();
    EXPECT_EQ(3, *(++it));
    EXPECT_EQ(5, *(++it));
    EXPECT_EQ(7, *(++it));
    EXPECT_EQ(9, *(++it));
    // N > M
    EXPECT_EQ(9, *(tR2.begin()));
    EXPECT_EQ(-1, *(tR2.end()));
    auto it2 = tR2.begin();
    EXPECT_EQ(7, *(++it2));
    EXPECT_EQ(5, *(++it2));
    EXPECT_EQ(3, *(++it2));
    EXPECT_EQ(1, *(++it2));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
