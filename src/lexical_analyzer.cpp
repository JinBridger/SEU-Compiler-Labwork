#include "dfa.hpp"
#include "minimize_dfa.hpp"
#include "nfa.hpp"
#include "regexpr.hpp"
#include "runner.hpp"

#include <iostream>
#include <string>
#include <vector>

void test_single() {
    std::string     rega = " ( )*";
    auto            a    = regexpr::convert(rega);
    auto            nfaa = nfa::convert(a, 100);
    std::vector<fa> vec{ nfaa };
    auto            res     = nfa::combine_nfas(vec);
    auto            dfares  = dfa::convert(res);
    auto            minires = minimize_dfa::convert(dfares);
    minires.print();
}

void test() {

    std::string space = " ( )*";  // 101
    std::string lft_b = "{";      // 102
    std::string rht_b = "}";      // 103
    // std::string lft_c = "(";                   // 104
    // std::string rht_c = ")";                   // 105
    std::string comma = ",";                   // 106
    std::string integ = "int";                 // 107
    std::string retur = "return";              // 108
    std::string numbe = "(0|1|2)*";            // 109
    std::string ident = "(m|a|i|n|r|e|t|u)*";  // 110

    auto reg_space = regexpr::convert(" *");  // 101
    auto reg_lft_b = regexpr::convert("{");   // 102
    auto reg_rht_b = regexpr::convert("}");   // 103
    // auto reg_lft_c = regexpr::convert("(");                    // 104
    // auto reg_rht_c = regexpr::convert(")");                    // 105
    auto reg_comma = regexpr::convert(";");                   // 106
    auto reg_integ = regexpr::convert("int");                 // 107
    auto reg_retur = regexpr::convert("return");              // 108
    auto reg_numbe = regexpr::convert("(0|1|2)(0|1|2)*");     // 109
    auto reg_ident = regexpr::convert("(m|a|i|n|r|e|t|u)*");  // 110
    std::cout << "FINISH REGEXPR CVT" << std::endl;

    auto nfa_space = nfa::convert(reg_space, 101);  // 101
    auto nfa_lft_b = nfa::convert(reg_lft_b, 102);  // 102
    auto nfa_rht_b = nfa::convert(reg_rht_b, 103);  // 103
    // auto nfa_lft_c = nfa::convert(reg_lft_c, 104);  // 104
    // auto nfa_rht_c = nfa::convert(reg_rht_c, 105);  // 105
    auto nfa_comma = nfa::convert(reg_comma, 106);  // 106
    auto nfa_integ = nfa::convert(reg_integ, 107);  // 107
    auto nfa_retur = nfa::convert(reg_retur, 108);  // 108
    auto nfa_numbe = nfa::convert(reg_numbe, 109);  // 109
    auto nfa_ident = nfa::convert(reg_ident, 110);  // 110
    std::cout << "FINISH NFA CVT" << std::endl;

    std::vector<fa> vec = { nfa_space, nfa_lft_b, nfa_rht_b,  // nfa_lft_c, nfa_rht_c,
                            nfa_comma, nfa_integ, nfa_retur, nfa_numbe, nfa_ident };

    auto combined = nfa::combine_nfas(vec);
    std::cout << "FINISH COMBINE" << std::endl;
    auto fin_dfa = dfa::convert(combined);
    std::cout << "FINISH CVT2DFA" << std::endl;
    auto fin_mindfa = minimize_dfa::convert(fin_dfa);
    std::cout << "FINISH MINDFA" << std::endl;

    std::string s   = "int main {return 0;}";
    int         res = runner::run(fin_dfa, s);
    std::cout << ((res == -1) ? "failed" : "eof");
}

int main() {
    test();
}