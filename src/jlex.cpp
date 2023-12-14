#include "file_reader.hpp"
#include "generate_cpp.hpp"

#include <iostream>

void execute(std::string input_file) {
    file_reader f;
    f.read_file_to_string(input_file);
    f.split_sections();
    f.parse_all_rules();
    f.parse_definition_code();
    generate_cpp g;
    g.load_source();
    g.find_insert_rule_pos();
    for (auto r : f._parsed_rules) {
        g.insert_parsed_rule(r);
    }
    g.insert_begin_program(f._definitions_code);
    g.insert_end_program(f._programs);
    g.output_cpp_file("./lex.yy.cpp");
}

int main(int argc, char** argv) {
    // test();
    // test_file_read();
    if (argc != 2) {
        std::cout << "usage: jlex [FILE]" << std::endl;
        return 0;
    }
    std::string input_file = argv[1];
    execute(input_file);
}