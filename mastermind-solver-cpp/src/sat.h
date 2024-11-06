#pragma once

#include "solver.h"

namespace mastermind {
    class Sat : public Solver {

    public:
        Sat(const GameConfig& config) : Solver(config) {}
        Code solve() override;
    };
}
