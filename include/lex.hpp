#pragma once

#include "dfa.hpp"
#include "fa.hpp"
#include "minimize_dfa.hpp"
#include "nfa.hpp"
#include "regexpr.hpp"
#include "runner.hpp"

#include <cstdlib>
#include <functional>
#include <map>
#include <string>
#include <tuple>
#include <vector>

class lex {
public:
    lex() : _total_enums(101) {}

    void add_regexpr(std::string reg, std::function<void(void)> func) {
        _regs.push_back(std::tuple<std::string, std::function<void(void)>, int>(reg, func, _total_enums++));
    }

    void execute(std::string prog) {
        std::map<int, std::function<void(void)>> table;
        std::vector<fa>                          fas;
        for (auto it : _regs) {
            table[std::get<2>(it)] = std::get<1>(it);
            auto reg_s             = regexpr::convert(std::get<0>(it));
            auto nfa               = nfa::convert(reg_s, std::get<2>(it));
            fas.push_back(nfa);
        }
        auto combined = nfa::combine_nfas(fas);
        auto fin_dfa  = dfa::convert(combined);
        auto min_dfa  = minimize_dfa::convert(fin_dfa);

        int res = runner::run(min_dfa, prog, table);
        if (res == -1) {
            exit(1);
        }
        // std::cout << "EOF" << std::endl;
    }

private:
    int _total_enums;

    std::vector<std::tuple<std::string, std::function<void(void)>, int>> _regs;
};