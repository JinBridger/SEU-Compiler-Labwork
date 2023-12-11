#include "dfa.hpp"
#include "lexical_rules.hpp"
#include "regexpr.hpp"

#include <iostream>
#include <string>

void test() {
    std::string a = "aa*(bab*a)*(a|b)b*";
    std::cout << "postf: " << regexpr::convert(a) << std::endl;
}

int main() {
    test();
}