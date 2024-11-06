#include "sat.h"

extern "C" {
    #include "kissat.h"
}
#include <ranges>

typedef std::vector<int> clause_t;

class Encoder {
    int next_lit = 1;

public:
    Encoder() {

    }

    int fresh_lit() { return next_lit++; }
    int top_id() { return next_lit-1; }

    std::vector<clause_t> at_most(const std::vector<int>& lits, int r, int top_id) {
        auto n = (int)(lits.size());
        assert(n>0);

        std::vector<clause_t> new_clauses;
        if(r==0) {
            for(auto l: lits)
                new_clauses.push_back({-l});
        } else {
            // s[k][j]
            auto s = std::vector<std::vector<int>>(r+1);
            for(int k=0; k<r+1; ++k) {
                s[k] = std::vector<int>(n-r+1);
                for(int j=0; j<n-r+1; ++j) {
                    s[k][j] = top_id + 1 + k*(n-r+1) + j;
                }
            }

            for(int k=1; k<r+1; ++k) {
                for(int j=1; j<n-r; ++j) {
                    new_clauses.push_back({-s[k][j], s[k][j+1]});
                }
            }

            for(int k=0; k<r+1; ++k) {
                for(int j=1; j<n-r+1; ++j) {
                    clause_t new_clause;
                    if(k != 0)
                        new_clause.push_back(-s[k][j]);
                    if(k != r)
                        new_clause.push_back(s[k+1][j]);
                    new_clause.push_back(-lits[j+k-1]);
                    new_clauses.push_back(new_clause);
                }
            }
        }
        return new_clauses;
    }

    std::vector<clause_t> at_least(const std::vector<int>& lits, int r, int top_id) {
        assert(r <= (int)lits.size());

        std::vector<int> flipped_lits;
        flipped_lits.reserve(lits.size());
        for (auto lit:lits)
            flipped_lits.push_back(-lit);

        return at_most(flipped_lits, (int)lits.size()-r, top_id);
    }

    std::vector<clause_t> exactly(const std::vector<int>& lits, int r, int top_id) {
        std::vector<clause_t> new_clauses = at_most(lits, r, top_id);

        auto new_top_id = top_id;
        for(const auto& clause:new_clauses) {
            for(auto lit: clause) {
                new_top_id = std::max(new_top_id, std::abs(lit));
            }
        }

        auto at_least_clauses = at_least(lits, r, new_top_id);
        new_clauses.insert(new_clauses.end(), at_least_clauses.begin(), at_least_clauses.end());
        return new_clauses;
    }

    std::vector<clause_t> sum_eq(const std::vector<int>& lits, int k) {
        auto res = exactly(lits, k, top_id());

        int max_lit = 0;
        for(const auto& clause:res) {
            for(auto lit: clause) {
                max_lit = std::max(max_lit, std::abs(lit));
            }
        }
        next_lit = max_lit + 1;
        return res;
    }

    std::vector<clause_t> mk_impl(int a, int b) {
        auto clause = clause_t{-a, b};
        return {clause};
    }

    std::vector<clause_t> mk_eq(int a, int b) {
        auto clauses = mk_impl(a,b);
        auto tmp = mk_impl(b,a);
        clauses.insert(clauses.end(), tmp.begin(), tmp.end());
        return clauses;
    }

    std::vector<clause_t> mk_eq_and(int a, int andLhs, int andRhs) {
        return std::vector<clause_t>{{andLhs, andRhs, -a}, {andLhs, -andRhs, -a}, {-andLhs, andRhs, -a}, {-andLhs, -andRhs, a}};
    }

    std::vector<clause_t> mk_eq_ands(int a, std::vector<int> cube, int top_id) {
        std::vector<clause_t> res;
        if(cube.empty())
            res.push_back({a});
        else if(cube.size() == 1)
            res = mk_eq(a, cube.front());
        else {
            auto cur = a;
            for(int i=0; i<(int)cube.size()-2; ++i) {
                auto lit = top_id + (i+1);
                auto tmp = mk_eq_and(cur, cube.at(i), lit);
                res.insert(res.end(), tmp.begin(), tmp.end());
                cur = lit;
            }
            auto tmp = mk_eq_and(cur, cube.at(cube.size()-2), cube.back());
            res.insert(res.end(), tmp.begin(), tmp.end());
            next_lit += (int)cube.size()-2;
        }
        return res;
    }
};

// TODO: Avoid unnecessary reallocation. Add lits/clauses immediately
mastermind::Code mastermind::Sat::solve() {
    auto encoder = new Encoder();
    auto clauses = std::vector<clause_t>();

    // Possible values at secret positions, i.e. s[0][2] denotes position 0 of secret having symbol 2
    auto s = std::vector<std::vector<int>>();
    s.reserve(config.secret_length);
    for(unsigned pos=0; pos<config.secret_length; ++pos) {
        std::vector<int> lits;
        lits.reserve(config.num_symbols);
        for(unsigned sym=0; sym<config.num_symbols; ++sym) {
            lits.push_back(encoder->fresh_lit());
        }
        s.push_back(lits);
    }

    // Exactly one symbol on each position
    for (unsigned pos=0; pos<config.secret_length; ++pos) {
        auto new_clauses = encoder->sum_eq(s[pos], 1);
        clauses.insert(clauses.end(), new_clauses.begin(), new_clauses.end());
    }

    for(auto const& interaction : history) {
        // Fresh "full match" variables for each position
        std::vector<int> fm;
        for(unsigned pos=0; pos<config.secret_length; ++pos)
            fm.push_back(encoder->fresh_lit());

        // Full matches must be consistent with feedback
        auto new_clauses = encoder->sum_eq(fm, (int)interaction.feedback.full_matches);
        clauses.insert(clauses.end(), new_clauses.begin(), new_clauses.end());

        // Possible full matches
        for(unsigned pos=0; pos<config.secret_length; ++pos) {
            auto sym = interaction.guess[pos];
            auto new_clauses = encoder->mk_eq(s[pos][sym], fm[pos]);
            clauses.insert(clauses.end(), new_clauses.begin(), new_clauses.end());
        }

        // Fresh "symbol match" variables for each pair of positions
        auto sm = std::vector<std::vector<int>>();
        sm.reserve(config.secret_length);
        for(unsigned src_pos=0; src_pos<config.secret_length; ++src_pos) {
            std::vector<int> tmp;
            tmp.reserve(config.secret_length);
            for(unsigned dst_pos=0; dst_pos<config.secret_length; ++dst_pos) {
                tmp.push_back(encoder->fresh_lit());
            }
            sm.push_back(tmp);
        }

        // Symbol matches must be consistent with feedback
        std::vector<int> sm_wo_diagonal;
        for(unsigned src_pos=0; src_pos<config.secret_length; ++src_pos) {
            for(unsigned dst_pos=0; dst_pos<config.secret_length; ++dst_pos) {
                if(src_pos == dst_pos)
                    continue;
                sm_wo_diagonal.push_back(sm[src_pos][dst_pos]);
            }
        }
        new_clauses = encoder->sum_eq(sm_wo_diagonal, (int)interaction.feedback.partial_matches);
        clauses.insert(clauses.end(), new_clauses.begin(), new_clauses.end());

        // Possible symbol matches
        for(unsigned src_pos=0; src_pos<config.secret_length; ++src_pos) {
            std::vector<clause_t> new_clauses;
            for(unsigned dst_pos=0; dst_pos<config.secret_length; ++dst_pos) {
                if(src_pos == dst_pos)
                    continue;

                std::vector<int> cube;
                cube.push_back(-fm[src_pos]);
                cube.push_back(s[dst_pos][interaction.guess[src_pos]]);
                cube.push_back(-fm[dst_pos]);
                // No previous position in the guess has a symbol match with the current dst_pos
                for(unsigned prev_pos=0; prev_pos<src_pos; ++prev_pos) {
                    if (dst_pos != prev_pos)
                        cube.push_back(-sm[prev_pos][dst_pos]);
                }
                // src_pos has no symbol match with a previous dst_pos
                for(unsigned prev_pos=0; prev_pos<dst_pos; ++prev_pos) {
                    if (src_pos != prev_pos)
                        cube.push_back(-sm[src_pos][prev_pos]);
                }

                new_clauses = encoder->mk_eq_ands(sm[src_pos][dst_pos], cube, encoder->top_id());
                clauses.insert(clauses.end(), new_clauses.begin(), new_clauses.end());
            }
        }
    }

    auto solver = kissat_init();
    for(const auto& clause : clauses) {
        for(auto lit: clause) {
            kissat_add(solver, lit);
        }
        kissat_add(solver, 0);
    }
    auto res = kissat_solve(solver);
    if (res != 10)
        return Code{};

    Code best_guess;
    for(unsigned pos=0; pos<config.secret_length; ++pos) {
        for(unsigned sym=0; sym<config.num_symbols; ++sym) {
            if(kissat_value(solver, s[pos][sym]) > 0) {
                best_guess.push_back((int)sym);
                break;
            }
        }
    }

    return best_guess;
}
