#include "lex.hpp"

#include <fstream>
#include <sstream>
#include <string>

std::string yyin;
std::string file_content;

void load_file() {
    std::ifstream      fs(yyin);
    std::ostringstream oss;
    oss << fs.rdbuf();
    file_content = oss.str();
    fs.close();
}

void read_from_input() {
    std::string s;
    while (std::cin >> s) {
        file_content += s;
        file_content += "\n";
    }
}

// Here's what we need to replace
void yylex() {
    if (yyin != "") {
        load_file();
    }
    else {
        read_from_input();
    }
    lex lexer;
    // INSERT RULE HERE
    lexer.execute(file_content);
}