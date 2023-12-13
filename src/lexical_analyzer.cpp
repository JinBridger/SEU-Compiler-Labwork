#include "dfa.hpp"
#include "minimize_dfa.hpp"
#include "nfa.hpp"
#include "regexpr.hpp"

#include <iostream>
#include <string>
#include <vector>

void test() {
    std::string     rega = "abc";
    std::string     regb = "ab";
    auto            a    = regexpr::convert(rega);
    auto            b    = regexpr::convert(regb);
    auto            nfaa = nfa::convert(a, 100);
    auto            nfab = nfa::convert(b, 101);
    std::vector<fa> vec{ nfaa, nfab };
    auto            res     = nfa::combine_nfas(vec);
    auto            dfares  = dfa::convert(res);
    auto            minires = minimize_dfa::convert(dfares);
    minires.print();
}

int main() {
    test();
}