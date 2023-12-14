#pragma once

#include "dfa.hpp"
#include "fa.hpp"
#include "minimize_dfa.hpp"
#include "nfa.hpp"
#include "regexpr.hpp"
#include "runner.hpp"

#include <map>
#include <string>
#include <tuple>
#include <vector>

class lex {
public:
    lex() : _total_enums(101) {}

    void add_regexpr(std::string reg, std::string name) {
        _regs.push_back(std::tuple<std::string, std::string, int>(reg, name, _total_enums++));
    }

    void match(std::string prog) {
        std::map<int, std::string> table;
        std::vector<fa>            fas;
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
            std::cout << "ERROR!" << std::endl;
            return;
        }
        std::cout << "EOF" << std::endl;
    }

private:
    int _total_enums;

    std::vector<std::tuple<std::string, std::string, int>> _regs;
};