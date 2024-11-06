#include "gtest/gtest.h"
#include "sat.h"

using namespace mastermind;

TEST(Sat, solve_6_4) {
    auto solver = std::make_unique<Sat>(GameConfig(6, 4));

    solver->add_interaction(Code{0, 5, 5, 4}, Feedback{0, 1});
    solver->add_interaction(Code{1, 3, 0, 0}, Feedback{1, 2});
    solver->add_interaction(Code{3, 2, 0, 1}, Feedback{2, 1});

    auto actual = solver->solve();
    auto pred = [](const Code& actual) {
        return actual == Code{2,0,0,1} || actual == Code{3,0,0,2};
    };
    EXPECT_PRED1(pred, actual);
}

TEST(Sat, solve_6_11) {
    auto solver = std::make_unique<Sat>(GameConfig(6, 11));

    auto guess = Code{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    auto feedback = Feedback{2, 0};
    solver->add_interaction(guess, feedback);

    auto actual = solver->solve();
    EXPECT_TRUE(eval_guess(guess, actual) == feedback);
}
