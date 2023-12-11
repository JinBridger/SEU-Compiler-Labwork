#include "dfa.hpp"
#include "lexical_rules.hpp"
#include "nfa.hpp"
#include "regexpr.hpp"

#include <iostream>
#include <string>

void test() {
    // std::cout << regexpr::convert("aa*(bab*a)*(a|b)b*");
    nfa::convert(regexpr::convert("aa*(bab*a)*(a|b)b*")).print();
}

int main() {
    test();
}