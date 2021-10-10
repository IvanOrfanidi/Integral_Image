#include <gtest/gtest.h>
#include <include/sum.h>

TEST(TestSuml, sum_eq)
{
    // arrange
    const int a = 2;
    const int b = 3;

    // act
    const auto res = sum(a, b);

    // assert
    EXPECT_EQ(res, 5);
}

TEST(TestSuml, sum_ne)
{
    // arrange
    const int a = 1;
    const int b = 2;

    // act
    const auto res = sum(a, b);

    // assert
    EXPECT_NE(res, 4);
}