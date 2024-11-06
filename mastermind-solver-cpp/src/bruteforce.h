#pragma once

#include "solver.h"
#include "core.h"

namespace mastermind {
    class BruteForce : public Solver {

    public:
        BruteForce(const GameConfig& config) : Solver(config) {}
        Code solve() override;
    };
}
