#include "core.h"
#include "gtest/gtest.h"

using namespace mastermind;

TEST(core, eval_guess){
    {
        auto actual = eval_guess({0, 5, 5, 4}, {2, 0, 0, 1});
        EXPECT_EQ(0, actual.full_matches);
        EXPECT_EQ(1, actual.partial_matches);
    }
    {
        auto actual = eval_guess({1,3,0,0}, {2,0,0,1});
        EXPECT_EQ(1, actual.full_matches);
        EXPECT_EQ(2, actual.partial_matches);
    }
    {
        auto actual = eval_guess({3,2,0,1}, {2,0,0,1});
        EXPECT_EQ(2, actual.full_matches);
        EXPECT_EQ(1, actual.partial_matches);
    }
    {
        auto actual = mastermind::eval_guess({2,0,0,1}, {2,0,0,1});
        EXPECT_EQ(4, actual.full_matches);
        EXPECT_EQ(0, actual.partial_matches);
    }
}