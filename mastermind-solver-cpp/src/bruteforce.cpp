#include "bruteforce.h"

#include "core.h"
#include <cmath>

namespace mastermind {
    bool consistent_with_history(const std::vector<Interaction> &history, const Code &secret) {
        for (auto &interaction: history)
            if (eval_guess(interaction.guess, secret) != interaction.feedback)
                return false;
        return true;
    }

    Code BruteForce::solve() {
        // Find first code that is consistent with history
        auto n_combinations = pow(config.num_symbols, config.secret_length);
        for(unsigned n=0; n < n_combinations; ++n) {
            Code code;
            unsigned rest = n;
            for(unsigned i=0; i<config.secret_length; ++i) {
                auto divisor = int(pow(config.num_symbols, config.secret_length-1-i));
                code.emplace_back(int(rest / divisor));
                rest = int(rest % divisor);
            }
            if(consistent_with_history(history, code))
                return code;
        }

        return {};
    }
}
