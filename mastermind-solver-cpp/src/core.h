#pragma once

#include <vector>

namespace mastermind {

    struct GameConfig {
        unsigned num_symbols;
        unsigned secret_length;
    };

    typedef std::vector<int> Code;

    struct Feedback {
        unsigned full_matches;
        unsigned partial_matches;

        auto operator<=>(const Feedback &other) const = default;
    };

    Feedback eval_guess(const Code &guess, const Code &secret);
}
