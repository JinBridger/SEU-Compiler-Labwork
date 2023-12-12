#include "dfa.hpp"
#include "minimize_dfa.hpp"
#include "nfa.hpp"
#include "regexpr.hpp"

#include <iostream>
#include <string>

void test() {
    while (1) {
        std::string reg;
        std::cin >> reg;
        auto i   = dfa::convert(nfa::convert(regexpr::convert(reg)));
        auto res = minimize_dfa::convert(i);
        res.print();
    }
}

int main() {
    test();
}