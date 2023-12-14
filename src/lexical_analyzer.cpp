#include "file_reader.hpp"
#include "lex.hpp"

void test() {
    lex test_lex;
    test_lex.add_regexpr(" ( )*", []() { std::cout << "space" << std::endl; });
    test_lex.add_regexpr("{", []() { std::cout << "lft_b" << std::endl; });
    test_lex.add_regexpr("}", []() { std::cout << "rht_b" << std::endl; });
    test_lex.add_regexpr("\\(", []() { std::cout << "lft_c" << std::endl; });
    test_lex.add_regexpr("\\)", []() { std::cout << "rht_c" << std::endl; });
    test_lex.add_regexpr("=", []() { std::cout << "assig" << std::endl; });
    test_lex.add_regexpr(";", []() { std::cout << "comma" << std::endl; });
    test_lex.add_regexpr("int", []() { std::cout << "integ" << std::endl; });
    test_lex.add_regexpr("main", []() { std::cout << "mainf" << std::endl; });
    test_lex.add_regexpr("return", []() { std::cout << "retur" << std::endl; });
    test_lex.add_regexpr("(0|1|2)*", []() { std::cout << "numbe" << std::endl; });
    test_lex.add_regexpr("(a-z|A-Z|_)(a-z|A-Z|0-9|_)*", []() { std::cout << "ident" << std::endl; });
    test_lex.add_regexpr("\n", []() { std::cout << "enter" << std::endl; });
    test_lex.execute("int main()\n {int test = 1; return 0;}");
}

void test_file_read() {
    file_reader f;
    f.read_file_to_string("./example/example.l");
    f.split_sections();
    f.parse_all_rules();
    f.parse_definition_code();
    std::cout << "FIN";
}

int main() {
    test();
    // test_file_read();
}