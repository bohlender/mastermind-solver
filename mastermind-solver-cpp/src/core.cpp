#include <cassert>
#include <map>
#include "core.h"

namespace mastermind {
    Feedback eval_guess(const Code &guess, const Code &secret) {
        assert(guess.size() == secret.size());

        unsigned full_matches = 0;
        std::map<int, size_t> guess_rest_frequencies = {};
        std::map<int, size_t> secret_rest_frequencies = {};
        for (size_t i = 0; i < guess.size(); ++i) {
            auto guess_i = guess.at(i);
            auto secret_i = secret.at(i);
            if (guess_i == secret_i) {
                ++full_matches;
            } else {
                auto it = guess_rest_frequencies.find(guess_i);
                guess_rest_frequencies[guess_i] = 1 + (it == guess_rest_frequencies.end() ? 0 : it->second);

                it = secret_rest_frequencies.find(secret_i);
                secret_rest_frequencies[secret_i] = 1 + (it == secret_rest_frequencies.end() ? 0 : it->second);
            }
        }

        unsigned partial_matches = 0;
        for (auto kv: guess_rest_frequencies) {
            auto it = secret_rest_frequencies.find(kv.first);
            if (it != secret_rest_frequencies.end())
                partial_matches += std::min(kv.second, it->second);
        }

        return Feedback{.full_matches=full_matches, .partial_matches=partial_matches};
    }
}