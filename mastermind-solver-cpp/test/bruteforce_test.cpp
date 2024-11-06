#include "gtest/gtest.h"

#include "core.h"
#include "bruteforce.h"

using namespace mastermind;

TEST(BruteForce, solve) {
    auto solver = std::make_unique<BruteForce>(GameConfig(6, 4));
    solver->add_interaction(Code{0, 5, 5, 4}, Feedback{0, 1});
    solver->add_interaction(Code{1, 3, 0, 0}, Feedback{1, 2});
    solver->add_interaction(Code{3, 2, 0, 1}, Feedback{2, 1});

    auto actual = solver->solve();
    auto expected = Code{2,0,0,1};
    EXPECT_EQ(expected, actual);
}

TEST(BruteForce, solve2) {
    auto solver = std::make_unique<BruteForce>(GameConfig(6, 4));
    solver->add_interaction(Code{0, 3, 3, 1}, Feedback{0, 1});
    solver->add_interaction(Code{4, 5, 0, 0}, Feedback{1, 2});
    solver->add_interaction(Code{5, 2, 0, 4}, Feedback{2, 1});

    auto actual = solver->solve();
    auto expected = Code{2,0,0,4};
    EXPECT_EQ(expected, actual);
}

TEST(BruteForce, solve_6_10) {
    auto solver = std::make_unique<BruteForce>(GameConfig(6, 10));

    solver->add_interaction(Code{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, Feedback{2, 0});

    auto actual = solver->solve();
    auto expected = Code{0,0,1,1,1,1,1,1,1,1};
    EXPECT_EQ(expected, actual);
}
