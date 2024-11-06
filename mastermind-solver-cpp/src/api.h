namespace mastermind {
    class Solver;
}

extern "C" {
    mastermind::Solver *Solver_ctor(unsigned num_symbols, unsigned secret_length);
    void Solver_dtor(mastermind::Solver *solver);
    void add_interaction(mastermind::Solver *solver, int *code, unsigned full_matches, unsigned partial_matches);
    // code expected to be allocated and reasonably sized
    bool solve(mastermind::Solver *solver, int *code);
}