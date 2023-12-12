#include "dfa.hpp"
#include "nfa.hpp"
#include "regexpr.hpp"

#include <iostream>
#include <set>
#include <string>

void test() {
    // std::cout << regexpr::convert("aa*(bab*a)*(a|b)b*");
    // nfa::convert(regexpr::convert("aa*(bab*a)*(a|b)b*")).print();
    // std::set<int> a;
    // a.insert(3);

    // auto epsilon_closure = dfa::find_char_closure(nfa::convert(regexpr::convert("aa*(bab*a)*(a|b)b*")), a, 'a');
    // for (auto it : epsilon_closure) {
    //     std::cout << it << std::endl;
    // }

    // nfa::convert(regexpr::convert("aa*(bab*a)*(a|b)b*")).print();

    dfa::convert(nfa::convert(regexpr::convert("a(bab*a)*(a|b)b*"))).print();
}

int main() {
    test();
}