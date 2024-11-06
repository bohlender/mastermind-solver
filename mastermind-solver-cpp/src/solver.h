#pragma once

#include <vector>
#include "core.h"
#include <cassert>

namespace mastermind {
    struct Interaction {
        Code guess;
        Feedback feedback;
    };

    class Solver {
    protected:
        std::vector<Interaction> history;

    public:
        const GameConfig config;

        explicit Solver(const GameConfig& config): config(config) {}

        void add_interaction(const Code &guess, const Feedback &feedback) {
            assert(guess.size() == config.secret_length);
            history.push_back(Interaction{.guess=guess, .feedback=feedback});
        }

        virtual Code solve() = 0;
        virtual ~Solver() = default;
    };
}
