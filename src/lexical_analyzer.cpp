#include "lex.hpp"

void test() {
    lex test_lex;
    test_lex.add_regexpr(" ( )*", "space");               // 101
    test_lex.add_regexpr("{", "lft_b");                   // 102
    test_lex.add_regexpr("}", "rht_b");                   // 103
    test_lex.add_regexpr("\\(", "lft_c");                 // 104
    test_lex.add_regexpr("\\)", "rht_c");                 // 105
    test_lex.add_regexpr(";", "comma");                   // 106
    test_lex.add_regexpr("int", "integ");                 // 107
    test_lex.add_regexpr("return", "retur");              // 108
    test_lex.add_regexpr("(0|1|2)*", "numbe");            // 109
    test_lex.add_regexpr("(m|a|i|n|r|e|t|u)*", "ident");  // 110
    test_lex.add_regexpr("\n", "enter");                  // 111
    test_lex.match("int main()\n {return 0;}");
}

int main() {
    // test();
    test();
}