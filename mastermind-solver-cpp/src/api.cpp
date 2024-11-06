#include "api.h"
#include "sat.h"

extern "C" {
    mastermind::Solver *Solver_ctor(unsigned num_symbols, unsigned secret_length) {
        auto solver = new mastermind::Sat(mastermind::GameConfig(num_symbols, secret_length));
        return solver;
    }

    void Solver_dtor(mastermind::Solver *solver) {
        delete solver;
    }

    void add_interaction(mastermind::Solver *solver, int *code, unsigned full_matches, unsigned partial_matches) {
        auto c = mastermind::Code(code, code + solver->config.secret_length);
        auto f = mastermind::Feedback{.full_matches=full_matches, .partial_matches=partial_matches};
        solver->add_interaction(c, f);
    }

    bool solve(mastermind::Solver *solver, int *code) {
        auto res = solver->solve();
        if (res.empty()) {
            return false;
        } else {
            std::copy(res.cbegin(), res.cend(), code);
            return true;
        }
    }
}