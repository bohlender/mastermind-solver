#include <cstdio>
#include "api.h"
#include "gtest/gtest.h"

using namespace mastermind;

TEST(API, solve) {
    auto solver = Solver_ctor(6,4);

    auto guess1 = new int[]{0, 5, 5, 4};
    add_interaction(solver, guess1, 0, 1);
    delete[] guess1;

    auto guess2 = new int[]{1, 3, 0, 0};
    add_interaction(solver, guess2, 1, 2);
    delete[] guess2;

    auto guess3 = new int[]{3, 2, 0, 1};
    add_interaction(solver, guess3, 2, 1);
    delete[] guess3;

    auto secret = new int[4];
    auto ok = solve(solver, secret);

    EXPECT_TRUE(ok);
    EXPECT_EQ(std::vector<int>({2,0,0,1}), std::vector(secret, secret+4));

    delete[] secret;
    Solver_dtor(solver);
}