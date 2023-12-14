#include "lex.hpp"

void test() {
    lex test_lex;
    test_lex.add_regexpr(" ( )*", "space");
    test_lex.add_regexpr("{", "lft_b");
    test_lex.add_regexpr("}", "rht_b");
    test_lex.add_regexpr("\\(", "lft_c");
    test_lex.add_regexpr("\\)", "rht_c");
    test_lex.add_regexpr("=", "assig");
    test_lex.add_regexpr(";", "comma");
    test_lex.add_regexpr("int", "integ");
    test_lex.add_regexpr("main", "mainf");
    test_lex.add_regexpr("return", "retur");
    test_lex.add_regexpr("(0|1|2)*", "numbe");
    test_lex.add_regexpr("(a-z|A-Z|_)(a-z|A-Z|0-9|_)*", "ident");
    test_lex.add_regexpr("\n", "enter");
    test_lex.match("int main()\n {int test = 1; return 0;}");
}

int main() {
    // test();
    test();
}